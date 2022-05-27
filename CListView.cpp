#include "CListView.h"

bool CListView::Create(int x,int y,int iWidth,int iHeight,const int id)
{
  m_hList = CreateWindowEx(WS_EX_CLIENTEDGE, 
	                       WC_LISTVIEW, TEXT(""), 
						   WS_CHILD | WS_VISIBLE|WS_BORDER |LVS_SHOWSELALWAYS|LVS_SINGLESEL| LVS_REPORT, 
						   x,y,          
						   iWidth,iHeight, 
						   m_hWnd, 
						   reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),
		                   reinterpret_cast<HINSTANCE>(GetModuleHandle(NULL)),
						   NULL);
  if(!m_hList)
   return false;

  return true;
}

void CListView::AddColumn(char* lpszTexto, int nAncho, int nIndice)
{
	LV_COLUMN   lvCol;      
	lvCol.cchTextMax = sizeof(lpszTexto);
	lvCol.pszText = lpszTexto;
	lvCol.mask = LVCF_TEXT|LVCF_WIDTH;
	lvCol.cx = nAncho;
	ListView_InsertColumn(m_hList, nIndice, &lvCol);
}

void CListView::SetItem(int iItem)
{
 ListView_SetItemState(m_hList,iItem,LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED); 
}
void CListView::AddItem(const char* strText, int nIndice, int nIndiceImagen)
{
    static LV_ITEM     lvItem; 
	lstrcpy(Text,strText);
	lvItem.pszText = Text; 
	lvItem.cchTextMax = sizeof(Text);
	lvItem.mask = LVIF_TEXT|LVIF_IMAGE; 
	lvItem.iItem = nIndice; 
	lvItem.iImage = nIndiceImagen;
	ListView_InsertItem(m_hList, &lvItem);
	ListView_Update(m_hList, nIndice);
	
}
void CListView::AddSubItem(const char* strText,int nIndiceItem, int nIndiceSubItem)
{
	LV_ITEM     lv;
    lstrcpy(Text,strText);
	lv.iSubItem = nIndiceSubItem;
	lv.pszText = Text;
	lv.cchTextMax=sizeof(Text);	
	SendMessage(m_hList, LVM_SETITEMTEXT, (WPARAM) (int) nIndiceItem, (LPARAM) (LV_ITEM FAR *) &lv);
}



void CListView::AutoSize(int x,int y,int iWidth,int iHeight)
{ 
 MoveWindow(m_hList,x,y,iWidth,iHeight,TRUE); 
}

