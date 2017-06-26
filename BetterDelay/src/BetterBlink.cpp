/*
 * BetterBlink
 * Rapidly cycles LED on/off followed by preset pause.
 */

// Need to use include and import Arduino.h library since writting in C++

#include "Arduino.h"

// Set LED_BUILTIN if it is not defined by Arduino framework (For Uno it is.)

// Create variable to capture LED state (on/off)
int ledstate = LOW;

// Set interval between rapid LED cycling
const long interval = 2000;  // interval in milliseconds

// Create a counter for how many times LED is turned on
int ledcounter = 0; //this value is related to blinkspeed. the larger the counter the more times the LED blinks before the long pause

// Set how long the LED is off inside the loop
int blinkspeed = 50; // blinkspeed in milliseconds

void setup() {
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Change LED state if we have not exceeded the maximum number of LED power cycles
  if (ledcounter <= 20) { // value should be interval divided by 2*blinkspeed

    // set LED state to opposite of current state
    if (ledstate == LOW) {
      ledstate = HIGH;
      ledcounter = ledcounter + 1;
      digitalWrite(LED_BUILTIN, ledstate);
      delay(blinkspeed);  // keep LED on for specified time before continuing if loop
    } else {
      ledstate = LOW;
      digitalWrite(LED_BUILTIN, ledstate);
      delay(blinkspeed);  // keep LED off for specified time before continuing if loop
    }
  } else {
    // Wait set interval before restarting main loop
    digitalWrite(LED_BUILTIN, LOW);
    ledcounter = 0; // reset ledcounter
    delay(interval);  // wait time interval in seconds
        }
}
