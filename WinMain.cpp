//CDRipper Version 1.0
//Programa que permite convertir de 
//.CDA (CD Audio) a .WAV
//.CDA (CD Audio) a .MP3
//Programa compilado con Visual C++ 6.0
//http://programacioncpp.irandohosting.0lx.net
#include "CPanel.h"

#pragma comment(lib,"comctl32.lib")

CApplication app;
CPanel p;
CCDInformation cdinf;


int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPreInst,LPSTR lpszCmdLine,int nCmdShow)

{
    HWND hWnd;               
    MSG Mensaje;            
    WNDCLASSEX ClaseVentana;        
    TCHAR NombreClase[]   = TEXT("MiClaseVentana");   
	
	ClaseVentana.cbSize = sizeof (WNDCLASSEX);
	ClaseVentana.style = CS_HREDRAW | CS_VREDRAW;
	ClaseVentana.lpfnWndProc = WndProc; 
	ClaseVentana.cbClsExtra = 0;                      
    ClaseVentana.cbWndExtra = 0; 
	ClaseVentana.hInstance = hInst;
    ClaseVentana.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
    ClaseVentana.hCursor = LoadCursor (NULL, IDC_ARROW);
	ClaseVentana.hbrBackground = reinterpret_cast<HBRUSH> (COLOR_BTNFACE+1);	
	ClaseVentana.lpszMenuName = NULL; 
    ClaseVentana.lpszClassName = NombreClase;
	ClaseVentana.hIconSm = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
		
    
  
    if (!RegisterClassEx (&ClaseVentana))
        return 0;

    
    hWnd = CreateWindowEx (
           0,                   
           NombreClase,         
           TEXT("CD Ripper Version 1.0"),       
           WS_MINIMIZEBOX | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
           CW_USEDEFAULT,      
           CW_USEDEFAULT,       
           750,                 
           450,                 
           NULL,       
           LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU1)),                
           hInst,       
           NULL                 
           );

    if(!hWnd) 
	 return 0;
	
    ShowWindow (hWnd, SW_SHOW);
    UpdateWindow(hWnd);
	
    HWND hDlg=CreateDialog(app.GetInstance(),MAKEINTRESOURCE(IDD_PANEL),hWnd,(DLGPROC)CDProc);
	p.SetHDLG(hDlg);
	p.ShowPanel();
    while (GetMessage (&Mensaje, NULL, 0, 0))
    {        
		if(hDlg == 0 || !IsDialogMessage(hDlg,&Mensaje)){
         TranslateMessage(&Mensaje);
         DispatchMessage(&Mensaje);
		}
    }

    return Mensaje.wParam;
}



