#include "CListView.h"
#include "CAudioConverter.h"
#include "resource.h"
#include "CStatusBar.h"
#include "CToolBar.h"
#include "CComboBox.h"
#include "hyperlink.h"
#include "CWnd.h"
#include "CBrowse.h"
#include "CSlider.h"
#include "CButton.h"
#include "CStringConverter.h"
#include "CListBox.h"
#include "CTime.h"
#include <direct.h>


#define ID_COMBO_DRIVE         5
#define ID_COMBO_OUTPUT        6
#define IDC_LISTVIEW           10
#define IDC_TOOLBAR            11
#define IDC_STATUSBAR          12
#define MAXDRIVES 10
#define MP3 0
#define WAV 1



class CApplication : public CWnd, public CStringConverter{
private:
 HMENU m_hMenu;
 
 int   m_iDrive;
 vector<int>  Tracks;
 vector<char> cDrive; 
 void SetDrive();
 void GenerateImageList();
 void ChangeText(bool bFlag,UINT uID);
 int  SetTracks(int iDrive);
 int  Update2(int iDrive);
 char m_strMp3[MAX_PATH];
 char m_strWav[MAX_PATH];
 int  m_output;
public:
 CListView       lv;		
 CToolBar        t;
 CComboBox       cb1,cb2;
 CStatusBar      s;
 CAudioConverter c;
 CBrowse         b;
 int   m_iNumTracks;
 CApplication(HWND hWnd=NULL) : CWnd(hWnd){
  t.SetHWND(hWnd);
  lv.SetHWND(hWnd);
  cb1.SetHWND(hWnd);
  cb2.SetHWND(hWnd); 
  s.SetHWND(hWnd);
  b.SetHWND(hWnd);
  GetCurrentDirectory(MAX_PATH,m_strMp3);
  GetCurrentDirectory(MAX_PATH,m_strWav);
  m_output=0;
  m_iNumTracks=0;
 }
 void Set_HWND(HWND hWnd){
  t.SetHWND(hWnd);
  lv.SetHWND(hWnd);
  cb1.SetHWND(hWnd);
  cb2.SetHWND(hWnd);
  s.SetHWND(hWnd);
  b.SetHWND(hWnd);
  SetHWND(hWnd);
 } 
 char* GetMp3Path(){
  return m_strMp3;
 }

 char* GetWavPath(){
  return m_strWav;
 }
 int GetOutPut(){
   return m_output;
 }
 char GetDrive(){
   return static_cast<char>(_getdrive() + 'A' - 1);   
 }
 void  UpdateCD(){
  m_iDrive=cb1.GetCurSel();
  m_iNumTracks=Update2(m_iDrive);	
 }
 void Extract();
 void OnSize(int iWidth,int iHeight);
 void OnInit();
 void OnDestroy();
 void SelectAll(){
  for(short i=0;i<m_iNumTracks;i++)
	lv.SetCheck(i,TRUE);
 }
 void SelectNone(){
  for(short i=0;i<m_iNumTracks;i++)
   lv.SetCheck(i,FALSE);
 }
 void Eject(bool bEject){  				   
  if(c.IsOpen())
   c.EjectCD(false);
  else
   c.EjectCD(true);
  ChangeText(bEject,ID_ACTION_EJECT);
 }

 void OnInitConverter(HWND hWnd,CComboBox c);
 bool Converter(HWND hWnd);
 void ReadConfig();
 void WriteConfig(HWND hWnd,CComboBox c);
 void OpenMp3(HWND hWnd);
 void OpenWav(HWND hWnd);
};

extern CApplication app;

class CCDInformation : public CTime, public CComboBox{
private:
 HWND m_hWnd; 
 string m_strArtist;
 string m_strAlbum;
 string m_strYear;
 string m_strGenre;
 int m_iGenre;
public:

 
 string GetArtist() const{
  return m_strArtist;
 }
 int  GetGenre2() const{
  return m_iGenre;
 }
 string GetGenre() const{
  return m_strGenre;
 }

