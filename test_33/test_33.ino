#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver Test");

  // Replace the operating frequency of your shield here.
  // 915E6 (US902-928) / 868E6 (EU863-870) / 433E6 (EU433)

  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // see if a packet was received
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // if a packet size is defined, a packet was received
    Serial.println("");
    Serial.println("Received packet!");

    // read the packet
    String message = "";
    while (LoRa.available()) {
      message += (char)LoRa.read();
    }

    // print the Packet and RSSI
    Serial.println("Message: " + message);
    Serial.print("RSSI: ");
    Serial.println(LoRa.packetRssi());
  }

  delay(5000);
}
