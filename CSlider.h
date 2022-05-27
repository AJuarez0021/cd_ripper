#ifndef __CSLIDER_H
#define __CSLIDER_H

#include <windows.h>
#include <commctrl.h> 

class CSlider{
private:
 HWND m_hWnd; 
 HWND m_hSlider;
public:
	CSlider(HWND hWnd=NULL){
     m_hWnd=hWnd;	 
	 m_hSlider=NULL;
	 INITCOMMONCONTROLSEX iccx;
     iccx.dwSize=sizeof(INITCOMMONCONTROLSEX);
     iccx.dwICC=ICC_PROGRESS_CLASS;
     InitCommonControlsEx(&iccx);

	}
	void SetHWND(HWND hWnd){
     m_hWnd=hWnd;
	}
    void AutoSize(int x,int y,int iWidth,int iHeight){
     MoveWindow(m_hSlider,x,y,iWidth,iHeight,TRUE);
	}
	bool Create(int x,int y,int iWidth,int iHeight,const int id)
	{
	 m_hSlider=CreateWindowEx(0,                  
                      TRACKBAR_CLASS,     
                      0,                 
                      WS_CHILD|WS_VISIBLE|TBS_AUTOTICKS,          
                      x,            
                      y,             
                      iWidth,          
                      iHeight,          
                      m_hWnd,                                  
                      reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),
                      reinterpret_cast<HINSTANCE>(GetModuleHandle(NULL)),              
                      0);              
	 if(!m_hSlider)
	  return false;

     return true;
	}
	int GetPos(){
      return SendMessage(m_hSlider, TBM_GETPOS, 0, 0); 
	}
	int GetPos(int nID){
      return SendMessage(GetDlgItem(m_hWnd,nID), TBM_GETPOS, 0, 0);
	}
	void SetPos(int iValue){
      SendMessage(m_hSlider, TBM_SETPOS, (WPARAM) TRUE, (LPARAM) iValue); 
	}
	void SetPos(int nID,int iValue){
      SendMessage(GetDlgItem(m_hWnd,nID), TBM_SETPOS, (WPARAM) TRUE, (LPARAM) iValue);
	}
	void SetRange(int iMin,int iMax){
      SendMessage(m_hSlider, TBM_SETRANGE, (WPARAM) TRUE,(LPARAM) MAKELONG(iMin, iMax));  
	}
	void SetRange(int nID,int iMin,int iMax){
      SendMessage(GetDlgItem(m_hWnd,nID), TBM_SETRANGE, (WPARAM) TRUE,(LPARAM) MAKELONG(iMin, iMax));  
	}
	void SetRangeMax(int nID,int iMax){
      SendMessage(GetDlgItem(m_hWnd,nID), TBM_SETRANGEMAX, (WPARAM)FALSE,(LPARAM)iMax);
	}
	void SetStart(int iStart){
       SendMessage(m_hSlider, TBM_SETSELSTART, (WPARAM) TRUE,(LPARAM)iStart);
	}
	void SetEnd(int iEnd){
       SendMessage(m_hSlider, TBM_SETSELEND, (WPARAM) TRUE,(LPARAM)iEnd);
	}
	void SetSliderFocus(){
     SetFocus(m_hSlider);
	}
};

#endif