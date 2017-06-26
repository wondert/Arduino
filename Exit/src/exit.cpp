/*
*Exit
*This program will turn all Digital I/O Pins to LOW ~ off setting
*Kill any running program loop with exit command
*/

// Need to use include and import Arduino.h library since writting in C++

#include "Arduino.h"

// Initiate Arduino Pins
void setup(){
  // Specity pins to shutdown from OUTPUT mode
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

// Activate pins in sequence
void loop(){
  // Turn pin on, wait, then off. Repeat with new pin.
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);

  // Exit loop.
  exit(0);  // The 0 is required to prevent compile error
}
