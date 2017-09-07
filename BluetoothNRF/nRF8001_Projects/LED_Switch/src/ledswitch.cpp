/*
example ledswitch.ino from MakeBluetooth uses the #define preprocessor macro.
this creates undefined behavior, since the function BLEPeripheral has parameters
with type unsigned char. The #define text replacement works here, but it acts as
'magic', since the behavior for an unsigned char of '10' is undefined. The char
is only 1 byte, and valid ASCII only goes 0-9 for 8-bit unsigned char.
If it were to accept unsigned char req [] that would be fine, since '10' can be
represented as an array ['1','0'].

Since BLEPeripheral will take values for the pins it connects to:
BLEPeripheral(unsigned char req, optional unsigned char rdy, optional unsigned char rst)

...so why do we not assign with ints???

const unsigned int BLE_REQ = 10;
const unsigned int BLE_RDY = 2;
const unsigned int BLE_RST = 9;

How does this even work with define 10....these params are pin numbers...C is wierd :(
*/
#include <SPI.h>
#include <BLEPeripheral.h>

#define LED_PIN     3
#define BUTTON_PIN  4

#define BLE_REQ     10
#define BLE_RDY     2
#define BLE_RST     9

int currentState  = 0;
int debounceState = 0;
int switchState   = 0;
int ledState      = 0;

// declare event handler for write commands to the switchCharacteristic sent from BLECentral devices
void switchCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic);

// create peripheral instance
BLEPeripheral blePeripheral = BLEPeripheral(BLE_REQ, BLE_RDY, BLE_RST);

// create service
BLEService lightswitch = BLEService("FF10");

// create switch characteristic
BLECharCharacteristic switchCharacteristic = BLECharCharacteristic("FF11", BLERead | BLEWrite);
BLEDescriptor switchDescriptor = BLEDescriptor("2901", "Switch");

BLECharCharacteristic stateCharacteristic = BLECharCharacteristic("FF12", BLENotify);
BLEDescriptor stateDescriptor = BLEDescriptor("2901", "State");

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  // set advertised local name and service UUID
  blePeripheral.setLocalName("Light Switch");  // Advertised in scan data as part of GAP, required for nRF Master Control Panel app
  blePeripheral.setDeviceName("Smart Light Switch"); // Advertised in generic access as part of GATT, required for LightBlue app
  blePeripheral.setAdvertisedServiceUuid(lightswitch.uuid());

  // add service and characteristics
  blePeripheral.addAttribute(lightswitch);

  blePeripheral.addAttribute(switchCharacteristic);
  blePeripheral.addAttribute(switchDescriptor);

  blePeripheral.addAttribute(stateCharacteristic);
  blePeripheral.addAttribute(stateDescriptor);

  // assign event handler for changing switch characteristic state
  switchCharacteristic.setEventHandler(BLEWritten, switchCharacteristicWritten);

  // begin initialization
  blePeripheral.begin();

  Serial.println(F("Smart Light Switch"));
}

void loop() {
  blePeripheral.poll();

  currentState = digitalRead(BUTTON_PIN);
  delay(10);
  debounceState = digitalRead(BUTTON_PIN);


  if( currentState == debounceState  ) {
    if ( currentState != switchState ) {

      if ( currentState == LOW ) {
        // Button just released

      } else {
        Serial.print(F("Button event: "));
        if ( ledState == 0 ) {
          stateCharacteristic.setValue(1);
          switchCharacteristic.setValue(1);
          digitalWrite(LED_PIN, HIGH);
          ledState = 1;
           Serial.println(F("light on"));
       } else {
          stateCharacteristic.setValue(0);
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

// event handler function for write commands to BLEPeripheral from BLECentral device
void switchCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
  Serial.print(F("Characteristic event: "));
  if (switchCharacteristic.value()) {
    Serial.println(F("light on"));
    digitalWrite(LED_PIN, HIGH);
    ledState = 1;
    stateCharacteristic.setValue(1);

  } else {
    Serial.println(F("light off"));
    digitalWrite(LED_PIN, LOW);
    ledState = 0;
    stateCharacteristic.setValue(0);

  }
}
