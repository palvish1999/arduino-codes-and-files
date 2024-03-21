#include <SPI.h>
#include <LoRa.h>

#define ss 15
#define rst 16
#define dio0 4

const int buttonPin = 2; // Pin connected to button to send HIGH/LOW signal

void setup() {
  Serial.begin(9600);
  while (!Serial);
  LoRa.setPins(ss, rst, dio0);

  pinMode(buttonPin, INPUT_PULLUP);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed. Check your connections.");
    while (1);
  }
}

void loop() {
  // Read button state
  int buttonState = digitalRead(buttonPin);

  // If button is pressed, send message
  if (buttonState == HIGH) {
    sendMessage("HIGH");
    delay(500); // Debouncing delay
  } else {
    sendMessage("LOW");
    delay(500); // Debouncing delay
  }
}

void sendMessage(String message) {
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
  Serial.println("Message sent: " + message);
}
