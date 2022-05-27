#ifndef __CBROWSE_H
#define __CBROWSE_H

#include <windows.h>
#include <shlobj.h>


class CBrowse
{
private:
 TCHAR* m_selectedFolder;
 
 HWND m_hWnd;
public:
 CBrowse(HWND hWnd=NULL){
  m_selectedFolder=NULL;  
  m_hWnd=hWnd;
 }
 void SetHWND(HWND hWnd){
   m_hWnd=hWnd;
 }
 bool Browse(TCHAR* strTitle);
 TCHAR* GetFolderName() const;
 
};
#endif