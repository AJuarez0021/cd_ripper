#include <windows.h>
#include <commctrl.h> 

class CProgressBar
{
private:
 HWND m_hwndProgress;

public:
	CProgressBar(){
      m_hwndProgress=NULL;
	  INITCOMMONCONTROLSEX iccx;
      iccx.dwSize=sizeof(INITCOMMONCONTROLSEX);
      iccx.dwICC=ICC_PROGRESS_CLASS;    
      InitCommonControlsEx(&iccx);
	}
 
 void SetValueProgressBar(int Value);
 void ResizeProgressBar(int x,int y,int iWidth,int iHeight);
 void ReinitProgressBar();
 void Destroy(){
  DestroyWindow(m_hwndProgress);
 }
 void Update(){
  UpdateWindow(m_hwndProgress);
 }
 void SetRangeProgressBar(int init,int end);
 void SetRange32ProgressBar(int init,int end);
 void SetStepProgressBar(int iStep);
 void SetBarColorProgressBar(COLORREF Color);
 void SetWNDProgressBar(HWND hWndProgress,UINT uID){ 
	  m_hwndProgress = GetDlgItem(hWndProgress,uID); 
 }
};