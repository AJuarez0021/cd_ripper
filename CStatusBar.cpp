#include "CStatusBar.h"
#include <commctrl.h>

int CStatusBar::GetHeight()
{

 GetWindowRect(m_hStatus, &rcStatus);
 return rcStatus.bottom - rcStatus.top;
}


void CStatusBar::AutoSize()
{
 SendMessage(m_hStatus, WM_SIZE, 0, 0);
}

void CStatusBar::SetParts(int *StatWidths)
{
 SendMessage(m_hStatus, SB_SETPARTS, sizeof(StatWidths)/sizeof(int), (LPARAM)StatWidths);
}

bool CStatusBar::CreateStatusBar(const int id)
{
 m_hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL,
		  WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
		  m_hWnd, 
		  reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),
		  reinterpret_cast<HINSTANCE>(GetModuleHandle(NULL)),		   
		  0);
 if(!m_hStatus)
  return false;

 return true;
}


void CStatusBar::SetText(const char* strText)
{
 SendMessage(m_hStatus, SB_SETTEXT, (WPARAM) 0 | 0, (LPARAM) strText);
}