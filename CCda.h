#include <windows.h>
#include "bass\basscd.h"
#include <vector>



void CALLBACK EndSync(HSYNC handle, DWORD channel, DWORD data, DWORD user);


class CCda{
private:
 HSTREAM m_Stream[10]; 
 int m_CurDrive;
public:
 
 CCda(){
  m_CurDrive=0; 
  memset(&m_Stream,0,sizeof(m_Stream));
 }

 ~CCda(){   
	
 }

 void Free(){
  BASS_StreamFree(m_Stream[m_CurDrive]);
 }
 void SetDrive(DWORD dwDrive){
  m_CurDrive=dwDrive;
 }
 int GetCurrentDrive(){
  return m_CurDrive;
 }
 void StreamCreate(DWORD dwTrack=0){
  m_Stream[m_CurDrive]=BASS_CD_StreamCreate(m_CurDrive,dwTrack,0);
 }
 void PlayCD(DWORD dwTrack){  
   if (m_Stream[m_CurDrive])
    BASS_CD_StreamSetTrack(m_Stream[m_CurDrive],dwTrack); 
   else{
    m_Stream[m_CurDrive]=BASS_CD_StreamCreate(m_CurDrive,dwTrack,0);
	BASS_ChannelSetSync(m_Stream[m_CurDrive],BASS_SYNC_END,0,&EndSync,0); 
   }

  BASS_ChannelPlay(m_Stream[m_CurDrive],FALSE);  
 }
 void PlayCD(){
  BASS_ChannelPlay(m_Stream[m_CurDrive],FALSE);
 }
 bool IsPlaying(){
  if (BASS_ChannelIsActive(m_Stream[m_CurDrive])==BASS_ACTIVE_PLAYING)
   return true;

  return false;
 }

 void PauseCD(){  
	BASS_ChannelPause(m_Stream[m_CurDrive]);
 };
 void StopCD(){
   BASS_ChannelStop(m_Stream[m_CurDrive]);
   m_Stream[m_CurDrive]=0;
   Free();

 }
 BOOL CDIsReady(){
  return BASS_CD_IsReady(m_CurDrive);
 }
 char* CDGetID(DWORD dwId){
   return (char*)BASS_CD_GetID(m_CurDrive,dwId);
 }

 void SetPositionCD(int iPos){
  BASS_ChannelSetPosition(m_Stream[m_CurDrive],iPos * 176400);
 }
 int GetPositionCD(){
  return BASS_ChannelGetPosition(m_Stream[m_CurDrive]);
 }
 void SetVolumeCD(int iVol){
  BASS_ChannelSetAttributes(m_Stream[m_CurDrive],-1,100-iVol,-101);
 }
 void SetPaneoCD(int iPanning){
  BASS_ChannelSetAttributes(m_Stream[m_CurDrive],-1,-1,100-iPanning);
 }
 void SetSpeedCD(int iSpeed){
  BASS_ChannelSetAttributes(m_Stream[m_CurDrive],iSpeed*441,-1,-101);
 }
 int GetTrack(){
  DWORD track=BASS_CD_StreamGetTrack(m_Stream[m_CurDrive]);
  return LOWORD(track);
 }
 int GetNumTracks(){
   return BASS_CD_GetTracks(m_CurDrive);
 }
 int GetCurrentPosition(){
  return BASS_ChannelBytes2Seconds(m_Stream[m_CurDrive],GetPositionCD());
 }
 int GetCurrentMinutes(){ 
  return GetCurrentPosition()/60;
 }
 int GetCurrentSeconds(){
  return GetCurrentPosition()%60;
 }
 int GetMinutes(int iTrack){
   return (BASS_CD_GetTrackLength(m_CurDrive,iTrack)/176400)/  60; 
 }
 int GetSeconds(int iTrack){	
   return (BASS_CD_GetTrackLength(m_CurDrive,iTrack)/176400) % 60; 
 }
 int GetLength(int iTrack){
  return (BASS_CD_GetTrackLength(m_CurDrive,iTrack)/1024)/1024;
 }
 int GetLength(){
   return BASS_ChannelGetLength(m_Stream[m_CurDrive])/176400;
 }
 int GetLevel(){
  return BASS_ChannelGetLevel(m_Stream[m_CurDrive]);
 }
 std::vector<char> GetDrives(){
  char str[10];
  std::vector<char> cddevice;

  cddevice.clear();	  
  for (int count=2;count < 26;count++){
    sprintf(str, "%c:\\", (char)('A' + count));
    if (GetDriveType(str) == DRIVE_CDROM)                
	  cddevice.push_back(str[0]);        
        
  }

  return cddevice;
 }

 bool IsActive(){
  if(BASS_ChannelIsActive(m_Stream[m_CurDrive]))
   return true;

  return false;
 }
 bool IsOpen(){
  if(BASS_CD_DoorIsOpen(m_CurDrive))
	return true;

  return false;
 }
 void EjectCD(bool bFlag=true){
  if(bFlag)
   BASS_CD_Door(m_CurDrive,BASS_CD_DOOR_OPEN);
  else
   BASS_CD_Door(m_CurDrive,BASS_CD_DOOR_CLOSE);
 }
};