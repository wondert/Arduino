/*
piezobuzzer generates a repeating single frequency tone.
the frequency is determined by the PWM duty cycle, which ranges from 0 to 255 (0 to 100%).
higher frequency can be obtained by a higher duty cycle.
the interval between tones is contrlled by a delay.
changing the input voltage to the piezo will increase the volume
*/

#include <Arduino.h>

#define PIEZO 3   // Pin 3 has PWM enabled

const int pause = 500;   // this sets the interval between tones. 500ms is a good starting value.

void buzzer(int pwm) {
  int freq = pwm;
  analogWrite(PIEZO, freq);
  delay(pause);
  digitalWrite(PIEZO, LOW);
  delay(pause);
}

void setup() {
  pinMode(PIEZO, OUTPUT);
}

void loop() {
  buzzer(200);
}
