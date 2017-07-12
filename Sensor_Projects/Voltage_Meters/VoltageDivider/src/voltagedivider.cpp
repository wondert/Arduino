#include <Arduino.h>

// define pins to be used on Arduino
#define voltreader1 0    // Analog Pin A0 to read voltage direct from battery
#define voltreader2 1   // Analog Pin A1 to read voltage from voltage divider (between series resistors)
#define LED0 10    // Blue LED, Digital Pin 10
#define LED1 11    // Yellow LED, Digital Pin 11
#define LED2 12    // White LED, Digital Pin 12

// define variables to store analgog read from A0 and convert to voltage
int pinread1 = 0;
int pinread2 = 0;
float voltage1 = 0;
float voltage2 = 0;
const float readtovolts = 0.0048;


// initalize Digital Pins to output state (by default, all pin are set to input so not really necessary to set Analog Pin A0 to input)
void setup() {
  Serial.begin(9600);
  pinMode(OUTPUT, LED0);
  pinMode(OUTPUT, LED1);
  pinMode(OUTPUT, LED2);
}

// define function to capture voltages. cannot return array, so need to set return to a pointer.
float * findvoltage() {
  // create local array variable to hold voltages
  // declare array as static since it is local to the function, and we want to access it outside the function as the return value.
  static float voltages [2];

  // read Analog Pins
  pinread1 = analogRead(voltreader1);
  pinread2 = analogRead(voltreader2);

  // convert reads to voltage
  voltage1 = pinread1*readtovolts;
  voltage2 = pinread2*readtovolts;
  voltages[0] = voltage2;   // arrays act as a bottom-up stack or queue (FIFO). new items are inserted at the start of the stack (index 0). older items get pushed up.
  voltages[1] = voltage1;   // to set the true voltage as the first index, it needs to be added last. conversely, the split voltage needs to be added first.

  return voltages;
}

// define function to print the battery voltage
void displayvoltage() {
  // create a pointer variable to capture array return value of findvoltage()
  float *values;
  values = findvoltage();

  // print voltages. need to reference pointer variable then the index.
  // recall array[index] and index[array] are just syntactic sugar for *(array + index)!!!
  Serial.print("The battery's true voltage is: ");
  Serial.print(*(values + 0));
  Serial.println(" volts");
  Serial.print("The voltage splitter reads: ");
  Serial.print(*(values + 1));
  Serial.println(" volts");
}

void lightlogic() {
  // create a pointer variable to capture array return value of findvoltage()
  float *values;
  values = findvoltage();

  // set LED based on true voltage
  if (values[0] >= 1.50) {
    digitalWrite(LED0, HIGH);
    delay(1000);
    digitalWrite(LED0, LOW);
  }

  if ((values[0] < 1.50) && (voltage1 >= 1.30)) {
    digitalWrite(LED1, HIGH);
    delay(1000);
    digitalWrite(LED1, LOW);
  }

  if (values[0] < 1.30) {
    digitalWrite(LED2, HIGH);
    delay(1000);
    digitalWrite(LED2, LOW);
  }

  delay(1000);
}

void loop() {
  displayvoltage();
  lightlogic();
}
