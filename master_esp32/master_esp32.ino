#include "BluetoothSerial.h"

BluetoothSerial SerialBT;


void setup() {
  Serial.begin(115200);
  SerialBT.begin("Button_1");
  Serial.println("Button_1 ready for connection");
}

void loop() {
  SerialBT.println("Button_1");
  delay(1000);
  if (SerialBT.available()) {
    Serial.println(SerialBT.read());
  }
}