LRESULT CALLBACK ConverterProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
 CTimer t;
 static int iMin=0,iSec=0,iHour=0;
 switch(uMsg)
 {
	case WM_INITDIALOG:			 		 		 
		 app.c.InitProgressBar(hWnd,IDC_PROGRESS1,RGB(125,125,125));
		 EnableWindow(GetDlgItem(hWnd,ID_PROGRESS_OK),TRUE);
		 app.SetText(hWnd,IDC_STATIC_PROGRESS_TIME,"");
		 app.SetDlgIcon(IDI_ICON1,hWnd);
	     return 0;
	case WM_CLOSE:
		 EndDialog(hWnd,0);			 
	     return 0;	
    case WM_COMMAND:
		 switch(LOWORD(wParam))
		 {
		   case ID_PROGRESS_OK:				    				
			    t.Start();
				 
				SetCursor(LoadCursor((HINSTANCE) GetWindowLong( hWnd, GWL_HINSTANCE ),MAKEINTRESOURCE(IDC_CURSOR)));			
			    EnableWindow(GetDlgItem(hWnd,ID_PROGRESS_OK),FALSE);														
				if(app.Converter(hWnd)){
				 SetCursor(LoadCursor(NULL,IDC_ARROW));
				 t.Stop();
				 iSec=t.GetElapsed();
				 if(iSec >= 60){
				  iMin=iSec / 60;
				  iSec=iSec % 60;
				 }
				 if(iMin >= 60){
                  iHour=iMin/60;
				  iMin= iMin%60;
				 }
				 app.SetText(hWnd,IDC_STATIC_PROGRESS_TIME,TEXT("Tiempo transcurrido: %02d:%02d:%02d"),iHour,iMin,iSec);			
			     if(SendDlgItemMessage(hWnd,IDC_CHECK_DETAILS, BM_GETCHECK, 0, 0) == BST_CHECKED)
				  DialogBox(app.GetInstance(),MAKEINTRESOURCE(IDD_LOG),hWnd,(DLGPROC)LogProc);
				}
			    break;
		   case ID_PROGRESS_CANCEL:			  
			    EndDialog(hWnd,0);
			    break;
		 }
		 return 0;
	case WM_DESTROY:		 
         return 0;
	default:
		 return 0;
	
 }
 return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK AboutProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
 HYPCTRL hc;
 RECT r;
 switch(uMsg){
  case WM_INITDIALOG:
	    app.SetDlgIcon(IDI_ICON1,hWnd);
	    GetClientRect(hWnd,&r);
	    InitHypCtrl(&hc);
		hc.ulStyle	 = ulHover;
		hc.szLink	 = TEXT("http://www.programacioncpp.irandohosting.0lx.net/");
		hc.szTooltip = TEXT("Visitar pagina Web");
		CreateHypCtrl(hWnd, &hc,r.bottom/2-68,r.bottom-70, 0, 0);		
	    break;
  case WM_COMMAND:
	   switch(LOWORD(wParam)){
	     case ID_ABOUT_OK:
			  EndDialog(hWnd,0);
			  break;

	   }
	   break;
  case WM_CLOSE:
	   EndDialog(hWnd,0);
	   break;
  default: 
	   return 0;

 }
 return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK CDInformationProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
  
  
  switch(uMsg){
    case WM_INITDIALOG:
		 app.SetDlgIcon(IDI_ICON1,hWnd);
		 cdinf.SetInfHWND(hWnd);
		 cdinf.SetInformation();		
		 break;
	case WM_COMMAND:
	     switch(LOWORD(wParam)){
		  case ID_INF_OK:
			   cdinf.ReadInformation();
			   EndDialog(hWnd,0);
			   break;
		  case ID_INF_CANCEL:
			   EndDialog(hWnd,0);
			   break;
		 }
		 break;
	case WM_CLOSE:		 		
		 EndDialog(hWnd,0);
		 break;
	default:
		 return 0;
  }
 return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


bool Export(string strFileName)
{
 ofstream out(strFileName.c_str());
 string strLine;
 string strFile=app.GetWinDirectory().c_str();
 strFile+="\\";
 strFile+="audio_converter.log";
 ifstream in(strFile.c_str());
 CTime t;
 if(in.fail()){
  app.ShowError("Error el archivo " + strFile + " no se pudo abrir para lectura");
  return false;
 }
 if(out.fail()){
  app.ShowError("Error el archivo " + strFileName + " no se pudo crear");
  return false;
 }
 out << "<html>" << endl;
 out << "<head>" << endl;
 out << "<title>" << endl;
 out << "Archivo .log de CD Ripper" << endl;
 out << "</title>" << endl;
 out << "</head>" << endl;
 out << "<body>" << endl; 
 out << "<center>" << endl;
 out << "<br><br>";
 out << "Hora: " << setw(2) << setfill('0') << t.GetHour()   << ":"; 
 out << setw(2) << setfill('0') << t.GetMinute() << ":"; 
 out << setw(2) << setfill('0') << t.GetSecond() << endl;
 out << "<br>";
 out << "Fecha: "  << t.GetDayWeek().c_str() << ", " << setw(2) << setfill('0') << t.GetDay() << " de " 
	 << t.GetStringMonth().c_str() << " de " << t.GetYear() << endl;
 out << "</center>" << endl;
 out << "<p align=\"justify\">" << endl;
 

 while(!in.eof()){
  getline(in,strLine);
  out << "<br>" << strLine.c_str() << endl;
 }
 out << "</p>" << endl;
 out << "<br><br><center>Archivo generado por <b>CD Ripper 1.0</b></center>" << endl;
 out << "</body>" << endl;
 out << "</html>" << endl;
 in.close();
 out.close();
 return true;
}
LRESULT CALLBACK LogProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
 CListBox l(hWnd);
 string strText;
 string strFile=app.GetWinDirectory().c_str();
 strFile+="\\";
 strFile+="audio_converter.log";
 ifstream in(strFile.c_str());
 switch(uMsg){
   case WM_INITDIALOG:
	     app.SetDlgIcon(IDI_ICON1,hWnd);
		 EnableWindow(GetDlgItem(hWnd,ID_LOG_EXPORT),TRUE);
	     if(in.fail()){
          app.ShowError("Error el archivo audio_converter.log no existe");
		  EndDialog(hWnd,1);
		 }
		 while(!in.eof()){
		  getline(in,strText);		
		  l.AddString(IDC_LIST_LOG,strText.c_str());
		 }
		 in.close();
		 l.SetListFocus(IDC_LIST_LOG);
	    break;
   case WM_COMMAND:
	     switch(LOWORD(wParam)){
		   case ID_LOG_EXPORT:
			    if(app.Save(hWnd,"Archivos .html *.html\0","Guardar")){
				 if(Export(app.GetFile())){				  
				  EnableWindow(GetDlgItem(hWnd,ID_LOG_EXPORT),FALSE);
				  app.ShowInformation("Se ha exportado el archivo correctamente");
				 }
				}
			    break;
		   case ID_LOG_CANCEL:
			    EndDialog(hWnd,0);
			    break;
		 }
		 break;
   case WM_CLOSE:	    
	    EndDialog(hWnd,0);
	    break;
   default:
	    return 0;
 }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
