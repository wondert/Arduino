/*
This project extends the LED Bluetooth Service from Project LED_Switch by adding
a second independent LED controllable light. Code also refactored for clarity.
*/
#include <SPI.h>
#include <BLEPeripheral.h>

#define LED_PIN     3
#define BUTTON_PIN  4
#define LED_PIN2    5

#define BLE_REQ     10
#define BLE_RDY     2
#define BLE_RST     9

int currentState  = 0;
int debounceState = 0;
int switchState   = 0;
int ledStateBlue  = 0;

char secret[] = "";

// declare event handlers for write commands to the switchCharacteristic sent from BLECentral devices
void switchCharacteristicBlueWritten(BLECentral& central, BLECharacteristic& characteristic);
void switchCharacteristicRedWritten(BLECentral& central, BLECharacteristic& characteristic);

// create peripheral instance
BLEPeripheral blePeripheral = BLEPeripheral(BLE_REQ, BLE_RDY, BLE_RST);

// create service
BLEService lightswitch = BLEService("FF10");

// create switch characteristics
BLECharCharacteristic switchCharacteristicBlue = BLECharCharacteristic("FF11", BLERead | BLEWrite);
BLEDescriptor switchDescriptorBlue = BLEDescriptor("2901", "SwitchBlue");

BLECharCharacteristic stateCharacteristicBlue = BLECharCharacteristic("FF12", BLENotify);
BLEDescriptor stateDescriptorBlue = BLEDescriptor("2901", "StateBlue");

BLECharCharacteristic switchCharacteristicRed = BLECharCharacteristic("FF13", BLERead | BLEWrite);
BLEDescriptor switchDescriptorRed = BLEDescriptor("2901", "SwitchRed");

BLECharCharacteristic stateCharacteristicRed = BLECharCharacteristic("FF14", BLENotify);
BLEDescriptor stateDescriptorRed = BLEDescriptor("2901", "StateRed");

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  // set advertised local name and service UUID
  blePeripheral.setLocalName("Light Switch");  // Advertised in scan data as part of GAP, required for nRF Master Control Panel app
  blePeripheral.setDeviceName("Smart Light Switch"); // Advertised in generic access as part of GATT, required for LightBlue app
  blePeripheral.setAdvertisedServiceUuid(lightswitch.uuid());

  // add service and characteristics
  blePeripheral.addAttribute(lightswitch);

  blePeripheral.addAttribute(switchCharacteristicBlue);
  blePeripheral.addAttribute(switchDescriptorBlue);

  blePeripheral.addAttribute(stateCharacteristicBlue);
  blePeripheral.addAttribute(stateDescriptorBlue);

  blePeripheral.addAttribute(switchCharacteristicRed);
  blePeripheral.addAttribute(switchDescriptorRed);

  blePeripheral.addAttribute(stateCharacteristicRed);
  blePeripheral.addAttribute(stateDescriptorRed);

  // assign event handlers for changing switch characteristic states
  switchCharacteristicBlue.setEventHandler(BLEWritten, switchCharacteristicBlueWritten);
  switchCharacteristicRed.setEventHandler(BLEWritten, switchCharacteristicRedWritten);

  // begin initialization
  blePeripheral.begin();

  Serial.println(F("Smart Light Switch"));
}

void loop() {
  blePeripheral.poll();

  currentState = digitalRead(BUTTON_PIN);
  delay(10);
  debounceState = digitalRead(BUTTON_PIN);

  // check if push-button used
  if( currentState == debounceState  ) {
    if ( currentState != switchState ) {

      if ( currentState == LOW ) {
        // Button just released

      } else {
        Serial.print(F("Button event: "));
        if ( ledStateBlue == 0 ) {
          stateCharacteristicBlue.setValue(1);
          switchCharacteristicBlue.setValue(1);
          digitalWrite(LED_PIN, HIGH);
          ledStateBlue = 1;
           Serial.println(F("light on"));
       } else {
          stateCharacteristicBlue.setValue(0);
          switchCharacteristicBlue.setValue(0);
          digitalWrite(LED_PIN, LOW);
          ledStateBlue = 0;
           Serial.println(F("light off"));
       }
      }
      switchState = currentState;
    }
  }
  // switch 2 button will be set completely by bluetooth.
}

// event handler Blue function for write commands to BLEPeripheral from BLECentral device
void switchCharacteristicBlueWritten(BLECentral& central, BLECharacteristic& characteristic) {
  Serial.print(F("Characteristic event: "));
  if (switchCharacteristicBlue.value()) {
    Serial.println(F("blue light on"));
    digitalWrite(LED_PIN, HIGH);
    ledStateBlue = 1;
    stateCharacteristicBlue.setValue(1);

  } else {
    Serial.println(F("blue light off"));
    digitalWrite(LED_PIN, LOW);
    ledStateBlue = 0;
    stateCharacteristicBlue.setValue(0);

  }
}

// event handler Red function for write commands to BLEPeripheral from BLECentral device
void switchCharacteristicRedWritten(BLECentral& central, BLECharacteristic& characteristic) {
  Serial.print(F("Characteristic event: "));
  if (switchCharacteristicRed.value()) {
    Serial.println(F("red light on"));
    digitalWrite(LED_PIN2, HIGH);
    stateCharacteristicRed.setValue(1);

  } else {
    Serial.println(F("red light off"));
    digitalWrite(LED_PIN2, LOW);
    stateCharacteristicRed.setValue(0);

  }
}
