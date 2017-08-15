/*
 This sketch displays the temperature from an LM35 sensor onto an LCD shield.
 Temperature displayed in Fareneheight.


 Arduino Shield LCD circuit:
 * LCD RS pin to digital pin 8
 * LCD Enable pin to digital pin 9
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

*/

// include the library code:
#include <LiquidCrystal.h>
#include "Arduino.h"

int temp;           // Creates variable of int type to capture temperature from LM35 sensor (it converts value onboard!!!)
int tempPin = 1;    // Sets analog input pin to A1

// initialize LiquidCrystal library
// setup pins for arduino shield
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
   lcd.print("Temperature (F):");
}

void loop() {
  temp = analogRead(tempPin);   // read temp data in faren's
  lcd.setCursor(0, 1);          // set the cursor to column 0, line 1. note line 1 is the second row, since counting begins with 0.
  lcd.print(temp);              // print temp data to LCD
  delay(1000);                  // update sensor reading each second
}