 string GetAlbum() const{
  return m_strAlbum;
 }
 string Get_Year() const{
  return  m_strYear;
 }

 CCDInformation(){
   m_strArtist="Unknown";
   m_strAlbum="Unknown";  
   m_strYear=app.ToString(GetYear()).c_str();
   m_strGenre="other";
   m_iGenre=0;
   m_hWnd=NULL;
 }
 CCDInformation(HWND hWnd) : CComboBox(hWnd,IDC_COMBO_GENRE)
 {
  m_hWnd=hWnd;

 }
 void SetInfHWND(HWND hWnd){
  SetHWND(hWnd,IDC_COMBO_GENRE);
  m_hWnd=hWnd;
 }
 void SetInformation(){
   SetDlgItemText(m_hWnd,IDC_EDIT_ARTIST,GetArtist().c_str());
   SetDlgItemText(m_hWnd,IDC_EDIT_ALBUM,GetAlbum().c_str());
   SetDlgItemText(m_hWnd,IDC_EDIT_YEAR,Get_Year().c_str());
   AddText("other");
   AddText("classical");
   AddText("metal");
   AddText("rock");
   AddText("soundtrack");
   AddText("country");
   AddText("folk");
   AddText("jazz");
   AddText("newage");
   AddText("reggae");   
   SetCurSel(GetGenre2());
   SendDlgItemMessage(m_hWnd, IDC_EDIT_ARTIST, EM_LIMITTEXT, 39, 0L);
   SendDlgItemMessage(m_hWnd, IDC_EDIT_ALBUM, EM_LIMITTEXT, 39, 0L);
   SendDlgItemMessage(m_hWnd, IDC_EDIT_YEAR, EM_LIMITTEXT, 4, 0L);
 }
 void ReadInformation(){
   char strArtist[40];
   char strYear[6];
   char strAlbum[40];
   
   GetDlgItemText(m_hWnd,IDC_EDIT_ARTIST,strArtist,39);
   GetDlgItemText(m_hWnd,IDC_EDIT_ALBUM,strAlbum,39);
   GetDlgItemText(m_hWnd,IDC_EDIT_YEAR,strYear,5);
   int iArtistLength=GetWindowTextLength(GetDlgItem(m_hWnd,IDC_EDIT_ARTIST));
   int iAlbumLength=GetWindowTextLength(GetDlgItem(m_hWnd,IDC_EDIT_ALBUM));
   int iYearLength=GetWindowTextLength(GetDlgItem(m_hWnd,IDC_EDIT_YEAR));
   if(iArtistLength > 0)
    m_strArtist=strArtist;
   else{
	app.ShowError("Error la longitud de la cadena artista es incorrecta");
	EndDialog(m_hWnd,0);
   }
   
   if(iAlbumLength > 0)
    m_strAlbum=strAlbum;
   else{
    app.ShowError("Error la longitud de la cadena album es incorrecta");
	EndDialog(m_hWnd,0);
   }

   if(iYearLength == 4)
    m_strYear=strYear;
   else{
    app.ShowError("Error la longitud de la cadena año es incorrecta\nFormato: YYYY");
	EndDialog(m_hWnd,0);
   }
   m_iGenre=GetCurSel();
   switch(m_iGenre){
     case 1: m_strGenre="classical";
		     break;
	 case 2: m_strGenre="metal";
		     break;
	 case 3: m_strGenre="rock";
		     break;
	 case 4: m_strGenre="soundtrack";
		     break;
	 case 5: m_strGenre="country";
		     break;
	 case 6: m_strGenre="folk";
		     break;
	 case 7: m_strGenre="jazz";
		     break;
	 case 8: m_strGenre="newage";
		     break;
	 case 9: m_strGenre="reggae";
		     break;
	 case 0: m_strGenre="other";
		     break;

   }
 }
};