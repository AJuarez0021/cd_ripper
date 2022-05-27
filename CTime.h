#include <windows.h>

class CTime{
private:
 SYSTEMTIME st;
public:
 CTime(){
  GetLocalTime(&st);
 }

 void GetTime(){
  GetLocalTime(&st);
 }

 int GetHour() const{
  return st.wHour;
 }
 int GetYear() const{
  return st.wYear;
 }
 int GetSecond() const{
  return st.wSecond;
 }

 int GetDay() const{
  return st.wDay;
 }
 int GetMonth() const{
  return st.wMonth;
 }
 string GetDayWeek(){
  string strDay;
  switch(st.wDayOfWeek){
   case 0: strDay=TEXT("Domingo");
	       break;
   case 1: strDay=TEXT("Lunes");
	       break;
   case 2: strDay=TEXT("Martes");
	       break;
   case 3: strDay=TEXT("Miercoles");
	       break;
   case 4: strDay=TEXT("Jueves");
	       break;
   case 5: strDay=TEXT("Viernes");
	       break;
   case 6: strDay=TEXT("Sabado");
	       break;
  
 }
 return strDay;
 }
 string GetStringMonth(){
  string strMonth;
  switch(st.wMonth){
   case 1:strMonth=TEXT("Enero");
	      break;
   case 2:strMonth=TEXT("Febrero");
	      break;
   case 3:strMonth=TEXT("Marzo");
	      break;
   case 4:strMonth=TEXT("Abril");
	      break;
   case 5:strMonth=TEXT("Mayo");
	      break;
   case 6:strMonth=TEXT("Junio");
	      break;
   case 7:strMonth=TEXT("Julio");
	      break;
   case 8:strMonth=TEXT("Agosto");
	      break;
   case 9:strMonth=TEXT("Septiembre");
	      break;
   case 10:strMonth=TEXT("Octubre");
	      break;
   case 11:strMonth=TEXT("Noviembre");
	      break;
   case 12:strMonth=TEXT("Diciembre");
	      break;      
   
  }
  return strMonth;
 }
 int GetMinute() const{
   return st.wMinute;
 }
};