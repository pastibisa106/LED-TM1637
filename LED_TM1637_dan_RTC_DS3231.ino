#include <Wire.h>
#include <DS3231.h>

#include <TM1637Display.h>
#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);

DS3231  rtc(SDA, SCL);

// Module connection pins (Digital Pins)
Time  t;
unsigned int h,m,s;
byte f;


//=========================
void setup() {
  rtc.begin();
  display.setBrightness(0x0f);
//--------------------------------------------------------------
//aktifkan baris perintah ini untuk seting RTC
//lakukan jika waktu tidak sesuai
//cukup sekali saja, setelah itu di-non-aktifkan lagi perintahnya
//rtc.setDate(01,03,2020);  //setting tanggal 11 Oktober 2019
//rtc.setTime(16, 28, 00);   //setting jam 08:15:00
//rtc.setDOW(0);            //setting hari Jumat, 0=Minggu,1=Senin
//--------------------------------------------------------------- 
}
//================== 
void loop() {
  t = rtc.getTime();
  h=t.hour,DEC;
  m=t.min,DEC;
  s=t.sec,DEC; 
  h=(h*100+m);
  if(f==0){
    display.showNumberDecEx(h, 64); 
    f=1;
  }
  else {
    display.showNumberDecEx(h, 0);
    f=0;
  }
  delay (1000);
}
