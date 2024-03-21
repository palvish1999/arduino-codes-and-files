#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>

String outgoing;
byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xBB;     // address of this device
byte destination = 0xFF;      // destination to send to
long lastSendTime = 0;        // last send time
int interval = 2000;          // interval between sends

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Two-Way Communication");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  if (millis() - lastSendTime > interval) {
    String message = "1,2,3,4,5";
    Serial.println("Sending message: " + message);
    sendMessage(message);
    lastSendTime = millis(); // timestamp the message
    interval = random(1000) + 2000; // 2-3 seconds
  }
  // parse for a packet, and call onReceive with the result:
  onReceive();
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}

void onReceive() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // read packet header bytes:
    int recipient = LoRa.read();          // recipient address
    byte sender = LoRa.read();            // sender address
    byte incomingMsgId = LoRa.read();     // incoming msg ID
    byte incomingLength = LoRa.read();    // incoming msg length

    // received a packet
    Serial.print("Received packet: ");
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    delay(1000);
  }
}
