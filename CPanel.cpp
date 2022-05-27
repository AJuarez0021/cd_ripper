#include "CPanel.h"



void CPanel::Next()
{
 int iTrack=GetTrack();
 iTrack++;
 if(iTrack >= 0 && iTrack<= GetNumTracks()){
  PlayCD(iTrack);
  app.lv.SetItem(iTrack);
 } 
}
void CPanel::Prev()
{
 int iTrack=GetTrack();
 iTrack--;
 if(iTrack >= 0){
  PlayCD(iTrack);
  app.lv.SetItem(iTrack);
 }
 
 
}
void CPanel::OnInit(HWND hWnd)
{
 b.SetHWND(hWnd);
 b2.SetHWND(hWnd);
 b3.SetHWND(hWnd);
 b4.SetHWND(hWnd);
 b5.SetHWND(hWnd);
 s.SetHWND(hWnd);
 s2.SetHWND(hWnd);
 s3.SetHWND(hWnd);
 SetHWND(hWnd);
 p1.SetWNDProgressBar(hWnd,IDC_PROGRESS_LEVEL1);
 p2.SetWNDProgressBar(hWnd,IDC_PROGRESS_LEVEL2);
 p1.SetRange32ProgressBar(0,30000);
 p2.SetRange32ProgressBar(0,30000);
 s3.SetRange(IDC_SLIDER_PANEO,0,100);
 s3.SetPos(IDC_SLIDER_PANEO,50);
 b.SetIconButton(IDC_PLAY,IDI_ICON8);
 b2.SetIconButton(IDC_STOP,IDI_ICON9);
 b3.SetIconButton(IDC_EJECT,IDI_ICON10);
 b4.SetIconButton(IDC_NEXT,IDI_ICON12);
 b5.SetIconButton(IDC_PREV,IDI_ICON11);
 EnableWindow(GetDlgItem(hWnd,IDC_SLIDER_POSITION),FALSE);
 EnableWindow(GetDlgItem(hWnd,IDC_SLIDER_VOL),FALSE);
 EnableWindow(GetDlgItem(hWnd,IDC_SLIDER_PANEO),FALSE);
 if(app.m_iNumTracks > 0){
  EnableWindow(GetDlgItem(hWnd,IDC_PLAY),TRUE);
  EnableWindow(GetDlgItem(hWnd,IDC_STOP),TRUE);
  EnableWindow(GetDlgItem(hWnd,IDC_NEXT),TRUE);
  EnableWindow(GetDlgItem(hWnd,IDC_PREV),TRUE);
  EnableWindow(GetDlgItem(hWnd,IDC_EJECT),TRUE);
 }
 else{
  EnableWindow(GetDlgItem(hWnd,IDC_PLAY),FALSE);
  EnableWindow(GetDlgItem(hWnd,IDC_STOP),FALSE);
  EnableWindow(GetDlgItem(hWnd,IDC_NEXT),FALSE);
  EnableWindow(GetDlgItem(hWnd,IDC_PREV),FALSE);  
  EnableWindow(GetDlgItem(hWnd,IDC_EJECT),FALSE);
 }
 if(!BASS_Init(-1,44100,0,hWnd,NULL)){
  app.ShowError("Error al iniciar BASS");
  exit(1);
 }
 SetTimer(hWnd,1,50,NULL);
}

void CPanel::Eject()
{
 p1.ReinitProgressBar();
 p2.ReinitProgressBar();
 if(IsOpen())
  EjectCD(false);
 else
  EjectCD(true);
}
void CPanel::Stop(HWND hWnd)
{
 StopCD();
 b.SetIconButton(IDC_PLAY,IDI_ICON8);
 s.SetPos(IDC_SLIDER_POSITION,0);
 s3.SetPos(IDC_SLIDER_PANEO,50); 
 p1.ReinitProgressBar();
 p2.ReinitProgressBar();
 app.SetText(hWnd,IDC_STATIC_TIME,TEXT("Tiempo:"));
 app.SetText(hWnd,IDC_STATIC_TRACK,TEXT("Numero de Track:"));
}

void CPanel::Play()
{
  
  if(IsPlaying())
  {
     PauseCD();
	 b.SetIconButton(IDC_PLAY,IDI_ICON8);
	 EnableWindow(GetDlgItem(GetHWND(),IDC_SLIDER_POSITION),FALSE);
  }
  else
  {	 
	 PlayCD();
	 if(IsActive()){
	  b.SetIconButton(IDC_PLAY,IDI_ICON7);
	  EnableWindow(GetDlgItem(GetHWND(),IDC_SLIDER_POSITION),TRUE);
	 }
  }	  
}

void CPanel::OnTimer(HWND hWnd)
{

  if(IsActive()){ 
	      static int levl=0,levr=0;
		  int level=GetLevel();
		  levl-=1500; if (levl<0) levl=0;
		  levr-=1500; if (levr<0) levr=0;
		  if (level!=-1) {
			if (levl<LOWORD(level)) levl=LOWORD(level);
			if (levr<HIWORD(level)) levr=HIWORD(level);
		  }
          p1.SetValueProgressBar(levl);
		  p2.SetValueProgressBar(levr);
	      app.SetText(hWnd,IDC_STATIC_TIME,TEXT("Tiempo: %02d:%02d-%02d:%02d"),GetCurrentMinutes(),GetCurrentSeconds(),GetMinutes(GetTrack()),GetSeconds(GetTrack()));
		  app.SetText(hWnd,IDC_STATIC_TRACK,TEXT("Numero de Track: %02d-%02d"),GetTrack()+1,GetNumTracks());		  
		 
		  s.SetPos(IDC_SLIDER_POSITION,GetCurrentPosition());		  
		 
		  
  }
 
}




LRESULT CPanel::OnNotify( HWND hWnd, NMHDR* pnmhdr)
{
    LRESULT lrt = FALSE;
	NMLVDISPINFO* plvdi = (NMLVDISPINFO*) pnmhdr;
	int iTrack;
    switch (pnmhdr->code){
	   case NM_DBLCLK:
		    iTrack=app.lv.GetItem();
				
			if(iTrack!=-1){
			 app.lv.SetItem(iTrack);
			 Stop(GetHWND());
			 SetDrive(app.cb1.GetCurSel());				
			 PlayCD(iTrack);
			 EnableWindow(GetDlgItem(GetHWND(),IDC_SLIDER_POSITION),TRUE);
			 EnableWindow(GetDlgItem(GetHWND(),IDC_SLIDER_VOL),TRUE);
             EnableWindow(GetDlgItem(GetHWND(),IDC_SLIDER_PANEO),TRUE);
			 s.SetRangeMax(IDC_SLIDER_POSITION,GetLength());
			 b.SetIconButton(IDC_PLAY,IDI_ICON7);
			 app.s.SetText("Reproduciendo CD Audio");
			}
			lrt=FALSE;
		    break;
        default:
			break;
	}
	return lrt;
}


