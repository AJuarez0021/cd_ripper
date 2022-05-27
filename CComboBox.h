#ifndef __CCOMBOBOX_H
#define __CCOMBOBOX_H

#include <windows.h>

class CComboBox
{
private:
 HWND m_hWnd,m_hCombo;
public:
 CComboBox(HWND hWnd=NULL){
  m_hWnd=hWnd;
  m_hCombo=NULL;
 }
 CComboBox(HWND hWnd,int nID){
  m_hWnd=hWnd;
  m_hCombo=GetDlgItem(hWnd,nID);
 }
 void SetHWND(HWND hWnd){
  m_hWnd=hWnd;
 }

 void SetHWND(HWND hWnd,int nID){
  m_hWnd=hWnd;
  m_hCombo=GetDlgItem(hWnd,nID);
 }
 bool CComboBox::Create(int x,int y,int cx,int cy,const int id)
 {
  m_hCombo=CreateWindowEx(0,
			                      TEXT("COMBOBOX"),
								  0,WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST,
								  x,y,
								  cx,cy,m_hWnd, 
								  reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),
								  reinterpret_cast<HINSTANCE>(GetModuleHandle(NULL)),
								  0);

  
  if(!m_hCombo)
   return false;

  return true;
 }
 void Destroy(){
   DestroyWindow(m_hCombo);	 
 }
 void Update(){
   UpdateWindow(m_hCombo);
 }
 void AddText(const char* strText){
  SendMessage(m_hCombo,CB_ADDSTRING,(WPARAM)0,(LPARAM)strText);
 }
 void SetCurSel(int nIndex=0){
  SendMessage(m_hCombo,CB_SETCURSEL,(WPARAM)nIndex,0);
 }
 HWND GetHwndComboBox(){
  return m_hCombo;
 }
 int GetCurSel(){
  return (int)SendMessage(m_hCombo,CB_GETCURSEL,0,0);
 }
};

#endif