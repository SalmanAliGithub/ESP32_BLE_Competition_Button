#include <esp_now.h>
#include <WiFi.h>

int int_value;
float float_value;

unsigned long timeMillis;

uint8_t broadcastAddress[] = {0xA0, 0xA3, 0xB3, 0xAA, 0xFE, 0x90};

esp_now_peer_info_t peerInfo;

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\n Last packet status: \t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Success");
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_MODE_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP NOW");
        return;
    }

    esp_now_register_send_cb(onDataSent);

    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }

}

void loop() {
    // int_value = random(1, 20);
    timeMillis = millis();

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &timeMillis, sizeof(int_value));
    if (result == ESP_OK) {
        Serial.println("Sending Confirmed");
    }
    else {
        Serial.println("Sending Error!");
    }

    delay(1000);

}