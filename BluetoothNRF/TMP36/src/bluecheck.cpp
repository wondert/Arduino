/*
   Copyright (c) 2015 Intel Corporation.  All rights reserved.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
   This sketch example partially implements the standard Bluetooth Low-Energy Heart Rate service.
   For more information: https://developer.bluetooth.org/gatt/services/Pages/ServicesHome.aspx
*/

#include <CurieBLE.h>

BLEPeripheral blePeripheral;          // BLE Peripheral Device (the board you're programming)
BLEService heartRateService("180D");  // BLE Heart Rate Service

// BLE Heart Rate Measurement Characteristic
BLECharacteristic heartRateChar("2A37",  // standard 16-bit characteristic UUID
    BLERead | BLENotify, 2);             // remote clients will be able to get notifications if this characteristic changes
                                         // the characteristic is 2 bytes long as the first field needs to be "Flags" as per BLE specifications
                                         // https://developer.bluetooth.org/gatt/characteristics/Pages/CharacteristicViewer.aspx?u=org.bluetooth.characteristic.heart_rate_measurement.xml

unsigned long previousMillis = 0;  // last time the temperature was checked in milliseconds
unsigned long interval = 2000; // time interval between sensor updates

void setup() {
  Serial.begin(115200);    // initialize serial communication
  pinMode(13, OUTPUT);     // initialize the LED on pin 13 to indicate when a central is connected

  /* Set a local name for the BLE device
     This name will appear in advertising packets
     and can be used by remote devices to identify this BLE device
     The name can be changed but may be truncated based on space left in advertisement packet
  */
  blePeripheral.setLocalName("TemperatureSketch");
  blePeripheral.setAdvertisedServiceUuid(heartRateService.uuid());  // add the service UUID
  blePeripheral.addAttribute(heartRateService);                     // Add the BLE Heart Rate service
  blePeripheral.addAttribute(heartRateChar);                        // add the Heart Rate Measurement characteristic

  /* Now activate the BLE device.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection
  */
  blePeripheral.begin();
  Serial.println("Bluetooth device active, waiting for connections...");
}

void updateTemp() {
  /* Read the current voltage level on the A0 analog input pin.
     This is used here to collect temperature measurement.

    The LM35 sensor output converts a temperature reading to the analog value corresponding to degrees in Farenheight. Very convenient!
    This sensor has a temperature range of -55C to 150C.
    A conversion factor supplied by the manufacture specifies each 0.01V is equivalent to 1C.
  */
  int tempData = analogRead(A0);                 // read temperature from LM35 sensor on the A0 analog input pin.
  Serial.print("Temperature is now: ");          // print temperature
  Serial.println(tempData);
  const unsigned char TemperatureCharArray[2] = { 0, (char)tempData };
  heartRateChar.setValue(TemperatureCharArray, 2);    // and update the temperature measurement characteristic
}

void loop() {
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());
    // turn on the LED to indicate the connection:
    digitalWrite(13, HIGH);

    // check the temperature measurement every 2000ms
    // as long as the central is still connected:
    while (central.connected()) {
      unsigned long currentMillis = millis();     // grab current time
      // check the temperature measurement every 2000ms:
      if ((unsigned long)(currentMillis - previousMillis) >= interval) {
        previousMillis = millis();                // remember last time we checked
        updateTemp();
      }
    }
    // when the central disconnects, turn off the LED:
    digitalWrite(13, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}
