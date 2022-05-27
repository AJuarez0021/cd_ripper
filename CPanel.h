#include "CApplication.h"
#include "CToolTip.h"

extern CApplication app;

LRESULT CALLBACK WndProc      (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ConverterProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK AboutProc    (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CDProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK LogProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
class CPanel : public CCda{
private:
 HWND m_hDlg;
 HWND m_hWnd;
 HWND m_hWnd2;
 bool bPause;
public:
	CButton  b,b2,b3,b4,b5;
	CSlider  s,s2,s3;
	CProgressBar p1,p2;
	CPanel(HWND hWnd=NULL){		
	 m_hWnd=hWnd;	 
	 m_hDlg=NULL;
	 bPause=true;
	}
	void SetMainHWND(HWND hWnd){
     m_hWnd=hWnd;
	}
	void SetHWND(HWND hWnd){
	 m_hWnd2=hWnd;
	}
	void SetHDLG(HWND hDlg){
     m_hDlg=hDlg;
	}
	HWND GetHWND(){
     return m_hWnd2;
	}
	void ShowPanel(){	            	 
     ShowWindow(m_hDlg,SW_SHOW);
	}
	void HidePanel(){
     ShowWindow(m_hDlg,SW_HIDE);
	}
	void OnInit(HWND);    	
	void OnDestroy(HWND hWnd){
	 Free();
	 BASS_Free();
     KillTimer(hWnd,1);
	}
	void OnTimer(HWND);
	void Play();
	void Stop(HWND);	
    LRESULT OnNotify( HWND hWnd, NMHDR* pnmhdr);
	void Eject();
	void Next();
	void Prev();
      	
};