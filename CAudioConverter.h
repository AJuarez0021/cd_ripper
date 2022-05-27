#ifndef __CAUDIO_CONVERTER_H
#define __CAUDIO_CONVERTER_H

#include <windows.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include "lame\BladeMP3EncDll.h"
#include "CProgressBar.h"
#include "bass\bass.h"
#include "CTimer.h"
#include "CCda.h"
using namespace std;

class CAudioConverter : public CCda
{

 private:
  ofstream Log;  
 public:
  void DisplayTime(char *strText);
 public:
  CProgressBar p;
  CAudioConverter(){ }
  bool Init(HWND);
  void Close();
  void InitProgressBar(HWND hWnd,UINT uID,COLORREF Color);
  bool CdaToWav(char cDrive,int iTrackNum,string OutputFileName);	
  bool WavToMp3(string strFileName,string OutputFileName);  
  
};

#endif
