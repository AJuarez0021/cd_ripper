#include "CPanel.h"
extern CCDInformation cdinf;
extern CPanel p;

struct Information
{
 int iOutput;
 char cDrive;
}inf;


void CApplication::OpenMp3(HWND hWnd)
{
 if(b.Browse(TEXT("Abrir")))
  SetDlgItemText(hWnd,IDC_EDIT_MP3,b.GetFolderName());
}

void CApplication::OpenWav(HWND hWnd)
{
 if(b.Browse(TEXT("Abrir")))
  SetDlgItemText(hWnd,IDC_EDIT_WAV,b.GetFolderName());
}
void CApplication::ReadConfig()
{
 
 ifstream in; 
 in.open("config.ini");
 if(!in.fail()){
  string strLine;
  getline(in,strLine);
  getline(in,strLine);
  strcpy(m_strMp3,strLine.c_str());
  getline(in,strLine);
  getline(in,strLine);
  strcpy(m_strWav,strLine.c_str());
  getline(in,strLine);
  getline(in,strLine);
  m_output=atoi(strLine.c_str());
  in.close();
 }
}
void CApplication::OnInitConverter(HWND hWnd,CComboBox c)
{
 ReadConfig();
 SetDlgItemText(hWnd,IDC_EDIT_MP3,m_strMp3);
 SetDlgItemText(hWnd,IDC_EDIT_WAV,m_strWav);
 c.SetCurSel(m_output);
}
void CApplication::WriteConfig(HWND hWnd,CComboBox c)
{
 ofstream out;
 GetDlgItemText(hWnd,IDC_EDIT_MP3,m_strMp3,MAX_PATH);
 GetDlgItemText(hWnd,IDC_EDIT_WAV,m_strWav,MAX_PATH);
 out.open("config.ini");
 if(out.fail()){
  ShowError(TEXT("Error el archivo config.ini no se pudo crear"));
  return;
 }

 out << "[PATH MP3]" << endl;
 out << m_strMp3  << endl;
 out << "[PATH WAV]" << endl;
 out << m_strWav  << endl;
 out << "[OUTPUT]" << endl;
 out << c.GetCurSel();
 out.close();
 EnableWindow(GetDlgItem(hWnd,ID_SETTINGS_OK),FALSE);
 EndDialog(hWnd,0);

}



 
bool CApplication::Converter(HWND hWnd)
{  

 if(Tracks.size() > 0){   
  c.DisplayTime("Hora de Inicio: ");
  char strTmpFile[40];  
  string strTrack;

  ReadConfig();
  s.SetText(TEXT("Espere un momento..."));
  
  if(inf.iOutput==MP3){
   for(short i=0;i<Tracks.size();i++){
	
	sprintf(strTmpFile,"%c:\\temp.wav",GetDrive());    
	SetText(hWnd,IDC_TEXT,TEXT("Accion: Convirtiendo Track%02d.cda a temp.wav"),Tracks[i]+1);    
	
    if(c.CdaToWav(inf.cDrive,Tracks[i]+1,strTmpFile)){		 
	 strTrack=GetMp3Path();	
	
	 switch(GetOutPut()){
	  case 0: 
		     strTrack+="\\Track";	 
	         if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);
	         strTrack+=".mp3";
		     break;
	  case 1:
			 strTrack+="\\";
			 strTrack+=cdinf.GetArtist().c_str();
			 strTrack+="-Track";
			 if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);			 			 
			 strTrack+=".mp3";			 
		     break;
	  case 2:
			 strTrack+="\\";
			 strTrack+=cdinf.GetArtist().c_str();
			 strTrack+="-";
			 strTrack+=cdinf.GetAlbum().c_str();
             strTrack+="-Track";
			 if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);            
			 strTrack+=".mp3";
		     break;
	  case 3:
		     strTrack+="\\";
		     strTrack+=cdinf.GetArtist().c_str();
			 strTrack+="-Track";
			 if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);
			 strTrack+=".mp3";
		     break;
	  case 4:strTrack+="\\";
		     strTrack+=cdinf.GetGenre().c_str();
			 strTrack+="-";
			 strTrack+=cdinf.GetArtist().c_str();
			 strTrack+="-Track";
			 if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);
			 strTrack+=".mp3";
		     break;
	  case 5:strTrack+="\\";
		     strTrack+=cdinf.GetGenre().c_str();		
			 strTrack+="-Track";
			 if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);
			 strTrack+=".mp3";
		     break;
	  case 6:strTrack+="\\";
		     strTrack+=cdinf.Get_Year().c_str();
			 strTrack+="-";
			 strTrack+=cdinf.GetGenre().c_str();			 
			 strTrack+="-Track";
			 if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);
			 strTrack+=".mp3";
		     break;
	  case 7:strTrack+="\\";
		     strTrack+=cdinf.Get_Year().c_str();
			 strTrack+="-";
			 strTrack+=cdinf.GetArtist().c_str();
             strTrack+="-Track";
			 if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);			 			 
			 strTrack+=".mp3";
		     break;


	 }
	 
	 SetText(hWnd,IDC_TEXT,TEXT("Accion: Convirtiendo temp.wav a Track%02d.mp3"),Tracks[i]+1);
	 if(!c.WavToMp3(strTmpFile,strTrack)){
	   ShowError(TEXT("Error al convertir en .mp3"));   
	   return false;
	 }
	 
	 DeleteFile(strTmpFile);   
     SetText(hWnd,IDC_TEXT,TEXT("Accion: Terminado"));
     s.SetText(TEXT("Conversion finalizada"));   
    }
    else{ 
     ShowError(TEXT("Error al convertir en .wav"));
	 return false;
	}
   }
   
  }

  if(inf.iOutput==WAV){
   for(short i=0;i<Tracks.size();i++){
	strTrack=GetWavPath();
	
	switch(GetOutPut()){
	  case 0: 
		     strTrack+="\\Track";	 
	         if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);
	         strTrack+=".wav";
		     break;
	  case 1:
			 strTrack+="\\";
			 strTrack+=cdinf.GetArtist().c_str();
			 strTrack+="-Track";
			 if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);			 			 
			 strTrack+=".wav";
			 
		     break;
	  case 2:
			 strTrack+="\\";
			 strTrack+=cdinf.GetArtist().c_str();
			 strTrack+="-";
			 strTrack+=cdinf.GetAlbum().c_str();
             strTrack+="-Track";
			 if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);            
			 strTrack+=".wav";
		     break;
	  case 3:
		     strTrack+="\\";
		     strTrack+=cdinf.GetArtist().c_str();
			 strTrack+="-Track";
			 if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);
			 strTrack+=".wav";
		     break;
	  case 4:strTrack+="\\";
		     strTrack+=cdinf.GetGenre().c_str();
			 strTrack+="-";
			 strTrack+=cdinf.GetArtist().c_str();
			 strTrack+="-Track";
			 if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);
			 strTrack+=".wav";
		     break;
	  case 5:strTrack+="\\";
		     strTrack+=cdinf.GetGenre().c_str();		
			 strTrack+="-Track";
			 if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);
			 strTrack+=".wav";
		     break;
	  case 6:strTrack+="\\";
		     strTrack+=cdinf.Get_Year().c_str();
			 strTrack+="-";
			 strTrack+=cdinf.GetGenre().c_str();			 
			 strTrack+="-Track";
			 if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);
			 strTrack+=".wav";
		     break;
	  case 7:strTrack+="\\";
		     strTrack+=cdinf.Get_Year().c_str();
			 strTrack+="-";
			 strTrack+=cdinf.GetArtist().c_str();
             strTrack+="-Track";
			 if((Tracks[i]+1) < 10)
	          strTrack+="0";

	         strTrack+=ToString(Tracks[i]+1);			 			 
			 strTrack+=".wav";
		     break;


	}
	 MessageBox(NULL,strTrack.c_str(),"",MB_OK);
    SetText(hWnd,IDC_TEXT,TEXT("Accion: Convirtiendo Track%02d.cda a Track%02d.wav"),Tracks[i]+1,Tracks[i]+1);
    if(!c.CdaToWav(inf.cDrive,Tracks[i]+1,strTrack)){
     ShowError(TEXT("Error al convertir en .wav"));	
	 return false;
    }
	SetText(hWnd,IDC_TEXT,TEXT("Accion: Terminado"));
    s.SetText(TEXT("Conversion finalizada"));
		
   }      
  }
  c.DisplayTime("Hora Final: ");
 }
 else{
  ShowInformation(TEXT("Selecciona un track para realizar la conversion")); 
  return false;
 }

 return true;
}

