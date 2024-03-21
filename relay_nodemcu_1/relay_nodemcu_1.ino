#define BLYNK_TEMPLATE_ID "TMPL4rVybwe-K"
#define BLYNK_TEMPLATE_NAME "home automation"
#define BLYNK_AUTH_TOKEN "6O8HBdvRDUgCzUCZ8ZS1o-EgqgNaAZuu"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// WiFi credentials
char ssid[] = "mabzone.net";
char pass[] = "Cisco@#0912";

// Pins connected to the relays
const int relayPins[] = {D1, D2, D3, D4};
const int numRelays = 4;

void setup() {
  Serial.begin(9600);
  
  Blynk.begin(auth, ssid, pass);

  // Set relay pins as outputs
  for (int i = 0; i < numRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
  }

  // Print the IP address assigned to your NodeMCU
  Serial.println(WiFi.localIP());
}

void loop() {
  Blynk.run();
}

// Blynk virtual pin handler for controlling individual relays
BLYNK_WRITE(V1) {
  int value = param.asInt();
  digitalWrite(relayPins[0], value);
}

BLYNK_WRITE(V2) {
  int value = param.asInt();
  digitalWrite(relayPins[1], value);
}

BLYNK_WRITE(V3) {
  int value = param.asInt();
  digitalWrite(relayPins[2], value);
}

BLYNK_WRITE(V4) {
  int value = param.asInt();
  digitalWrite(relayPins[3], value);
}
