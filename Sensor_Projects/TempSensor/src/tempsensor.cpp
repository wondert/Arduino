/*
*Tempsensor
*This program will use the LM35 temperature sensor to detect the temperature and send that information back via serial port
*Temperature will update every second and be printed to serial output
*/

// Need to use include and import Arduino.h library since writting in C++

#include "Arduino.h"

int tempData;         // Creates variable of int type to capture temperature from LM35 sensor (it converts value onboard!!!)
int tempPin = 0;    // Sets analog input pin to A0

void setup() {
   Serial.begin(9600);    // Sets serial port to 9600
}

void loop() {
   tempData = analogRead(tempPin);
   Serial.print("TEMPERATURE = ");
   Serial.print(tempData); // display temperature value to serial monitor
   Serial.print("*F");
   Serial.println();
   delay(1000); // update sensor reading each one second
}
