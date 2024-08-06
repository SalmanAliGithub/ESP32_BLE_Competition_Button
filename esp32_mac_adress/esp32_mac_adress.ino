#include "WiFi.h"

void setup() {
    Serial.begin(115200);

    // Initialize WiFi as Station
    WiFi.mode(WIFI_MODE_STA);

    // Wait for WiFi to initialize
    delay(1000);

    // Print MAC Address
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void loop() {
    // Empty loop
}
