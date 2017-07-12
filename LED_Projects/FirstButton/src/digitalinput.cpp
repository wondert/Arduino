/*
*digitalinput
*This program will turn on LED in response to button push
*Demonstrating the use of the digitalRead function to sense changes in voltage/current
*Need a breadboard, capacitor, tactile push button, resistors, wires, and external LEDs for this to work
*/

// Need to use include and import Arduino.h library since writting in C++

#include "Arduino.h"

#define LED 11    // using define statement to set a fixed value. no need for semicolon after statement!
#define BUTTON 6    // not sure why we dont use normal int variable definition...

void setup() {
  pinMode(LED, OUTPUT);   // output for the LED
  pinMode(BUTTON, INPUT);   // input for the button
}

void loop() {
  if (digitalRead(BUTTON) == HIGH) {
    digitalWrite(LED, HIGH);    // turn on the LED
    delay(50);   // wait for 50 milliseconds. button will appear very responsive.
    digitalWrite(LED, LOW);   // turn off the LED
  }
}
