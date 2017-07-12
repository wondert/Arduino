/*
ocarina will play the ocarina lullaby song from N64 Zelda The Ocarina of Time once!
the tone built-in function will be used generate the C scale
the pitches library will be used so that we do not have to set the notes
Uno board frequency: Min@ 31Hz, Max@65635Hz
Used python RTTL converter notebook to create melody notes and durations from RTTL formatted ring tone
*/

#include <Arduino.h>
#include <pitches.h>    // include this file in src directory. helper file need to create from tone tutorial.

#define PIEZO 8   // Pin 8 is a digital pin only

// notes in melody
unsigned int melody[] ={
  NOTE_B5, NOTE_PAUSE, NOTE_D6, NOTE_PAUSE, NOTE_A5, NOTE_PAUSE, NOTE_G5, NOTE_PAUSE, NOTE_A5, NOTE_PAUSE, NOTE_B5, NOTE_PAUSE, NOTE_D6, NOTE_PAUSE, NOTE_A5, NOTE_PAUSE, NOTE_B5, NOTE_PAUSE, NOTE_D6, NOTE_PAUSE, NOTE_A6, NOTE_PAUSE, NOTE_G6, NOTE_PAUSE, NOTE_D6, NOTE_PAUSE, NOTE_C6, NOTE_PAUSE, NOTE_B5, NOTE_PAUSE, NOTE_A5, NOTE_PAUSE, NOTE_B5, NOTE_PAUSE, NOTE_D6, NOTE_PAUSE, NOTE_A5, NOTE_PAUSE, NOTE_G5, NOTE_PAUSE, NOTE_A5, NOTE_PAUSE, NOTE_B5, NOTE_PAUSE, NOTE_D6, NOTE_PAUSE, NOTE_A5, NOTE_PAUSE, NOTE_B5, NOTE_PAUSE, NOTE_D6, NOTE_PAUSE, NOTE_A6, NOTE_PAUSE, NOTE_G6, NOTE_PAUSE, NOTE_D7
};

// note durations as in milliseconds.
unsigned long noteDurations[] = {
  250, 250, 125, 250, 250, 250, 62, 250, 62, 250, 250, 250, 125, 250, 500, 250, 250, 250, 125, 250, 250, 250, 125, 250, 250, 250, 62, 250, 62, 250, 500, 250, 250, 250, 125, 250, 250, 250, 62, 250, 62, 250, 250, 250, 125, 250, 500, 250, 250, 250, 125, 250, 250, 250, 125, 250, 500
};

void setup() {
  pinMode(PIEZO, OUTPUT);   // set Pin 8 to output

  // iterate over the notes of the melody
  for (int thisNote = 0; thisNote < 57; thisNote++) {
    // play the tone. pauses will generate no tone for duration.
    tone(PIEZO, melody[thisNote], noteDurations[thisNote]);    // tone(pin, frequency, duration)
    int pauseBetweenNotes = noteDurations[thisNote] * 1.30;    // to distinguish between notes, set a brief pause. 30% + notes duration seems to work well.
    delay(pauseBetweenNotes);

  // stop playing the tone. if noTone not called will continue to play forever not exit loop
  noTone(PIEZO);
  }
}

void loop() {
  // nothing here. we want to have the melody play just once!
}
