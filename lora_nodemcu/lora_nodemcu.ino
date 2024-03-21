// For NodeMCU (ESP8266) with LoRa SX1278 Module
#include <SPI.h>
#include <LoRa.h>

#define SS_PIN 15
#define RST_PIN 16
#define DI0_PIN 4

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.onReceive(receiveEvent);
}

void loop() {
  // Nothing to do here, all actions are handled in receiveEvent
}

void receiveEvent(int packetSize) {
  if (packetSize == 0) return;

  Serial.println("Receiving packet...");
  while (LoRa.available()) {
    Serial.print(LoRa.read(), HEX);  // Print the raw byte value in hexadecimal
    Serial.print(" ");
  }
  // Read incoming data and store it in a buffer
 // char incomingMessage[packetSize];
  //int i = 0;
 // while (LoRa.available()) {
 //   incomingMessage[i++] = (char)LoRa.read();
 // }
 // incomingMessage[i] = '\0'; // Add null terminator to make it a valid string

  // Print the received message
  Serial.println("Received message: ");
 // Serial.println(incomingMessage);
}
