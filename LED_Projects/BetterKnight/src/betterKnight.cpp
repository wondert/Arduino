/*
*KnightRider
*This program will turn on series of LEDs in sequence
*Digital Output using pins (2, 3, 4, 5, 6)
*/

// Need to use include and import Arduino.h library since writting in C++

#include "Arduino.h"

// Set Digital I/O pins for use with LEDs
int LED0 = 2;
int LED1 = 3;
int LED2 = 4;
int LED3 = 5;
int LED4 = 6;

// Set time between LED activations
int ledtime = 100;  // time in milliseconds

// Initiate Arduino Pins
void setup() {
  // Specity pins to use and set OUTPUT mode
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
    // Turn on LEDs in sequence with timed delay between on/off
    for (int i = 2; i <= 6; i++){
      digitalWrite(i, HIGH);
      delay(ledtime);
      digitalWrite(i, LOW);
      delay(ledtime);
    }

    // Reverse the sequence starting with second to last LED
    for (int a = 5; a > 2; a--){
      digitalWrite(a, HIGH);
      delay(ledtime);
      digitalWrite(a, LOW);
      delay(ledtime);
    }
}
