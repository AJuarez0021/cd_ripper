#include <windows.h>

class CTimer{
 private:
  DWORD m_FirstTime,m_FinalTime;
  DWORD m_TimeElapsed;
 public:
	CTimer(){
      m_FirstTime=m_FinalTime=m_TimeElapsed=0;
	}
	void Start(){
     m_FirstTime=timeGetTime();
	}
	void Stop(){
      m_FinalTime=timeGetTime();
      m_TimeElapsed=m_FinalTime-m_FirstTime;
	}
	DWORD GetElapsed(){
     return m_TimeElapsed/1000;
	}

};