LRESULT CALLBACK SettingsProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
 CComboBox c(hWnd,IDC_COMBO_OUTPUT);
 switch(uMsg){
  case WM_INITDIALOG:	   	   
	   app.SetDlgIcon(IDI_ICON1,hWnd);  	   
	   c.AddText("<titulo>");	   
	   c.AddText("<artista><titulo>");
	   c.AddText("<artista><album><titulo>");
	   c.AddText("<artista><titulo>");
	   c.AddText("<genero><artista><titulo>");
	   c.AddText("<genero><titulo>");
	   c.AddText("<año><genero><titulo>");
	   c.AddText("<año><artista><titulo>");
	   app.OnInitConverter(hWnd,c);
	   break;
  case WM_COMMAND:
	   switch(LOWORD(wParam)){
	     case IDC_MP3OUTPUT_OPEN:			  
			  app.OpenMp3(hWnd);
			  break;
		 case IDC_WAVOUTPUT_OPEN:			 
			  app.OpenWav(hWnd);
			  break;
	     case ID_SETTINGS_OK:
			  app.WriteConfig(hWnd,c);			  
			  break;
		 case ID_SETTINGS_CANCEL:
			  EndDialog(hWnd,0);
			  break;

	   }
	   break;
  case WM_CLOSE:
	   EndDialog(hWnd,0);
	   break;
  default: 
	   return 0;

 }
 return DefWindowProc(hWnd, uMsg, wParam, lParam);
}





