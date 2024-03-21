#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>





// Set the credentials of your Wi-Fi network
char ssid[] = "mabzone.net";
char pass[] = "Cisco@#0912";

// Pins connected to the relay modules
#define RELAY1_PIN D1
#define RELAY2_PIN D2
#define RELAY3_PIN D3
#define RELAY4_PIN D4

void setup() {
  // Debug console
  Serial.begin(9600);

  // Initialize Blynk
  Blynk.begin("6O8HBdvRDUgCzUCZ8ZS1o-EgqgNaAZuu", ssid, pass);

  // Initialize the relay pins as output
  pinMode(RELAY1_PIN, OUTPUT);                           
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);
  pinMode(RELAY4_PIN, OUTPUT);
}

void loop() {
  Blynk.run();
}

// Function to control relay 1
BLYNK_WRITE(V1) {
  int state = param.asInt();
  digitalWrite(RELAY1_PIN, state);
}

// Function to control relay 2
BLYNK_WRITE(V2) {
  int state = param.asInt();
  digitalWrite(RELAY2_PIN, state);
}

// Function to control relay 3
BLYNK_WRITE(V3) {
  int state = param.asInt();
  digitalWrite(RELAY3_PIN, state);
}

// Function to control relay 4
BLYNK_WRITE(V4) {
  int state = param.asInt();
  digitalWrite(RELAY4_PIN, state);
}
