#include "CAudioConverter.h"
#include "CApplication.h"

extern CApplication app;
struct FormatChunk
{
    char            chunkID[4];
    long            chunkSize;
    short           wFormatTag;
    unsigned short  wChannels;
    unsigned long   dwSamplesPerSec;
    unsigned long   dwAvgBytesPerSec;
    unsigned short  wBlockAlign;
    unsigned short  wBitsPerSample;
};

struct Chunk
{
    char            chunkID[4];
    long            chunkSize;
};

typedef struct
{        
	HINSTANCE	        mDLL;
	BE_VERSION	        Version;    
    BEINITSTREAM        beInitStream;
    BEENCODECHUNK       beEncodeChunk;
    BEDEINITSTREAM      beDeinitStream;
    BECLOSESTREAM       beCloseStream;
    BEVERSION           beVersion;
    BEWRITEVBRHEADER    beWriteVBRHeader;

}outputmp3_state;

char startID[12];

void CAudioConverter::DisplayTime(char *strText)
{
 SYSTEMTIME st;
 GetLocalTime(&st);
 Log << strText << setw(2) << setfill('0') << st.wHour << ":" 
	            << setw(2) << setfill('0') << st.wMinute << ":" 
			    << setw(2) << setfill('0') << st.wSecond << endl;
}


bool CAudioConverter::Init(HWND hWnd)
{
 string strFile=app.GetWinDirectory().c_str();
 strFile+="\\";
 strFile+="audio_converter.log";
 Log.open(strFile.c_str());
 if(Log.fail()){
  MessageBox(NULL,TEXT("Error al abrir en el archivo"),TEXT("Audio Converter"),MB_ICONERROR);
  return false;
 }
 
 if(HIWORD(BASS_GetVersion())!=BASSVERSION) {
   Log << "Una version incorrecta de BASS se ha cargado" << endl;
   return false;
 }
 Log << "Version correcta" << endl;


 if (!BASS_Init(0,44100,0,hWnd,NULL)){
  Log << "Error no se pudo inicializar el dispositivo de sonido" << endl;
  return false;
 }
 Log << "Inicializacion de bass correcta" << endl;
 
 return true;
}

void CAudioConverter::Close()
{ 
 Log << "Cerrando BASS" << endl;
 BASS_Free(); 
 Log.close();
}

void CAudioConverter::InitProgressBar(HWND hWnd,UINT uID,COLORREF Color)
{
 
  p.SetWNDProgressBar(hWnd,uID);
  p.SetRangeProgressBar(1,10);
  p.SetStepProgressBar(1);     	
  p.SetBarColorProgressBar(Color); 
 
}

