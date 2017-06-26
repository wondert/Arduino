/*
*Fade
*This program will ramp LED brightness between the max and min values
*AnalogWrite is only supported on certain pins (3, 5, 6, 9, 10, 11) that support Pulse-Width Modulation (PWM)
*Cannot modify brightness of built-in LED (pin 13)
*Need a breadboard and external LEDs for this to work
*/

// Need to use include and import Arduino.h library since writting in C++

#include "Arduino.h"

// Set default LED brightness and how much to fade each cycle
int led0 = 3;          // set pin that the led is attached to. must support PWM.
int led1 = 5;          // set pin that the led is attached to. must support PWM.
int brightness = 0;    // set starting brightness of the LED (0% PWM)
int fadeAmount = 5;    // how many points to fade the LED by

// Start up LED
void setup() {
  // Initialize pin for LED as OUTPUT
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
}

// Change LED brightness gradually between min/max values
void loop() {
  // set the brightness of LED_BUILTIN:
  analogWrite(led0, brightness);
  analogWrite(led1, brightness);

  // increment brightness
  brightness = brightness + fadeAmount;

  // if brightness reached max or min values, reverse direction of change in LED brightness
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount;
  }

  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
