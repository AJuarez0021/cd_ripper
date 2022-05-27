#include <windows.h>

class CToolTip{
private:
 HWND m_hWnd;
 HWND m_hToolTip;
public:
 CToolTip(HWND hWnd=NULL){
  m_hWnd=hWnd;
 }
 void SetHWND(HWND hWnd){
  m_hWnd=hWnd;
 }
 bool Create(int x,int y,int iWidth,int iHeight,const int id){
  m_hToolTip=CreateWindowEx(0,                  
                      TOOLTIPS_CLASS,  
                      TEXT(""),    
                      TTS_ALWAYSTIP,           
                      x,            
                      y,             
                      iWidth,           
                      iHeight,          
                      m_hWnd,            
                      reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),
                      GetModuleHandle(NULL),              
                      0);               
  if(!m_hToolTip)
   return false;

  return true;
 }
 
 HWND GetHWNDToolTip() const{
   return m_hToolTip;
 }

 void SetToolTip(HWND hWnd,char* strText){
  static TOOLINFO ti;
  memset(&ti,0,sizeof(ti));
  ti.cbSize=sizeof(ti);
  ti.uFlags=TTF_IDISHWND|TTF_SUBCLASS;
  ti.uId=(UINT_PTR)hWnd;
  ti.lpszText=strText;
  ti.hwnd=m_hWnd;  
  SendMessage(m_hToolTip,TTM_ADDTOOL,0, reinterpret_cast<LPARAM>(&ti));
 }
};