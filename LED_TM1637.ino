#include <TM1637Display.h>

#define CLK 2
#define DIO 3

TM1637Display display (CLK, DIO);

int nilai;

void setup() {
  display.setBrightness(0x0f);
}
  
void loop() {
  for (nilai = 0; nilai < 1001; nilai++) {
    display.showNumberDec(nilai);
    delay(1);
  }
}
