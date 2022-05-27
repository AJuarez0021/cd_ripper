#include "CPanel.h"
extern CPanel p;

void CALLBACK EndSync(HSYNC handle, DWORD channel, DWORD data, DWORD user)
{
	
		DWORD track=BASS_CD_StreamGetTrack(channel);
		DWORD drive=HIWORD(track);
		DWORD tracks=BASS_CD_GetTracks(drive);
		if (tracks==-1) 
		 return; 

		track=(LOWORD(track)+1)%tracks;
		app.lv.SetItem(track);
	    p.SetDrive(drive);
		p.PlayCD(track);
	
}



