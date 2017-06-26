/*
*Tempsensor
*This program will use the LM35 temperature sensor to detect the temperature and send that information back via serial port
*Temperature will update every second and be printed to serial output
*/

// Need to use include and import Arduino.h library since writting in C++

#include "Arduino.h"

float temp;         // Creates variable of float type to capture analog voltage from LM35 sensor
float faren;
int tempPin = 0;    // Sets analog input pin to A0

void setup() {
   Serial.begin(9600);    // Sets serial port to 9600
}

void loop() {
   temp = analogRead(tempPin);
   // read analog volt from sensor and save to variable temp
   temp = temp * 0.48828125;
   // convert the analog volt to its temperature equivalent
   faren = (temp * 1.8) + 32;
   Serial.print("TEMPERATURE = ");
   Serial.print(faren); // display temperature value to serial monitor
   Serial.print("*F");
   Serial.println();
   delay(5000); // update sensor reading each one second
}
