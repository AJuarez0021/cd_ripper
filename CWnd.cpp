#include "CWnd.h"


void CWnd::Center()
{
 RECT r;	
 RECT ScreenRect;
 GetClientRect(m_hWnd,&r);
 int m_Width	= r.right;
 int m_Height	= r.bottom;

	
 GetWindowRect (GetDesktopWindow(), &ScreenRect);
 SetWindowPos (m_hWnd, HWND_TOP, 
		       (((ScreenRect.right + ScreenRect.left) / 2) - (m_Width / 2)),
			   (((ScreenRect.bottom + ScreenRect.top) / 2) - (m_Height / 2)),
			    0, 
				0, 
				SWP_NOCOPYBITS | SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
}

void CWnd::SetDlgIcon(UINT nIDIcon,HWND hWnd)

{
 HICON hIcon;
 HINSTANCE hInst;
 hInst = (HINSTANCE) GetWindowLong( hWnd, GWL_HINSTANCE );
 hIcon=LoadIcon(hInst,MAKEINTRESOURCE(nIDIcon));
 SendMessage(hWnd,WM_SETICON,ICON_BIG, (LPARAM) hIcon);
 SendMessage(hWnd,WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
}

BOOL CWnd::Save(HWND hWnd, LPSTR lpszFiltro, LPSTR lpszTitulo)
{
	static  OPENFILENAME  ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = (lpszFiltro);
	ofn.lpstrFile = m_strFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = (lpszTitulo);	
	ofn.lpstrDefExt = "html";	
	ofn.Flags = OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY;
	return GetSaveFileName (&ofn);	
}