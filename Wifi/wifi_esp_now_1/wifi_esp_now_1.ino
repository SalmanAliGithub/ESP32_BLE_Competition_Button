#include <esp_now.h>
#include <WiFi.h>

const int buttonPin = 14; // GPIO for button
const int ledPin = 2;
const int externalLedPin = 25;
const int buzzerPin = 12;
bool buttonPressed = false;
bool receivedFirst = false;
bool checked = false;

uint8_t broadcastAddress[] = {0xE8, 0x6B, 0xEA, 0xD0, 0xDC, 0xD8}; 

esp_now_peer_info_t peerInfo;

unsigned long startMillis = 0;
unsigned long currentMillis;
const unsigned long interval = 2000;

void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
    if (!buttonPressed) {
        digitalWrite(ledPin, LOW);
        digitalWrite(externalLedPin, LOW);
        digitalWrite(buzzerPin, LOW);
        receivedFirst = true; // The other button tapped first
        Serial.println("The other button tapped first.");
    }
}

void setup() {
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    pinMode(externalLedPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    digitalWrite(externalLedPin, LOW);
    digitalWrite(buzzerPin, LOW);

    Serial.begin(115200);
    WiFi.mode(WIFI_MODE_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_recv_cb(onDataRecv);

    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
}

void loop() {
    currentMillis = millis();

    if (receivedFirst && !checked) {
        startMillis = currentMillis;
        checked = true;
    }

    if (receivedFirst && (currentMillis - startMillis < interval)) {
        digitalWrite(ledPin, LOW);
        digitalWrite(externalLedPin, LOW);
        digitalWrite(buzzerPin, LOW);
        Serial.print(". ");
        Serial.print((currentMillis - startMillis) / 1000);
    } else if (receivedFirst && (currentMillis - startMillis >= interval)) {
        receivedFirst = false;
        checked = false;
        Serial.println("Ready to accept new comparison.");
    }

    if (digitalRead(buttonPin) == LOW && !buttonPressed && (currentMillis - startMillis >= interval) ) {
        delay(20);
        Serial.println();
        buttonPressed = true;
        digitalWrite(ledPin, HIGH);
        digitalWrite(externalLedPin, HIGH);
        digitalWrite(buzzerPin, HIGH); // Turn on LED/Buzzer
        esp_now_send(broadcastAddress, (uint8_t *)"pressed", 7);
        Serial.println("This button tapped first.");
        receivedFirst = false;
        checked = false;
        delay(500);
        digitalWrite(ledPin, LOW);
        digitalWrite(externalLedPin, LOW);
        digitalWrite(buzzerPin, LOW);
    }
    buttonPressed = false;
}
