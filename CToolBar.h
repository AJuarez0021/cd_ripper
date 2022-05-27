#ifndef __CTOOLBAR_H
#define __CTOOLBAR_H

#include <windows.h>
#include <commctrl.h>
#define ID_TOOLBAR_EXTRACT     1
#define ID_TOOLBAR_UPDATE      2
#define ID_TOOLBAR_SETTINGS    3
#define ID_TOOLBAR_ABOUT       4

class CToolBar
{

private:
	HWND m_hToolBar;
	HWND m_hWnd;
    RECT rcTool;
public:
	 TBBUTTON tbb;
     CToolBar(HWND hWnd=NULL){ 
	  INITCOMMONCONTROLSEX iccx;
	  iccx.dwSize=sizeof(INITCOMMONCONTROLSEX);
      iccx.dwICC=ICC_BAR_CLASSES;
      InitCommonControlsEx(&iccx);
	  m_hToolBar=NULL;
	  m_hWnd=hWnd;
	 }
	~CToolBar(){ }
	void SetHWND(HWND hWnd){
      m_hWnd=hWnd;
	}
	bool CreateToolBar(const int id);
	void AddButton(int nID,int iBitmap,char* Text);
	void AddButtonExt(int nID,int iBitmap,char* Text);
	void AddSeparator();
	void Destroy(){ 
		DestroyWindow(m_hToolBar); 
	}
	void Update(){
     UpdateWindow(m_hToolBar);
	}
    void Enable(BOOL bEnable,UINT uID);
	void AutoSize();
	int GetHeight();
	HWND GetHWNDToolBar(){ 
		return m_hToolBar; 
	}
	void OnNotify(LPARAM lParam);
};
#endif