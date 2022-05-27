#ifndef __CSTATUSBAR_H
#define __CSTATUSBAR_H

#include <windows.h>

class CStatusBar
{
private:
 HWND m_hStatus;
 HWND m_hWnd;
 RECT rcStatus;
public:
 CStatusBar(HWND hWnd=NULL){ 
	m_hStatus=NULL; 
	m_hWnd=hWnd;
 }
 void SetHWND(HWND hWnd){
  m_hWnd=hWnd;
 }
 bool CreateStatusBar(const int id);
 void Destroy(){
  DestroyWindow(m_hStatus);
 }
 void Update(){
  UpdateWindow(m_hStatus);
 }
 void SetText(const char* strText);
 void SetParts(int *StatWidths);
 void AutoSize();
 int GetHeight();
 HWND GetHwndStatus(){
  return m_hStatus;
 }
};

#endif