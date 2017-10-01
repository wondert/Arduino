/*
PhoneGAP application.
Use bluetooth to control an LED from Android phone.
LED logic embedded on Arduino Uno
*/
#include <SPI.h>
#include <BLEPeripheral.h>

// Arduino Uno
#define LED_PIN     3
#define BUTTON_PIN  4

// Bluetooth NRF8001
#define BLE_REQ     10
#define BLE_RDY     2
#define BLE_RST     9

// LED control pins + switch button variables
int currentState  = 0;
int debounceState = 0;
int switchState   = 0;
int ledState      = 0;

// declare event handlers and control functions.
void switchCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic);
void blePeripheralConnectHandler(BLECentral& central);
void blePeripheralDisconnectHandler(BLECentral& central);
void switchLED(const unsigned char* code, int codeLength);
void buttonPush();

// create peripheral instance
BLEPeripheral blePeripheral = BLEPeripheral(BLE_REQ, BLE_RDY, BLE_RST);

// create service
BLEService lightswitch = BLEService("D270");

// create switch characteristic
BLECharacteristic switchCharacteristic = BLECharacteristic("D271", BLEWrite, 20);
BLEDescriptor switchDescriptor = BLEDescriptor("2901", "Switch");

// create status characteristic
BLECharacteristic statusCharacteristic = BLECharacteristic("D272", BLENotify, 20);
BLEDescriptor statusDescriptor = BLEDescriptor("2901", "Status Message");

// code to change state of LED
const char secret[5] = "12345";

void setup() {
  Serial.begin(9600);
  Serial.println(F("Smart Light Switch"));

  // set advertised local name and service UUID
  blePeripheral.setLocalName("Light Switch");  // Advertised in scan data as part of GAP, required for nRF Master Control Panel app
  blePeripheral.setDeviceName("Light Switch"); // Advertised in generic access as part of GATT, required for LightBlue app
  blePeripheral.setAdvertisedServiceUuid(lightswitch.uuid());

  // add service and characteristics
  blePeripheral.addAttribute(lightswitch);

  blePeripheral.addAttribute(switchCharacteristic);
  blePeripheral.addAttribute(switchDescriptor);

  blePeripheral.addAttribute(statusCharacteristic);
  blePeripheral.addAttribute(statusDescriptor);

  // assign event handlers for connected, disconnected to peripheral
  blePeripheral.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  blePeripheral.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  // assign event handler for changing switch characteristic state
  switchCharacteristic.setEventHandler(BLEWritten, switchCharacteristicWritten);

  // begin initialization
  blePeripheral.begin();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Tell the bluetooth radio to do whatever it should be working on
  blePeripheral.poll();
  
  // check for button pressed event
  buttonPush();
}

// central connected event handler
void blePeripheralConnectHandler(BLECentral& central) {
  Serial.print(F("Connected event, central: "));
  Serial.println(central.address());
}

// central disconnected event handler
void blePeripheralDisconnectHandler(BLECentral& central) {
  Serial.print(F("Disconnected event, central: "));
  Serial.println(central.address());
}

// event handler function for write commands to BLEPeripheral from BLECentral device
void switchCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
  Serial.print(F("Characteristic event: "));
  switchLED(characteristic.value(), characteristic.valueLength());
}

// check passcode. modify LED accordingly if valid code sent.
void switchLED(const unsigned char* code, int codeLength) {
  boolean match = false;

  // does the code match the secret ON/OFF passcode
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
  
  if (match && ledState == 0) {
    // turn on LED
    Serial.println(F("code matches, lights on"));
    digitalWrite(LED_PIN, HIGH);
    ledState = 1;
    statusCharacteristic.setValue("light on");
  } else if (match && ledState == 1) {
    // turn off LED
    Serial.println(F("code matches, lights off"));
    digitalWrite(LED_PIN, LOW);
    ledState = 0;
    statusCharacteristic.setValue("light off");
  } else {
    // bad code, don't turn on LED
    Serial.println("invalid code");
    statusCharacteristic.setValue("invalid code");
  }
}

// led logic for physical button pressed.
void buttonPush() {
  // read button state
  currentState = digitalRead(BUTTON_PIN);
  delay(10);
  debounceState = digitalRead(BUTTON_PIN);

  // manually set LED via button push.
  if( currentState == debounceState  ) {
    // if state is stable, continue
    if ( currentState != switchState ) {
      // if state is different from last time we checked, continue
      if ( currentState == LOW ) {
        // if currentState is OFF, do nothing. if ON, continue
      } else {
        Serial.print(F("Button event: "));
        if ( ledState == 0 ) {
          switchCharacteristic.setValue(1);
          digitalWrite(LED_PIN, HIGH);
          ledState = 1;
          Serial.println(F("light on"));
       } else {
          switchCharacteristic.setValue(0);
          digitalWrite(LED_PIN, LOW);
          ledState = 0;
          Serial.println(F("light off"));
       }
      }
      switchState = currentState;
    }
  }
}