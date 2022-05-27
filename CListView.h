#ifndef __CLISTVIEW_H
#define __CLISTVIEW_H

#include <windows.h>
#include <commctrl.h> 

class CListView
{
private:
 HWND m_hWnd;
 HWND m_hList;
 TCHAR Text[512];
public:
 CListView(HWND hWnd=NULL){
  m_hWnd=hWnd;
  m_hList=NULL;
  INITCOMMONCONTROLSEX icex; 
  icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
  icex.dwICC  = ICC_LISTVIEW_CLASSES;
  InitCommonControlsEx(&icex);   
 }
 void SetHWND(HWND hWnd){
  m_hWnd=hWnd;
 }
 HWND GetHwndLV(){
  return m_hList;
 }
 
 void SetGrid(){
  SendMessage(m_hList, LVM_SETEXTENDEDLISTVIEWSTYLE,0,(LPARAM)LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
 }
 void SetCombo(){
  ListView_SetExtendedListViewStyleEx(m_hList,0,LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
 }
 ;
 bool Create(int x,int y,int iWidth,int iHeight,const int id);
 void AutoSize(int x,int y,int iWidth,int iHeight);
 void Destroy(){
  DestroyWindow(m_hList);
 }
 void Update(){
  UpdateWindow(m_hList);
 }
 void SetCheck(int iIndex,BOOL bCheck){  
  ListView_SetItemState(m_hList,iIndex,INDEXTOSTATEIMAGEMASK((bCheck)?2:1),LVIS_STATEIMAGEMASK);
 }
 BOOL GetCheck(int iIndex){
  return ListView_GetCheckState(m_hList,iIndex);
 }
 void AddColumn(char* lpszTexto, int nAncho, int nIndice);
 void AddItem(const char* strText, int nIndice, int nIndiceImagen);
 void AddSubItem(const char* strText,int nIndiceItem, int nIndiceSubItem);
 void DeleteAllItems(){ ListView_DeleteAllItems(m_hList); }
 int  GetItem(){ 
   return ListView_GetNextItem(m_hList,-1,LVNI_SELECTED); 
 }
 void DeleteItem(int iItem){
   ListView_DeleteItem(m_hList,iItem);	
 }
 void SetItem(int iItem);

};

#endif