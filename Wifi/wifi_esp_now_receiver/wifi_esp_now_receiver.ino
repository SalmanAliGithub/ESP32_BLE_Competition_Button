#include <esp_now.h>
#include <WiFi.h>

int int_value;

// Callback function when data is received
void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
    memcpy(&int_value, incomingData, sizeof(int_value));
    Serial.print("Data Received: ");
    Serial.println(len);
    Serial.print("Integer received: ");
    Serial.println(int_value);
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_MODE_STA);

    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register for a callback function that will be called when data is received
    esp_now_register_recv_cb(onDataRecv);
}

void loop() {
  unsigned long timeMillis = millis();

  Serial.print("Uptime of this is: ");
  Serial.println(timeMillis);
  delay(1000);
    // Empty loop
}
