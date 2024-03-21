#include <SPI.h>
#include <LoRa.h>

#define DIO0 2
#define DIO1 3
#define NSS 10

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize LoRa module
  LoRa.setPins(NSS, DIO0, DIO1);
  if (!LoRa.begin(868E6)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (1);
  }

  // Set DIO0 pin as input for interrupt
  pinMode(DIO0, INPUT);
  attachInterrupt(digitalPinToInterrupt(DIO0), onReceive, RISING);

  Serial.println("LoRa initialized.");
}

void loop() {
  // Example of sending data
  String message = "Hello, World!";
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
  delay(1000);
}

//void onReceive() {
  // Example of receiving data
  //while (LoRa.available()) {
   // String received = LoRa.readString();
  //  Serial.print("Received: ");
  //  Serial.println(received);
  }
}
