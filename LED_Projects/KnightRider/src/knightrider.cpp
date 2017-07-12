/*
*KnightRider
*This program will turn on series of LEDs in sequence
*Digital Output using pins (2, 3, 4, 5, 6)
*/

// Need to use include and import Arduino.h library since writting in C++

#include "Arduino.h"

// Initiate Arduino Pins
void setup(){
  // Specity pins to use and set OUTPUT mode
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

// Activate pins in sequence
void loop(){
  // Turn pin on, wait, then off. Repeat with new pin.
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  delay(500);
  digitalWrite(6, LOW);
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(3, LOW);
}
