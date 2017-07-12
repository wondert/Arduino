/*
Cscale will play the full scale of the C note, to the tune of DO RAE MI LA FA SI DOE
the tone built-in function will be used generate the C scale
*/

#include <Arduino.h>

#define PIEZO 8   // Pin 8 is a digital pin only

// define the full C scale notes
#define NOTE_C6 1047
#define NOTE_D6 1175
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_G6 1568
#define NOTE_A6 1760
#define NOTE_B6 1976
#define NOTE_C7 2093

const int pause = 500;   // this sets the interval between tones. 500ms is a good starting value.

void setup() {
  pinMode(PIEZO, OUTPUT);   // set Pin 8 to output
}

void loop() {
  // tone(pin, frequency, duration)
  tone(PIEZO, NOTE_C6, pause);
  delay(pause);
  tone(PIEZO, NOTE_D6, pause);
  delay(pause);
  tone(PIEZO, NOTE_E6, pause);
  delay(pause);
  tone(PIEZO, NOTE_F6, pause);
  delay(pause);
  tone(PIEZO, NOTE_G6, pause);
  delay(pause);
  tone(PIEZO, NOTE_A6, pause);
  delay(pause);
  tone(PIEZO, NOTE_B6, pause);
  delay(pause);
  tone(PIEZO, NOTE_C7, pause);
  delay(pause);
}
