/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 * Can use this program to test output of any Digital Pin.
 */

// Need to use include and import Arduino.h library since writting in C++

#include "Arduino.h"

// Set LED_BUILTIN if it is not defined by Arduino framework (For Uno it is.)
// int LED_BUILTIN = 13  // Sets value of pin to 13

// By default, pin 13 is connected to the onboard LED


void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  // wait for a second
  delay(200);

  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);

   // wait for a second
  delay(200);
}
