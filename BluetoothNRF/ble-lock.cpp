// Bluetooth Low Energy Lock
// (c) 2014-2015 Don Coleman
//
// Adafruit nRF8001 Bluefruit LE http://adafru.it/1697
// RedBear Lab BLE Shield http://redbearlab.com/bleshield/
// Solenoid Lock http://adafru.it/1512
// arduino-BLEPeripheral https://github.com/sandeepmistry/arduino-BLEPeripheral.git

#include <SPI.h>
#include <BLEPeripheral.h>

#define LOCK_PIN 6
#define RED_LED_PIN 4
#define GREEN_LED_PIN 5

// See BLE Peripheral documentation for setting for your hardware
// https://github.com/sandeepmistry/arduino-BLEPeripheral#pinouts

// Adafruit Bluefruit LE
#define BLE_REQ 10
#define BLE_RDY 2
#define BLE_RST 9

// RedBear BLE Shield 2.x
//#define BLE_REQ 9
//#define BLE_RDY 8
//#define BLE_RST UNUSED

BLEPeripheral blePeripheral = BLEPeripheral(BLE_REQ, BLE_RDY, BLE_RST);
BLEService lockService = BLEService("D270");
BLECharacteristic unlockCharacteristic = BLECharacteristic("D271", BLEWrite, 20);
BLEDescriptor unlockDescriptor = BLEDescriptor("2901", "Unlock");
BLECharacteristic statusCharacteristic = BLECharacteristic("D272", BLENotify, 20);
BLEDescriptor statusDescriptor = BLEDescriptor("2901", "Status Message");

// code that opens the lock
char secret[] = "12345";
long openTime = 0;

void setup() {
  Serial.begin(9600);
  Serial.println(F("BLE Lock"));

  // set advertised name and service
  blePeripheral.setDeviceName("BLE Lock");
  blePeripheral.setLocalName("BLE Lock");
  blePeripheral.setAdvertisedServiceUuid(lockService.uuid());

  // add service and characteristic
  blePeripheral.addAttribute(lockService);

  blePeripheral.addAttribute(unlockCharacteristic);
  blePeripheral.addAttribute(unlockDescriptor);

  blePeripheral.addAttribute(statusCharacteristic);
  blePeripheral.addAttribute(statusDescriptor);

  // assign event handlers for connected, disconnected to peripheral
  blePeripheral.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  blePeripheral.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  // assign event handlers for characteristic
  unlockCharacteristic.setEventHandler(BLEWritten, unlockCharacteristicWritten);

  // begin initialization
  blePeripheral.begin();

  pinMode(LOCK_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  digitalWrite(LOCK_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
}

void loop() {

  // Tell the bluetooth radio to do whatever it should be working on
  blePeripheral.poll();

  // close lock and reset lights after 4 seconds
  if (openTime && millis() - openTime > 4000) {
    resetLock();
  }

}

void blePeripheralConnectHandler(BLECentral& central) {
  // central connected event handler
  Serial.print(F("Connected event, central: "));
  Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLECentral& central) {
  // central disconnected event handler
  Serial.print(F("Disconnected event, central: "));
  Serial.println(central.address());
}

void unlockCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
  // central wrote new value to the unlock characteristic
  Serial.println(F("Unlock characteristic written"));

  openLock(characteristic.value(), characteristic.valueLength());
}

void openLock(const unsigned char* code, int codeLength) {
  openTime = millis();  // set even if bad code so we can reset the lights

  // does the code match the secret
  boolean match = false;

  if (strlen(secret) == codeLength) {
    for (int i = 0; i < codeLength; i++) {
      if (secret[i] != code[i]) {
        match = false;
        break;
      } else {
        match = true;
      }
    }
  }

  if (match) {
    // open the lock
    Serial.println("Code matches, opening lock");
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(LOCK_PIN, HIGH); // open the lock
    statusCharacteristic.setValue("unlocked");
  } else {
    // bad code, don't open
    Serial.println("Invalid code");
    digitalWrite(RED_LED_PIN, HIGH);
    statusCharacteristic.setValue("invalid code");
  }
}

// closes the lock and resets the lights
void resetLock() {
  // reset the lights
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(LOCK_PIN, LOW); // close the lock
  statusCharacteristic.setValue("locked");
  openTime = 0;
}
