/*
pintest will test pins for output capacity
*/

#include "Arduino.h"

// define pin names
int LED0 = 4;
int LED1 = 5;
int LED2 = 6;
int LED3 = 7;

// define pin states. each pin will act as a LED source only.
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  // Set LED's to blink in alternating pattern..
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  digitalWrite(LED_BUILTIN, HIGH);

  delay(500);

  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED_BUILTIN, LOW);

  delay(500);

}