LRESULT CALLBACK CDProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
  RECT rc;
  SetRectEmpty(&rc);
  static CToolTip t(hWnd);
		
  switch(uMsg){
   case WM_INITDIALOG:		    	    
	    t.Create(rc.left,rc.top,rc.right,rc.bottom,0);
		t.SetToolTip(GetDlgItem(hWnd,IDC_PLAY),TEXT("Reproducir/Pausar un track"));
		t.SetToolTip(GetDlgItem(hWnd,IDC_STOP),TEXT("Detiene el track"));
		t.SetToolTip(GetDlgItem(hWnd,IDC_NEXT),TEXT("Track siguiente"));
		t.SetToolTip(GetDlgItem(hWnd,IDC_PREV),TEXT("Track anterior"));
		t.SetToolTip(GetDlgItem(hWnd,IDC_EJECT),TEXT("Expulsa el cd audio"));
		t.SetToolTip(GetDlgItem(hWnd,IDC_SLIDER_POSITION),TEXT("Posicion del track actual"));
		t.SetToolTip(GetDlgItem(hWnd,IDC_SLIDER_VOL),TEXT("Volumen"));
	    t.SetToolTip(GetDlgItem(hWnd,IDC_SLIDER_PANEO),TEXT("Paneo"));		
	    p.OnInit(hWnd);			
	    break;
   case WM_TIMER:
	    p.OnTimer(hWnd);
	    break;
   case WM_HSCROLL:
	    p.SetPositionCD(p.s.GetPos(IDC_SLIDER_POSITION));
        break;
   case WM_VSCROLL:
	   if(GetDlgCtrlID(GetDlgItem(hWnd,IDC_SLIDER_VOL))==IDC_SLIDER_VOL){
		  t.SetToolTip(GetDlgItem(hWnd,IDC_SLIDER_VOL),(char*)app.ToString(100-p.s2.GetPos(IDC_SLIDER_VOL)).c_str());
		  p.SetVolumeCD(p.s2.GetPos(IDC_SLIDER_VOL));	
	   }
		if(GetDlgCtrlID(GetDlgItem(hWnd,IDC_SLIDER_PANEO))==IDC_SLIDER_PANEO){
		  t.SetToolTip(GetDlgItem(hWnd,IDC_SLIDER_PANEO),(char*)app.ToString(100-p.s3.GetPos(IDC_SLIDER_PANEO)).c_str());
		  p.SetPaneoCD(p.s3.GetPos(IDC_SLIDER_PANEO));
		 
		}
	    break;
   case WM_COMMAND:
	    switch(LOWORD(wParam)){
		  case IDC_PLAY:			   			   
			   p.Play();			  
			   break;		 			   			   
		  case IDC_STOP:
			   p.Stop(hWnd);
			   break;
		  case IDC_NEXT:
			   p.Next();
			   break;
		  case IDC_PREV:
			   p.Prev();
			   break;
		  case IDC_EJECT:
			   if(p.IsPlaying())
			    p.StopCD();

			   p.Eject();
			   app.UpdateCD();
			   break;
		}
	    break;
   case WM_DESTROY:	 	    
	    p.OnDestroy(hWnd);
	    break;
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{		
	static bool bEject=false;

    switch (uMsg)                  
    {
	    case WM_CREATE:			
			 app.Set_HWND(hWnd);
			 app.OnInit();					 
			 p.SetMainHWND(hWnd);			
			 SetTimer(hWnd,2,1000,NULL);			 
			 return 0;	
		case WM_TIMER:
			 if(app.c.GetCurrentDrive() != app.cb1.GetCurSel())				
               app.UpdateCD();	
			 
			 return 0;
		case WM_NOTIFY:
			 app.t.OnNotify(lParam);
			 return p.OnNotify(hWnd,(LPNMHDR)lParam);			 
		case WM_COMMAND:
			 switch(LOWORD(wParam)){			  
			  case ID_FILE_EXIT:				  
				   app.Close();
				   break;
			  case ID_EDIT_SELECTALL:
				   app.SelectAll();				   
				   break;
			  case ID_EDIT_SELECTNONE:
				   app.SelectNone();                  
				   break;	
			  case ID_TOOL_MP3OUTPUTFOLDER:
				   app.ReadConfig();
				   ShellExecute(hWnd,"open",NULL,NULL,app.GetMp3Path(),SW_SHOW);
				   break;
			  case ID_TOOL_WAVOUTPUTFOLDER:
				   app.ReadConfig();
				   ShellExecute(hWnd,"open",NULL,NULL,app.GetWavPath(),SW_SHOW);
				   break;
			  case ID_TOOL_INFCD:
				   DialogBox(app.GetInstance(),MAKEINTRESOURCE(IDD_CD_INFORMATION),hWnd,(DLGPROC)CDInformationProc);
				   break;
			  case ID_TOOLBAR_SETTINGS:
			  case ID_TOOL_SETTINGS:
				   DialogBox(app.GetInstance(),MAKEINTRESOURCE(IDD_SETTINGS),hWnd,(DLGPROC)SettingsProc);
				   break;
			  case ID_TOOLBAR_UPDATE:
			  case ID_ACTION_UPDATE:
				   app.UpdateCD();				   				   				  
				   break;
			  case ID_ACTION_EJECT:
				   if(p.IsPlaying())
					p.StopCD();
				   bEject=!bEject;
				   app.Eject(bEject);	
				   app.UpdateCD();
				   break;
			  case ID_TOOLBAR_ABOUT:
			  case ID_HELP_ABOUT:
				   DialogBox(app.GetInstance(),MAKEINTRESOURCE(IDD_ABOUT),hWnd,(DLGPROC)AboutProc);
				   break;
			  case ID_TOOLBAR_EXTRACT:
			  case ID_ACTION_EXTRACT:
				   p.Stop(p.GetHWND());
				   app.Extract();					 
				   DialogBox(app.GetInstance(),MAKEINTRESOURCE(IDD_PROGRESS),hWnd,(DLGPROC)ConverterProc);
				   break;
			 }
			 return 0;
		case WM_SIZE:	        				 			 		 			
			 return 0;
		
        case WM_CLOSE:
        case WM_DESTROY:
			{
			 KillTimer(hWnd,2);
			 string strFile=app.GetWinDirectory().c_str();
             strFile+="\\";
             strFile+="audio_converter.log";
			 DeleteFile(strFile.c_str());
			 app.OnDestroy();
             PostQuitMessage(0);       
			}
             return 0;
        default:                      
             return DefWindowProc (hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