void CApplication::Extract()
{
 BOOL bCheck;
 Tracks.clear();
 for(short i=0;i<m_iNumTracks;i++){
	bCheck=lv.GetCheck(i);
	if(bCheck)
     Tracks.push_back(i);
 }				   
 m_iDrive=cb1.GetCurSel();
 c.SetDrive(m_iDrive);

 inf.cDrive=cDrive[m_iDrive];
 inf.iOutput= (cb2.GetCurSel() == 0) ? MP3 : WAV;

}
void CApplication::OnInit()
{
 RECT r;
 m_hMenu=GetMenu(GetHWND());			 
 s.CreateStatusBar(IDC_STATUSBAR); 			 
 t.CreateToolBar(IDC_TOOLBAR); 
 GenerateImageList();			 
 t.AddButton(ID_TOOLBAR_EXTRACT,0,TEXT("Extraer"));			 
 t.AddButton(ID_TOOLBAR_UPDATE,1,TEXT("Actualizar"));
 t.AddSeparator();
 t.AddButton(ID_TOOLBAR_SETTINGS,2,TEXT("Opciones"));
 t.AddButton(ID_TOOLBAR_ABOUT,3,TEXT("Acerca de"));
 t.AddSeparator(); 
 cb1.Create(320,1,280,20,ID_COMBO_DRIVE );            
 SetDrive();					 
 SetParent(cb1.GetHwndComboBox(),t.GetHWNDToolBar());
 cb2.Create(610,1,80,20,ID_COMBO_OUTPUT);			 
 cb2.AddText(TEXT("MP3"));
 cb2.AddText(TEXT("WAV"));
 cb2.SetCurSel();
 SetParent(cb2.GetHwndComboBox(),t.GetHWNDToolBar());			              
 GetClientRect(GetHWND(),&r);
 lv.Create(r.right/2-200,t.GetHeight(),r.right,r.bottom-s.GetHeight()-t.GetHeight(),IDC_LISTVIEW);
 lv.SetCombo();				 			 			 						 
 lv.AddColumn(TEXT("#"),50,0);
 lv.AddColumn(TEXT("Titulo"),150,1);
 lv.AddColumn(TEXT("Longitud"),100,2);
 lv.AddColumn(TEXT("Tamaño"),90,3);		
 m_iDrive=cb1.GetCurSel();			 
 if(c.Init(GetHWND()))
  m_iNumTracks=SetTracks(m_iDrive);
 else{
  ShowError("Error al iniciar BASS");
  exit(1);
 }
				 
 Center();
}

