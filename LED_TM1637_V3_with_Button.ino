#include <TM1637Display.h>
#define CLK 2
#define DIO 3
TM1637Display display (CLK, DIO);

int nilai;
int i=0;

const uint8_t berhenti[] = {
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,           // S
  SEG_F | SEG_E | SEG_D | SEG_G,                   // t
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_A | SEG_B | SEG_G | SEG_F | SEG_E            // P
};

// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};

void setup() {
  display.setBrightness(0x0f);
  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
  digitalWrite (A0, 1);
  digitalWrite (A1, 1);
}

void loop() {
  if (digitalRead(A0)==0) {
    for (nilai = 0; nilai < 1001; nilai++) {
      if(digitalRead(A1)==0) {
        display.setSegments(berhenti);
        delay(300);
        display.setSegments(blank);
        delay(300);
      }
      display.showNumberDec(nilai);
      delay(1);
    }
  }
  else if (digitalRead(A1)==0) {
    display.setSegments(blank);
  }
}
