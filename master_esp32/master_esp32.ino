#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  if (!SerialBT.begin("Button_1")) { // Initialize Bluetooth with the name "Button_1"
    Serial.println("An error occurred initializing Bluetooth");
  } else {
    Serial.println("Bluetooth initialized");
  }
  Serial.println("Button_1 ready for connection");
}

void loop() {
  // Send data
  SerialBT.println("Button_1");
  delay(1000);

  // Read incoming data
  if (SerialBT.available()) {
    String receivedData = SerialBT.readString();
    Serial.println("Received: " + receivedData);
  }
}
