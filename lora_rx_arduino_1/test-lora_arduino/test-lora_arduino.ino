#include <SPI.h>
#include <LoRa.h>

#define SS 10     // Define SS pin
#define RST 9     // Define RESET pin
#define DI0 2     // Define DIO0 pin

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize LoRa module
  LoRa.setPins(SS, RST, DI0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (1);
  }

  Serial.println("LoRa init succeeded.");

LoRa.setSpreadingFactor(12); // ranges from 6-12,default 7 see API docs
LoRa.setSignalBandwidth(62.5E3 ); // for -139dB (page - 112)
LoRa.setCodingRate4(8); // for -139dB (page - 112)
//LoRa.setSyncWord(SyncWord);
/*
Serial.print("current spreading factor : ");
Serial.println(LoRa.getSpreadingFactor());
Serial.print("current bandwidth : ");
Serial.println(LoRa.getSignalBandwidth());
Serial.println("LoRa init succeeded.");
*/
}



void loop() {
  int dataToSend = 1; // Integer data to send
  Serial.println("Sending message...");

  // Convert integer to string
   int dataStr = int(dataToSend);

  // Send the message
  LoRa.beginPacket();
  LoRa.print(dataStr);
  LoRa.endPacket();

  Serial.println("Message sent.");

  delay(10000); // Send message every 1 second
}
