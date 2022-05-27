#include "CProgressBar.h"

void CProgressBar::SetValueProgressBar(int iValue)
{
 SendMessage(m_hwndProgress,PBM_SETPOS,iValue,0);
}

void CProgressBar::SetRange32ProgressBar(int init,int end)
{
 SendMessage(m_hwndProgress,PBM_SETRANGE32,(WPARAM)init,(LPARAM)end);
}
void CProgressBar::ResizeProgressBar(int x,int y,int iWidth,int iHeight)
{
 MoveWindow(m_hwndProgress,x,y,iWidth,iHeight,TRUE);
}

void CProgressBar::ReinitProgressBar()
{
 SendMessage(m_hwndProgress, PBM_SETPOS, (WPARAM) 0 , 0);
}


void CProgressBar::SetRangeProgressBar(int init,int end)
{

 SendMessage(m_hwndProgress, PBM_SETRANGE, 0, MAKELPARAM(init, end));
}

void CProgressBar::SetStepProgressBar(int iStep)
{
 SendMessage(m_hwndProgress, PBM_SETSTEP, (WPARAM) iStep, 0);         
}


void CProgressBar::SetBarColorProgressBar(COLORREF Color)
{
				 
 SendMessage(m_hwndProgress, PBM_SETBARCOLOR, 0, (LPARAM) Color);
}
