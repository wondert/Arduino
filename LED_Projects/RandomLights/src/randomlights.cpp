/*
*RandomLights
*This program will ramp LED brightness between the max and min values for random LED's present on the board
*AnalogWrite is only supported on certain pins (3, 5, 6, 9, 10, 11) that support Pulse-Width Modulation (PWM)
*Cannot modify brightness of built-in LED (pin 13)
*Need a breadboard and external LEDs for this to work
*/

// Need to use include and import Arduino.h library since writting in C++

#include <Arduino.h>

// Set pins to cycle through in program
int led0 = 3;          // set pin that the led is attached to. must support PWM.
int led1 = 5;          // set pin that the led is attached to. must support PWM.
int led2 = 6;          // set pin that the led is attached to. must support PWM.
int led3 = 9;          // set pin that the led is attached to. must support PWM.
int led4 = 10;          // set pin that the led is attached to. must support PWM.

// Create array containing PWM compatible pins
int a[] = {led0, led1, led2, led3, led4};

// Set default LED brightness and how much to fade each cycle
int brightness = 0;    // set starting brightness of the LED (0% PWM)
int fadeAmount = -5;    // how many points to fade the LED by

// Set time between LED activations
int ledtime = 500;  // time in milliseconds

// startup pins for program
void setup() {
  // Specity pins to use and set OUTPUT mode
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

// Cycle through brightness for fixed led's, cycle on/off sequence for others
void loop() {
  // Set upper and lower bounds for random number
  int HI = 4;
  int LO = 0;

  // Select random LED and set brightness
  int r = LO + rand() % (HI - LO);
  analogWrite(a[r], brightness);

  // Tracking variable to count times brightness = 0
  int tracker = 0;

  // Create loop to cycle brightness...
  while(tracker < 3) {
    // If brightness reached min or max value, reverse direction of change in LED brightness
    if (brightness == 0 || brightness == 255) {
      fadeAmount = -fadeAmount;
      tracker++;
    }

    // Activate random LED and increment brightness
    analogWrite(a[r], brightness);
    brightness = brightness + fadeAmount;

    // Reset fadeAmount sign to original value before we exit While loop
    if (tracker == 3) {
      fadeAmount = -fadeAmount;
    }

    // wait for 30 milliseconds to see the dimming effect
    delay(30);
    }
  delay(ledtime);
}
