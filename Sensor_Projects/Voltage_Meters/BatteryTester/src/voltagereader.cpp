#include <Arduino.h>
// #include <iostream>    // add when printing output to Serial Monitor
// using namespace std;   // add when printing output to Serial Monitor

// define pins to be used on Arduino
#define voltreader 0    // Analog Pin A0 to read voltage
#define LED0 10    // Blue LED, Digital Pin 10
#define LED1 11    // Yellow LED, Digital Pin 11
#define LED2 12    // White LED, Digital Pin 12

// define variables to store analgog read from A0 and convert to voltage
int pinread = 0;
float voltage = 0;
const float readtovolts = 0.0048;


// initalize Digital Pins to output state (by default, all pin are set to input so not really necessary to set Analog Pin A0 to input)
void setup() {
  pinMode(OUTPUT, LED0);
  pinMode(OUTPUT, LED1);
  pinMode(OUTPUT, LED2);
}

void loop() {
  pinread = analogRead(voltreader);
  voltage = pinread*readtovolts;

  if (voltage >= 1.5) {
    digitalWrite(LED0, HIGH);
    delay(1000);
    digitalWrite(LED0, LOW);
  }
  else if ((voltage < 1.5) && (voltage >= 1.3)) {
    digitalWrite(LED1, HIGH);
    delay(1000);
    digitalWrite(LED1, LOW);
  }
  else {
    digitalWrite(LED2, HIGH);
    delay(1000);
    digitalWrite(LED2, LOW);
  }

  delay(1000);
}