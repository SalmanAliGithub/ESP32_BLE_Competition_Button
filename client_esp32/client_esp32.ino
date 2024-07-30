#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  if (!SerialBT.begin("Button_2")) { // Initialize Bluetooth with the name "Button_2"
    Serial.println("An error occurred initializing Bluetooth");
  } else {
    Serial.println("Bluetooth initialized");
  }
  Serial.println("Attempting to connect to Button_1");

  while (!SerialBT.connect("Button_1")) {
    Serial.println("Failed to connect, retrying...");
    delay(1000);
  }

  Serial.println("Connected to Button_1");
}

void loop() {
  // Send data
  SerialBT.println("Button_2");
  delay(1000);

  // Read incoming data
  if (SerialBT.available()) {
    String receivedData = SerialBT.readString();
    Serial.println("Received: " + receivedData);
  }
}
