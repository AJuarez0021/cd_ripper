#ifndef __CLISTBOX_H
#define __CLISTBOX_H
#include <windows.h>

class CListBox{
private:
  HWND m_hWnd;
public:
	CListBox(HWND hWnd=NULL){
      m_hWnd=hWnd;
	}
	void AddString(UINT nID,LPCSTR strText){
     SendDlgItemMessage(m_hWnd,nID, LB_ADDSTRING,   (WPARAM)0,(LPARAM)strText);
	}
	void SelectString(UINT nID,LPSTR strText){
     SendDlgItemMessage(m_hWnd,nID, LB_SELECTSTRING,(WPARAM)-1,(LPARAM)strText);
	}
	void SetListFocus(UINT nID){
      SetFocus(GetDlgItem(m_hWnd,nID));
	}
	int GetCurSel(UINT nID){
	 return SendDlgItemMessage(m_hWnd,nID, LB_GETCURSEL, 0, 0);
	}
	void GetText(UINT nID,int nIndice,LPSTR strBuffer){
      SendDlgItemMessage(m_hWnd,nID, LB_GETTEXT,nIndice, (LPARAM)strBuffer);
	}
	int GetTextLength(UINT nID,int nIndex){
     return SendDlgItemMessage(m_hWnd,nID,LB_GETTEXTLEN,(WPARAM)nIndex,(LPARAM)0);
	}
    void ResetContent(UINT nID){ 
		SendDlgItemMessage(m_hWnd,nID,LB_RESETCONTENT,(WPARAM)0,(LPARAM)0);
	}
	int GetCont(UINT nID){
        return SendDlgItemMessage(m_hWnd,nID,LB_GETCOUNT,(WPARAM)0,(LPARAM)0);
	}
};
#endif