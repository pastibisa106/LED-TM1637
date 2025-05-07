#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TM1637Display.h>
#define CLK 2
#define DIO 3

TM1637Display display (CLK, DIO);

int nilai;

LiquidCrystal_I2C lcd (0x27 , 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

unsigned long mulai, selesai, dataStopWatch;
int i=0;
int fPaus = 0;
long lastButton = 0;
long delayAntiBouncing = 50;
long dataPaus = 0;

void setup() {
  // put your setup code here, to run once:

  display.setBrightness(0x0f);

  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
  digitalWrite (A0, 1);
  digitalWrite (A1, 1);
  lcd.begin (16, 2);
  
  lcd.setCursor (1, 0); // baris pertama
  lcd.print("TEST Stopwatch");
  lcd.setCursor (1, 1);
  lcd.print("by VCOOL"); // baris kedua
  delay (4000);
  lcd.clear();
  lcd.print ("Tekan Tombol");
  lcd.setCursor (0, 1);
  lcd.println ("Start / Stop    ");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(A0)==0) {
    for (nilai = 0; nilai < 201; nilai++) {
      display.showNumberDec(nilai);
      delay(1);
    }
    if ((millis()-lastButton) > delayAntiBouncing) {
      if (i==0) {
        lcd.clear();
        lcd.setCursor (0,0);
        lcd.print("Start Timer");
        mulai = millis();
        fPaus = 0;
      }
      else if (i==1) {
      //lcd.clear();
        lcd.setCursor (0,0);
        lcd.print ("Stop Timer ");
        dataPaus = dataStopWatch;
        fPaus = 1;
      }
      i = !i;
    }
    lastButton = millis();
  }
  else if (digitalRead(A1)== 0 && fPaus==1) {
    dataStopWatch = 0;
    dataPaus = 0;
    lcd.clear();
    lcd.print ("Reset Stopwatch");
    lcd.setCursor (0,1);
    lcd.print ("0:0:0:0");
    delay (2000);
    lcd.clear();
    lcd.print ("Tekan Tombol");
    lcd.setCursor (0,1);
    lcd.print("Start / Stop");
  }
  if (i==1) {
    selesai = millis();
    float jam, menit, detik, miliDetik;
    unsigned long over;
    
    //MATH time!!!
    dataStopWatch = selesai - mulai;
    dataStopWatch = dataPaus + dataStopWatch;
    
    jam = int (dataStopWatch / 3600000);
    over = dataStopWatch % 3600000;
    menit = int (over/60000);
    over = over % 60000;
    detik = int (over/1000);
    miliDetik = over % 1000;
    
    lcd.setCursor (0,1);
    lcd.print(jam, 0);
    lcd.print(":");
    lcd.print (menit, 0);
    lcd.print(":");
    lcd.print (detik, 0);
    lcd.print(".");
    if (jam < 10){
      lcd.print(miliDetik,0);
      lcd.print(" ");
    }
  }
}
