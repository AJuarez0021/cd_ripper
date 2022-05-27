#include "CToolBar.h"
#include "resource.h"

void CToolBar::OnNotify(LPARAM lParam)
{
	switch (((LPNMHDR) lParam)->code)
	{
       case TTN_GETDISPINFO: 
			{ 
               LPTOOLTIPTEXT lpttt; 
			   lpttt = (LPTOOLTIPTEXT) lParam; 
			   lpttt->hinst = (HINSTANCE)GetModuleHandle(NULL); 
			   switch(lpttt->hdr.idFrom){			    
			     case ID_TOOLBAR_EXTRACT:
					  lpttt->lpszText=TEXT("Extraer un track del CD Audio");
					  break;
				 case ID_TOOLBAR_UPDATE:
					  lpttt->lpszText=TEXT("Actualizar CD Audio");
					  break;
				 case ID_TOOLBAR_SETTINGS:
					  lpttt->lpszText=TEXT("Opciones de salida");
					  break;
				 case ID_TOOLBAR_ABOUT:
					  lpttt->lpszText=TEXT("Muestra informacion del autor del programa");
					  break;
				 
			   }
			}
			break;
   }
}

void CToolBar::Enable(BOOL bEnable,UINT uID)
{
 SendMessage(m_hToolBar,TB_ENABLEBUTTON,uID,MAKELONG(bEnable, 0));
}

int CToolBar::GetHeight()
{
  GetWindowRect(m_hToolBar, &rcTool);

 return rcTool.bottom - rcTool.top;
}


bool CToolBar::CreateToolBar(const int id)
{
  m_hToolBar=CreateWindowEx(0,      
                            TOOLBARCLASSNAME,             
                            NULL,                         
                            WS_CHILD | WS_VISIBLE |TBSTYLE_TOOLTIPS|TBSTYLE_LIST,                           
                            0,                           
                            0,                            
                            0,                           
                            0,                            
                            m_hWnd,                        
                            reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),
		                     reinterpret_cast<HINSTANCE>(GetModuleHandle(NULL)),                      
                            NULL);                        

 
  if(!m_hToolBar)
   return false;


  SendMessage(m_hToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
  
  return true;

}

void CToolBar::AddButton(int nID,int iBitmap,char *Text)
{
	                   
	        TBADDBITMAP tbab;		  
			tbab.hInst = HINST_COMMCTRL;
			tbab.nID = IDB_STD_SMALL_COLOR;
			SendMessage(m_hToolBar, TB_ADDBITMAP, 0, (LPARAM)&tbab);				
			tbb.iBitmap=iBitmap;			
			tbb.fsState= TBSTATE_ENABLED;
			tbb.fsStyle=TBSTYLE_BUTTON; 
			tbb.idCommand=nID;  
			tbb.iString=(Text!=NULL) ? (int)TEXT(Text) : 0; 	
			SendMessage(m_hToolBar, TB_ADDBUTTONS,sizeof(tbb)/sizeof(TBBUTTON), (LPARAM)&tbb);
								
}

void CToolBar::AddButtonExt(int nID,int iBitmap,char *Text)
{
  TBADDBITMAP tbab;	


  tbab.hInst = HINST_COMMCTRL;
  tbab.nID = IDB_STD_SMALL_COLOR;
  SendMessage(m_hToolBar, TB_ADDBITMAP, 0, (LPARAM)&tbab);	
  
  tbb.iBitmap=iBitmap;			
  tbb.fsState= TBSTATE_ENABLED;
  tbb.fsStyle=TBSTYLE_DROPDOWN;
  tbb.idCommand=nID;  
  tbb.iString=(Text!=NULL) ? (int)TEXT(Text) : 0; 	
  
  SendMessage(m_hToolBar,TB_SETEXTENDEDSTYLE,(WPARAM)0,(LPARAM)TBSTYLE_EX_DRAWDDARROWS);
  SendMessage(m_hToolBar, TB_ADDBUTTONS,sizeof(tbb)/sizeof(TBBUTTON), (LPARAM)&tbb);
}

void CToolBar::AddSeparator()
{
 tbb.iBitmap=0;
 tbb.idCommand=-1;
 tbb.fsState=TBSTATE_ENABLED;
 tbb.fsStyle=TBSTYLE_SEP;	
 tbb.dwData=0;
 tbb.iString=0;
 SendMessage(m_hToolBar, TB_ADDBUTTONS,sizeof(tbb)/sizeof(TBBUTTON), (LPARAM)&tbb);

}


void CToolBar::AutoSize()
{
 SendMessage(m_hToolBar, TB_AUTOSIZE, 0, 0); 
}
