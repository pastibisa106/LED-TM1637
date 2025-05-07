// DEFINES
// macros to retrievev the fractional seconds and minute parts of a time
// supplied in ms

#define numberOfSeconds (_time_) ((_time_ / 1000) % 60)
#define numberOfMinutes (_time_) (((_time_ / 1000) / 60) % 60)

// INCLUDES
#include <TM1637Display.h>

// Constants
const uint8_t OFF[] = {0,0,0,0};
// in this library, the byte order is GFEDCBA
const uint8_t PLAY[] = {B01110011, B00111000, B01011111, B01101110};

// GLOBALS
// create a display object, specifying parameters (clock pin, data pin)
TM1637Display display(2,3);

// 1000ms in 1sec, 60 secs in 1min, 60min in 1hr. So, 1000x60x60 = 3600000ms = 1hr
unsigned long timeLimit = 3600000;

void setup () {
  Serial.begin(9600);
  // set brightness
  display.setBrightness(0x0c);
  // Clear the display
  display.setSegments(OFF);
}

void countdown() {
  // Calculate the time remaining
  unsigned long timeRemaining = timeLimit - millis();

  while (timeRemaining > 0) {
    // To display the countdown in mm:ss format, separate the parts
    int seconds = numberOfSeconds (timeRemaining);
    int minutes = numberOfMinutes (timeRemaining));

    // This displays the seconds in the last two places
    display.showNumberDecEx (seconds, 0, true, 2, 2);
    // Display the minutes in the first two places, with colon
    display.showNumberDecEx (minutes, 0x80>>3, true, 2, 0);

    // Update the time remaining
    timeRemaining = timeLimit - millis();
  }
}

void displayText () {
  display.setSegments (PLAY);
  delay (2000);
}

void loop () {
  // displayText();
  countdown();
}

