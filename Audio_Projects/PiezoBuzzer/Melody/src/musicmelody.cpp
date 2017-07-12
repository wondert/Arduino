/*
musicmelody will play a short melody once!
the tone built-in function will be used generate the C scale
the pitches library will be used so that we do not have to set the notes
Uno board frequency: Min@ 31Hz, Max@65635Hz
*/

#include <Arduino.h>
#include <pitches.h>    // include this file in src directory. helper file need to create from tone tutorial.

#define PIEZO 8   // Pin 8 is a digital pin only

// notes in melody
unsigned int melody[] ={
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations as follows -- 4 = quarter note, 8 = eighth note, etc.
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  pinMode(PIEZO, OUTPUT);   // set Pin 8 to output

  // iterate over the notes of the melody
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    unsigned long noteDuration = 1000/noteDurations[thisNote];    // divide each note duration by 1000ms. so quarter note comes to 1/4
    tone(PIEZO, melody[thisNote], noteDuration);    // tone(pin, frequency, duration)

    int pauseBetweenNotes = noteDuration * 1.30;    // to distinguish between notes, set a brief pause. 30% + notes duration seems to work well.
    delay(pauseBetweenNotes);

    // stop playing the tone. if noTone not called will continue to play forever not exit loop
    noTone(8);

  }
}

void loop() {
  // nothing here. we want to have the melody play just once!
}
