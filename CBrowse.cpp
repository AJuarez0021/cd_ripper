#include "CBrowse.h"

TCHAR* CBrowse::GetFolderName() const
{
	return m_selectedFolder;
}


bool CBrowse::Browse(TCHAR* strTitle)
{
 BROWSEINFO bi;
 ZeroMemory(&bi, sizeof(BROWSEINFO));
 TCHAR strBuffer[MAX_PATH];
 bi.hwndOwner      = m_hWnd;
 bi.pidlRoot       = 0;
 bi.pszDisplayName = strBuffer;
 bi.lpszTitle      = strTitle;
 bi.ulFlags        = BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS; 
 bi.lParam         = 0;


 LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
 if (pidl != 0){  
  SHGetPathFromIDList(pidl, strBuffer);  
  m_selectedFolder = strBuffer;
 }
 return (lstrlen(m_selectedFolder) > 0) ? true : false;
}