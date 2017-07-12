/*
gerudo will play the gerudo valley music from N64 Zelda The Ocarina of Time once!
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
  NOTE_CS5, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_PAUSE, NOTE_CS5, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_PAUSE, NOTE_D5, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_PAUSE, NOTE_D5, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_PAUSE, NOTE_B4, NOTE_E5, NOTE_FS5, NOTE_GS5, NOTE_PAUSE, NOTE_B4, NOTE_E5, NOTE_FS5, NOTE_GS5, NOTE_PAUSE, NOTE_FS5, NOTE_GS5, NOTE_FS5, NOTE_F5, NOTE_PAUSE, NOTE_CS5, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_PAUSE, NOTE_CS5, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_PAUSE, NOTE_D5, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_PAUSE, NOTE_D5, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_PAUSE, NOTE_B4, NOTE_E5, NOTE_FS5, NOTE_GS5, NOTE_PAUSE, NOTE_B4, NOTE_E5, NOTE_FS5, NOTE_GS5, NOTE_PAUSE, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_GS5
};

// note durations as in milliseconds.
unsigned long noteDurations[] = {
  62, 62, 62, 125, 250, 62, 62, 62, 250, 125, 62, 62, 62, 125, 250, 62, 62, 62, 250, 125, 62, 62, 62, 125, 250, 62, 62, 62, 250, 125, 62, 62, 62, 500, 125, 62, 62, 62, 125, 250, 62, 62, 62, 250, 125, 62, 62, 62, 125, 250, 62, 62, 62, 250, 125, 62, 62, 62, 125, 250, 62, 62, 62, 250, 125, 62, 62, 62, 500
};

void setup() {
  pinMode(PIEZO, OUTPUT);   // set Pin 8 to output

  // iterate over the notes of the melody
  for (int thisNote = 0; thisNote < 69; thisNote++) {
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
