#include <RHReliableDatagram.h>
#include <RH_RF95.h>

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2

// Define LoRa module pins
#define LORA_CS_PIN 10
#define LORA_RST_PIN 9
#define LORA_IRQ_PIN 2

RH_RF95 rf95(LORA_CS_PIN, LORA_IRQ_PIN);
RHReliableDatagram manager(rf95, SERVER_ADDRESS);

void setup() {
  Serial.begin(9600);
  if (!manager.init()) {
    Serial.println("LoRa initialization failed!");
    while (1);
  }
  rf95.setFrequency(433.0);
  Serial.println("LoRa receiver ready!");
}

void loop() {
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if (manager.recvfromAck(buf, &len)) {
    Serial.print("Received message: ");
    Serial.println((char*)buf);
  }
}