void CApplication::OnSize(int iWidth,int iHeight)
{
  RECT r;
  t.AutoSize();
  s.AutoSize();			 
  GetClientRect(GetHWND(),&r);			 			
  lv.AutoSize(r.right/2-200,t.GetHeight(),r.right,r.bottom-s.GetHeight()-t.GetHeight());
}

int CApplication::SetTracks(int iDrive)
{
 short i;
 TCHAR strText[20];
 
 c.SetDrive(iDrive);
 m_iNumTracks=c.GetNumTracks();			 
 
 if(m_iNumTracks >= 0){
    for(i=m_iNumTracks; i >= 1; i--){
      wsprintf(strText,TEXT("%02d"),i);  
	  lv.AddItem(strText,0,0);			  
	}
	for(i=0; i < m_iNumTracks; i++){
       wsprintf(strText,TEXT("Track%02d.cda"),i+1); 
	   lv.AddSubItem(strText,i,1);			  
	   wsprintf(strText,TEXT("%02d:%02d"),c.GetMinutes(i),c.GetSeconds(i));       
	   lv.AddSubItem(strText,i,2);
	   sprintf(strText,TEXT("%d MB"),c.GetLength(i));
	   lv.AddSubItem(strText,i,3);
	}
	EnableMenuItem(m_hMenu,ID_ACTION_EXTRACT,MF_ENABLED);
	EnableMenuItem(m_hMenu,ID_EDIT_SELECTALL,MF_ENABLED);
	EnableMenuItem(m_hMenu,ID_EDIT_SELECTNONE,MF_ENABLED);
	EnableMenuItem(m_hMenu,ID_ACTION_EJECT,MF_ENABLED);
	EnableMenuItem(m_hMenu,ID_TOOL_SETTINGS,MF_ENABLED);
	EnableMenuItem(m_hMenu,ID_TOOL_INFCD,MF_ENABLED);
	EnableWindow(GetDlgItem(p.GetHWND(),IDC_PLAY),TRUE);
    EnableWindow(GetDlgItem(p.GetHWND(),IDC_STOP),TRUE);
    EnableWindow(GetDlgItem(p.GetHWND(),IDC_NEXT),TRUE);
    EnableWindow(GetDlgItem(p.GetHWND(),IDC_PREV),TRUE);
    EnableWindow(GetDlgItem(p.GetHWND(),IDC_EJECT),TRUE);
	t.Enable(TRUE,ID_TOOLBAR_EXTRACT);
	t.Enable(TRUE,ID_TOOLBAR_SETTINGS);
	s.SetText(TEXT("CD Listo - Para reproducir un track del cd audio dar doble clic sobre el track seleccionado"));
	
 }
 else{
	EnableMenuItem(m_hMenu,ID_ACTION_EXTRACT,MF_GRAYED);
	EnableMenuItem(m_hMenu,ID_EDIT_SELECTALL,MF_GRAYED);
	EnableMenuItem(m_hMenu,ID_EDIT_SELECTNONE,MF_GRAYED);
    EnableMenuItem(m_hMenu,ID_ACTION_EJECT,MF_GRAYED);
	EnableMenuItem(m_hMenu,ID_TOOL_SETTINGS,MF_GRAYED);
	EnableMenuItem(m_hMenu,ID_TOOL_INFCD,MF_GRAYED);
	EnableWindow(GetDlgItem(p.GetHWND(),IDC_PLAY),FALSE);
    EnableWindow(GetDlgItem(p.GetHWND(),IDC_STOP),FALSE);
    EnableWindow(GetDlgItem(p.GetHWND(),IDC_NEXT),FALSE);
    EnableWindow(GetDlgItem(p.GetHWND(),IDC_PREV),FALSE);
    EnableWindow(GetDlgItem(p.GetHWND(),IDC_EJECT),FALSE);
	t.Enable(FALSE,ID_TOOLBAR_EXTRACT);
	t.Enable(FALSE,ID_TOOLBAR_SETTINGS);
	m_iNumTracks=0;
	s.SetText("Introduzca un CD Audio - Presione el boton de Actualizar");
 }

 
 return m_iNumTracks;
}