bool CAudioConverter::CdaToWav(char cDrive,int iTrackNum,string Out)
{
 DWORD chan,t;
 QWORD pos,length=1;
 FILE *fp=NULL;
 BYTE *buf=new BYTE[20000];
 char *strTrack=new char[30];
 WAVEFORMATEX wf;



 if(!buf){
  Log << "No hay memoria suficiente" << endl;
  return false;
 }
 
 if(!strTrack){
  Log << "No hay memoria suficiente" << endl;
  return false;
 }
 Log << "Asignacion de memoria correcta" << endl; 
 sprintf(strTrack,"%c:\\Track%02d.cda",toupper(cDrive),iTrackNum);
 if (!(chan=BASS_CD_StreamCreateFile(strTrack,BASS_STREAM_DECODE))){
  Log << "Error al crear el archivo " << strTrack << endl;
  return false;
 }
 Log << "Creando Stream para " << strTrack << endl;
 pos=BASS_ChannelGetLength(chan);
 if (pos) {
   t=(DWORD)BASS_ChannelBytes2Seconds(chan,pos);
   length=pos;  
 }
 else
  length=1;

 if (!(fp=fopen(Out.c_str(),"wb"))){
  Log << "Error al crear el archivo " << Out.c_str() << endl;
  return false;
 }
 Log << "Se abrio el archivo: " << Out.c_str() << " correctamente" << endl;
    wf.wFormatTag=1;
	wf.nChannels=2;
	wf.wBitsPerSample=16;
	wf.nBlockAlign=4;
	wf.nSamplesPerSec=44100;
	wf.nAvgBytesPerSec=176400;
	fwrite("RIFF\0\0\0\0WAVEfmt \20\0\0\0",20,1,fp);
	fwrite(&wf,16,1,fp);
	fwrite("data\0\0\0\0",8,1,fp);

	Log << "Creando el archivo wav\nEspere un momento..." << endl;
	while (BASS_ChannelIsActive(chan)) {		
		fwrite(buf,1,BASS_ChannelGetData(chan,buf,20000),fp);
		pos=BASS_ChannelGetPosition(chan);				
		p.SetValueProgressBar((pos*10)/length);
		p.Update();		
		
	}
	
	fflush(fp);
	t=ftell(fp);
	fseek(fp,4,SEEK_SET);
	_putw(t-8,fp);
	fflush(fp);
	fseek(fp,40,SEEK_SET);
	_putw(t-44,fp);
	fflush(fp);
	Log << "Se creo el archivo" << endl;
	if(fp!=NULL){
	 Log << "Cerrando archivo " << endl;
	 fclose(fp);
	}

		
	if(buf!=0){
	 delete [] buf;
	 Log << "Libeando memoria del buffer" << endl;
	}
	if(strTrack!=0){
	 Log << "Liberando memoria del track" << endl;
	 delete strTrack;
	}
	p.ReinitProgressBar();
    Log << "Reiniciando progress bar" << endl;
    return true;
}

