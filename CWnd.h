#ifndef __CWND_H
#define __CWND_H

#include <windows.h> 
#include <cstdio>
#include <string>
class CWnd
{
protected:

private:
   HWND m_hWnd;
   char m_strBuffer[512];
   std::string m_strPath;
   char m_strFile[MAX_PATH];
   char strPath[MAX_PATH];
public:
 CWnd(HWND hWnd=NULL){
  m_hWnd=hWnd;
  memset(m_strBuffer,0,sizeof(m_strBuffer));
  memset(m_strFile,0,sizeof(m_strFile));  
 }
 
 virtual void SetHWND(HWND hWnd){
  m_hWnd=hWnd;
 }
 HWND GetHWND() const{
  return m_hWnd;
 }
 HINSTANCE GetInstance() const{
   return (HINSTANCE)GetModuleHandle(NULL);
 }
 void Center();

 std::string GetWinDirectory(){
  
  GetWindowsDirectory(strPath,MAX_PATH);
  m_strPath=strPath;
  return m_strPath;
 }
 void Close(){
  SendMessage(m_hWnd,WM_CLOSE,0,0);
 }
 virtual void Update(){
  UpdateWindow(m_hWnd);
 }
 void Destroy(){
  DestroyWindow(m_hWnd);
 }
 void ShowError(std::string strMsg){
  MessageBox(m_hWnd,strMsg.c_str(),TEXT("CD Ripper"),MB_ICONERROR);
 }
 void ShowInformation(std::string strMsg){
  MessageBox(m_hWnd,strMsg.c_str(),TEXT("CD Ripper"),MB_ICONINFORMATION);
 }

 void SetText(int nID,char* strText,...){
     va_list v;
	 va_start(v,strText);
	 vsprintf(m_strBuffer,strText,v);
	 va_end (v);
	 SetDlgItemText(m_hWnd,nID,m_strBuffer);
 }

 void SetText(HWND hWnd,int nID,char* strText,...){
     va_list v;
	 va_start(v,strText);
	 vsprintf(m_strBuffer,strText,v);
	 va_end (v);
	 SetDlgItemText(hWnd,nID,m_strBuffer);
 }
 void SetDlgIcon(UINT nIDIcon,HWND hWnd);
 BOOL Save(HWND hWnd, LPSTR lpszFiltro, LPSTR lpszTitulo);
 char* GetFile(){
   return m_strFile;
 }
};
#endif