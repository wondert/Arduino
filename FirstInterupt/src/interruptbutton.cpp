#include <Arduino.h>

// create constant value names for the blinking LED and sensor pin
#define LED0 12
#define sensor 2

// create variable for ISP. must be volatile if used in interupt. volatiles are stored in RAM rather than a register, so are more stable.
volatile int state = 0;   // can also use byte, since it uses less memory. in this case, set initial value to LOW.

// definte interupt service function (ISR) to trigger change in control flow of main loop
void interuptFunction() {
  state = !state;   // trigger LED to stay on for 3 seconds
}

void setup() {
  // create interupt. must set pin to use for interupt, name of ISR function, and condition to trigger interupt.
  attachInterrupt(0, interuptFunction, HIGH);    // trigger ISR when digital pin2 (interupt pin 0) goes to high voltage ~ on button push.
  pinMode(LED0, OUTPUT);
  pinMode(sensor, INPUT);   // technically unneccesary to include this line, since all Digital Pins are set to input by default
}

void loop() {
  // code triggered by interupt through ISR function call
  if (state) {
    delay(250);
    digitalWrite(LED0, LOW);
    delay(1000);
    digitalWrite(LED0, HIGH);
    delay(3000);
    digitalWrite(LED0, LOW);
    delay(250);
    state = !state;
  }

  // default code for loop, blinking LED at 500ms interval
  digitalWrite(LED0, HIGH);
  delay(500);
  digitalWrite(LED0, LOW);
  delay(500);
}