int CApplication::Update2(int iDrive)
{ 
 lv.DeleteAllItems();
 m_iNumTracks=SetTracks(iDrive); 
 return m_iNumTracks;
}

void CApplication::ChangeText(bool bFlag,UINT uID)
{
 if(bFlag)     
  ModifyMenu(m_hMenu,uID,MF_BYCOMMAND,uID,TEXT("Cerrar CD-ROM"));         
 else
  ModifyMenu(m_hMenu,uID,MF_BYCOMMAND,uID,TEXT("Expulsar CD-ROM")); 
}

void CApplication::SetDrive()
{
 int a=0;
 const char *n=NULL;
 
 cDrive.clear();
 while (a<MAXDRIVES && (n=BASS_CD_GetDriveDescription(a))) {
	 char text[100];
	 sprintf(text,"%c: %s",BASS_CD_GetDriveLetter(a)+'A',n); 	 
	 cb1.AddText(text);
	 cDrive.push_back(tolower(text[0]));
	 a++;
 }
 if(!a){	
	ShowError(TEXT("No se encontro drive de CD"));
	Close();
 }
 cb1.SetCurSel();
}

void CApplication::GenerateImageList()
{
 #define CX_ICON  16 
 #define CY_ICON  16 
 #define MAX 4

 HIMAGELIST hImglBtn;
 HICON hIcon;
 
 
 long lStyle = GetWindowLong(t.GetHWNDToolBar(), GWL_STYLE );
 lStyle |= TBSTYLE_FLAT;
 SetWindowLong(t.GetHWNDToolBar(), GWL_STYLE, lStyle );

 hImglBtn = ImageList_Create(CX_ICON, CY_ICON, ILC_COLORDDB|ILC_MASK, MAX, 0);
 hIcon = (HICON)LoadImage (GetInstance(), MAKEINTRESOURCE (IDI_ICON2), IMAGE_ICON, CX_ICON, CY_ICON, LR_DEFAULTCOLOR);
 if(hIcon){
  if (-1 == ImageList_AddIcon (hImglBtn, hIcon)) 
    DestroyIcon(hIcon);
 }
 SendMessage(t.GetHWNDToolBar(), TB_SETIMAGELIST, (WPARAM)0, (WPARAM)hImglBtn);
 
 hIcon = (HICON)LoadImage (GetInstance(), MAKEINTRESOURCE (IDI_ICON3), IMAGE_ICON, CX_ICON, CY_ICON, LR_DEFAULTCOLOR);
 if(hIcon){
  if (-1 == ImageList_AddIcon (hImglBtn, hIcon)) 
    DestroyIcon(hIcon);
 } 
 SendMessage(t.GetHWNDToolBar(), TB_SETIMAGELIST, (WPARAM)0, (WPARAM)hImglBtn);
 
 hIcon = (HICON)LoadImage (GetInstance(), MAKEINTRESOURCE (IDI_ICON4), IMAGE_ICON, CX_ICON, CY_ICON, LR_DEFAULTCOLOR);
 if(hIcon){
  if (-1 == ImageList_AddIcon (hImglBtn, hIcon)) 
    DestroyIcon(hIcon);
 } 
 SendMessage(t.GetHWNDToolBar(), TB_SETIMAGELIST, (WPARAM)0, (WPARAM)hImglBtn);
 
 hIcon = (HICON)LoadImage (GetInstance(), MAKEINTRESOURCE (IDI_ICON5), IMAGE_ICON, CX_ICON, CY_ICON, LR_DEFAULTCOLOR);
 if(hIcon){
  if (-1 == ImageList_AddIcon (hImglBtn, hIcon)) 
    DestroyIcon(hIcon);
 } 
 SendMessage(t.GetHWNDToolBar(), TB_SETIMAGELIST, (WPARAM)0, (WPARAM)hImglBtn); 
}

void CApplication::OnDestroy()
{
 lv.Destroy();
 t.Destroy();
 cb1.Destroy();
 cb2.Destroy();
 c.p.Destroy();
 s.Destroy();
 c.Close();
 Destroy();
}