bool CAudioConverter::WavToMp3(string strFileName,string OutputFileName)
{
    outputmp3_state *state;
	BE_CONFIG bc={0,};

    state =  new outputmp3_state;

	state->mDLL = LoadLibrary("lame_enc.dll");
	if (!state->mDLL){
		Log << "Error al cargar lame_enc.dll" << endl;
		return false;
	}
	Log << "Se cargo correctamente lame_enc.dll" << endl;
	state->beInitStream	    = (BEINITSTREAM)     GetProcAddress(state->mDLL, TEXT_BEINITSTREAM);
	state->beEncodeChunk	= (BEENCODECHUNK)    GetProcAddress(state->mDLL, TEXT_BEENCODECHUNK);
	state->beDeinitStream	= (BEDEINITSTREAM)   GetProcAddress(state->mDLL, TEXT_BEDEINITSTREAM);
	state->beCloseStream	= (BECLOSESTREAM)    GetProcAddress(state->mDLL, TEXT_BECLOSESTREAM);
	state->beVersion		= (BEVERSION)        GetProcAddress(state->mDLL, TEXT_BEVERSION);
	state->beWriteVBRHeader = (BEWRITEVBRHEADER) GetProcAddress(state->mDLL, TEXT_BEWRITEVBRHEADER);

	if(!state->beInitStream || !state->beEncodeChunk || !state->beDeinitStream || !state->beCloseStream || !state->beVersion || !state->beWriteVBRHeader){
		Log << "Error al leer las funciones de lame_enc.dll" << endl;
		return false;
	}
    Log << "Se obtuvieron las funciones de lame_enc.dll correctamente" << endl;
	state->beVersion( &state->Version );

    ifstream fin(strFileName.c_str(), std::ios::binary);
    if(!fin){
	  Log << "No existe el archivo" << endl;
      return false;
	}
    Log << "Se abrio el archivo " << strFileName.c_str() << " correctamente" << endl;
    fin.read((char*)&startID, sizeof(startID)); 
    FormatChunk fc;
    fin.read((char*)&fc, sizeof(FormatChunk)); 
    if(strncmp(fc.chunkID, "fmt ", 4) != 0){
        
		Log << "No es un archivo valido" << endl;
        return false;
    }
    if(fc.wFormatTag!=1){        
		Log << "Error handle" << endl;
        return false;
    }
    
    Log << "Archivo valido"<< endl;
	memset(&bc,0,sizeof(bc));
    bc.dwConfig = BE_CONFIG_MP3;
    
    if(fc.dwSamplesPerSec == 32000 || fc.dwSamplesPerSec == 44100 || fc.dwSamplesPerSec == 48000){
        bc.format.mp3.dwSampleRate = fc.dwSamplesPerSec;
		Log << "Muestreo " << fc.dwSamplesPerSec << " correcto" << endl;
	}
    else
    {
        
		Log << "muestreo sin soportar" << endl;
        return false;
    }
    if(fc.wChannels == 1)
        bc.format.mp3.byMode = BE_MP3_MODE_MONO;
    else
        bc.format.mp3.byMode = BE_MP3_MODE_STEREO;

	Log << "Canales: " << fc.wChannels << endl;
    bc.format.mp3.wBitrate = 192;
    bc.format.mp3.bCopyright = false;
    bc.format.mp3.bCRC = false;
    bc.format.mp3.bOriginal = false;
    bc.format.mp3.bPrivate = false;
  
    if(sizeof(FormatChunk) < int(8 + fc.chunkSize)){
        char c;
        for(int i=0; i< int(8 + fc.chunkSize - sizeof(FormatChunk)); i++)
            fin.get(c);
    }
   
    Chunk chunk;
    fin.read((char*)&chunk, sizeof(Chunk));
    Log << "Leyendo la estructura Chunk" << endl;
    while(strncmp(chunk.chunkID, "data", 4) != 0){
        char c;
        for(int i=0; i<chunk.chunkSize; i++)
            fin.get(c);
        fin.read((char*)&chunk,sizeof(Chunk));
    }
   
    DWORD dwNumberOfSamples;
    DWORD dwOutputBufferLength;
    HBE_STREAM hStream;


    if(state->beInitStream(&bc, &dwNumberOfSamples, &dwOutputBufferLength,&hStream) != BE_ERR_SUCCESSFUL){        
	 Log << "Error no se pudo comprimir" << endl;
     return false;
    }
	Log << "Se ha inicializado Stream correctamente" << endl;
    ofstream fout(OutputFileName.c_str(), ios::binary);
	if(!fout){
     Log << "Error no se pudo crear el archivo" << endl;
	 return false;
	}
	Log << "Se ha abierto el archivo de salida: " << OutputFileName.c_str() << " corretamente" << endl;
    char *Mp3Buffer = new char[dwOutputBufferLength];
    SHORT  *InputBuffer = new SHORT [dwNumberOfSamples];      
    
    if(!Mp3Buffer){
     Log << "No hay memoria" << endl;
	 return false;
	}

     Log << "Se ha asignado memoria para el Buffer Mp3 correctamente" << endl;
	if(!InputBuffer){
     Log << "No hay memoria" << endl;
	 return false;
	}
    Log << "Se ha asignado memoria para el Buffer de entrada" << endl;
    int nSamplesPerformed=0;
    DWORD dwNumberOfSamplesEncoded;
    Log << "Espere un momento" << endl;
    while(nSamplesPerformed < chunk.chunkSize){
        fin.read((char*)InputBuffer, dwNumberOfSamples * 2);
        nSamplesPerformed += dwNumberOfSamples * 2;				
        if(state->beEncodeChunk(hStream, dwNumberOfSamples, InputBuffer,(BYTE*)Mp3Buffer, &dwNumberOfSamplesEncoded) != BE_ERR_SUCCESSFUL){
            
			Log << "no se pudo comprimir" << endl;					
            return false;
		
        }
	
        fout.write(Mp3Buffer, dwNumberOfSamplesEncoded);
		p.SetValueProgressBar((nSamplesPerformed *10)/chunk.chunkSize);
		p.Update();
		
    }
	 Log << "Cerrando el Stream" << endl;
    state->beDeinitStream(hStream, (BYTE*)Mp3Buffer, &dwNumberOfSamplesEncoded);
    state->beCloseStream(hStream);

	Log << "Liberando memoria" << endl;
    delete Mp3Buffer;
    delete InputBuffer;
	delete state;
	Log << "Cerrando archivos" << endl;
	fin.close();
	fout.close();
	Log << "Reiniciando ProgressBar" << endl;
	p.ReinitProgressBar();	
    return true;
}
