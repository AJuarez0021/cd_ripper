#ifndef __CBUTTON_H
#define __CBUTTON_H

#include <windows.h>

class CButton{

private:
 HWND m_hButton,m_hWnd;
public:
 CButton(HWND hWnd=NULL){
  m_hWnd=hWnd;
 }
 enum Type{BITMAP,ICON};

 void SetHWND(HWND hWnd){
  m_hWnd=hWnd;
 }
 bool Create(int x,int y,int iWidth,int iHeight,Type t,const int id){
  
  DWORD dwStyle;

  if(t==ICON)
   dwStyle=WS_CHILD | WS_VISIBLE | BS_ICON;
  else
   dwStyle=WS_CHILD | WS_VISIBLE | BS_BITMAP;

  m_hButton=CreateWindow (         TEXT("button"), 
                                   TEXT(""),
                                   dwStyle,
                                   x, y,
                                   iWidth,iHeight,
                                   m_hWnd, 
								   reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),
                                   reinterpret_cast<HINSTANCE>(GetModuleHandle(NULL)), 
								   NULL) ;

  if(!m_hButton)
   return false;

  return true;
 }

 void SetBitmapButton(int nIDImage){
  HBITMAP hBmp=reinterpret_cast<HBITMAP>(LoadImage(0,MAKEINTRESOURCE(nIDImage),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR));
  SendMessage(m_hButton,BM_SETIMAGE,IMAGE_BITMAP,reinterpret_cast<LPARAM>(hBmp));
 }
 void SetIconButton(int nIDImage){
  HICON hIcon=reinterpret_cast<HICON>(LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(nIDImage),IMAGE_ICON,GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),LR_DEFAULTCOLOR)); 
  SendMessage(m_hButton,BM_SETIMAGE,IMAGE_ICON,reinterpret_cast<LPARAM>(hIcon));
 }
 void SetBitmapButton(int nIDButton,int nIDImage){
  HBITMAP hBmp=reinterpret_cast<HBITMAP>(LoadImage(0,MAKEINTRESOURCE(nIDImage),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR));
  SendMessage(GetDlgItem(m_hWnd,nIDButton),BM_SETIMAGE,IMAGE_BITMAP,reinterpret_cast<LPARAM>(hBmp));
 }

 void SetIconButton(int nIDButton,int nIDImage){
  HICON hIcon=reinterpret_cast<HICON>(LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(nIDImage),IMAGE_ICON,GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),LR_DEFAULTCOLOR));
  SendMessage(GetDlgItem(m_hWnd,nIDButton),BM_SETIMAGE,IMAGE_ICON,reinterpret_cast<LPARAM>(hIcon));
  //SendMessage(GetDlgItem(m_hWnd,nIDButton),BM_SETIMAGE,IMAGE_ICON,(LPARAM)(HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(nIDImage),IMAGE_ICON,GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),LR_DEFAULTCOLOR));
 }
 void AutoSize(int x,int y,int iWidth,int iHeight){
  MoveWindow(m_hButton,x,y,iWidth,iHeight,TRUE);
 }
};

#endif