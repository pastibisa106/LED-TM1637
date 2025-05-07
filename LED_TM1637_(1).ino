// INCLUDES
// https://github.com/avishorp/TM1637
#include <TM1637Display.h>

// CONSTANTS
const uint8_t OFF[] = {0, 0, 0, 0};
// In this library, the byte order is .GFEDCBA
const uint8_t PLAY[] = {B01110011, B00111000, B01011111, B01101110};

// Create a display object, specifying parameters (Clock pin, Data pin)
TM1637Display display(2, 3);

void setup(){
  // Set brightness
  display.setBrightness(0x0c);
  // Clear the display
  display.setSegments(OFF);
}

void countdown() {
  for(int i=5000; i>0; i--) {
    // showNumberDec is a convenience function for displaying numeric values,
    // with options for decimal places, leading zeroes etc.
    display.showNumberDec(i, true, 4, 0);
    delay(80);
  }
}
void displayText() {
  display.setSegments(PLAY);
  delay(2000);
}
void loop(){
  displayText();
  countdown();
}
