/*
trafficlights simulates a single lane bridge with traffic lights on both ends.
the goal is to prevent cars from colliding in the center.
switch sensors will be present on both ends. we will use a tactile push button switch to simulate the sensor.
light sequence will include flashing green to warn of change to red, and time for cars to cross bridge after red change before opposite light turns green.
*/

#include "Arduino.h"

// define pin names
#define LED_BUILTIN 13
#define northsensor 12   // set pin 13 as sensor for southbound traffic. simulated using switch.
#define southsensor 3   // set pin 3 as sensor for northbound traffic. simulated using switch.
#define northgreen 7   // set pin 7 as output for Green LED on North side.
#define northred 6   // set pin 6 as output for Red LED on North side.
#define southgreen 5   // set pin 5 as output for Green LED on South side.
#define southred 4   // set pin 4 as output for Red LED on South side.
int valnorth = 0;   // set default value for north input sensor
int valsouth = 0;   // set default value for south input sensor

// define pin states. each pin will act as a sensor or LED source only.
void setup() {
  pinMode(northsensor, INPUT);
  pinMode(southsensor, INPUT);
  pinMode(northgreen, OUTPUT);
  pinMode(northred, OUTPUT);
  pinMode(southgreen, OUTPUT);
  pinMode(southred, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

// lightlogic defines the sequence of LED changes when a sensor switch is triggered.
// the light sequence is the same regardless of the switch triggered since we set a default state (south green, north red).
void lightlogic() {
  // trigger southgreen LED to flash for 5 seconds to warn drivers light is changing soon.
  for (int i = 0; i < 5; i++) {
    digitalWrite(southgreen, LOW);
    delay(500);
    digitalWrite(southgreen, HIGH);
    delay(500);
  }

  // turn south LED red.
  digitalWrite(southgreen, LOW);
  digitalWrite(southred, HIGH);

  // wait 5 seconds for cars going northbound to finish crossing.
  delay(5000);

  // turn north LED green.
  digitalWrite(northgreen, HIGH);
  digitalWrite(northred, LOW);

  // allow 5 seconds for green light.
  delay(5000);

  // trigger northgreen LED to flash for 5 seconds to warn drivers light is changing soon.
  for (int j = 0; j < 5; j++) {
    digitalWrite(northgreen, LOW);
    delay(500);
    digitalWrite(northgreen, HIGH);
    delay(500);
  }

  // turn north LED red.
  digitalWrite(northgreen, LOW);
  digitalWrite(northred, HIGH);

  // wait 5 seconds for cars going southbound to finish crossing.
  delay(5000);

  // return to default settings
  digitalWrite(southgreen, HIGH);
  digitalWrite(southred, LOW);

  return;
}

void loop() {
  // Set default LED states to prevent both lights from being Red at the same time.
  digitalWrite(northgreen, LOW);
  digitalWrite(northred, HIGH);
  digitalWrite(southgreen, HIGH);
  digitalWrite(southred, LOW);

  // Provide three second blink warning before sensor reads.
  for (int j = 0; j < 3; j++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }

  // read switch states.
  valnorth = digitalRead(northsensor);
  valsouth = digitalRead(southsensor);

  // Prevent both lights from being Green at the same time.
  if ((valnorth == HIGH) && (valsouth == HIGH)) {
    lightlogic();
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Prevent both lights from being Red at same time.
  if ((valnorth == HIGH) && (valsouth == LOW)) {
    lightlogic();
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(2000);
}
