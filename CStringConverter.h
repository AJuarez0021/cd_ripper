#include <windows.h>
#include <string>

using namespace std;

class CStringConverter{
private:
  char m_strBuffer[10];
protected:
 typedef std::basic_string<TCHAR> ustring;
public:
  CStringConverter(){ }
  
 string ToString(int iValue){  
  sprintf(m_strBuffer,"%d",iValue);
  string strRes=m_strBuffer;
  return strRes;
 }
 string ToString(char ch){
  sprintf(m_strBuffer,"%c",ch);
  string strRes=m_strBuffer;
  return strRes;
 }
 string ToString(float fValue){
  sprintf(m_strBuffer,"%1.6f",fValue);
  string strRes=m_strBuffer;
  return strRes;
 }
 string ToString(long lValue){
  sprintf(m_strBuffer,"%l",lValue);
  string strRes=m_strBuffer;
  return strRes;
 }
};