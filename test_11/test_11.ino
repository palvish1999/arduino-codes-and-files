#include <SPI.h>
#include <RH_RF95.h>

#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 2

RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available

  if (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");
}

void loop() {
  // Sending messages
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    Serial.print("Sending message: ");
    Serial.println(message);
    
    // Send a message
    rf95.send((uint8_t *)message.c_str(), message.length());
    rf95.waitPacketSent();
  }

  // Receiving messages
  if (rf95.available()) {
    // Should be a message for us now   
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len)) {
      Serial.print("Received message: ");
      Serial.println((char*)buf);
    }
  }
}
