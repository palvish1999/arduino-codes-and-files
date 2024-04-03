#include <ESP8266WiFi.h>
#include <WiFiManager.h>

char ssid[] = "mabzone.net";
char password[] = "Cisco@#0912";

char server[] = "192.168.1.181";
int port = 12345;

WiFiClient client;

#define RELAY_PIN 2 // Change this to the pin connected to the relay

bool relayState = false;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Initialize WiFiManager
  //WiFiManager wifiManager;

  // Uncomment the line below to reset WiFi credentials
  //wifiManager.resetSettings();

  // Start WiFiManager
  //wifiManager.autoConnect("AutoConnectAP");

  Serial.println("Connected to WiFi");

  // Connect to server
  Serial.println("Connecting to server...");
  if (client.connect(server, port)) {
    Serial.println("Connected to server");
  } else {
    Serial.println("Connection failed");
  }
}

void loop() {
  // Raspberry Pi control over sockets
  if (client.available()) {
    char command = client.read();
    if (command == '1') {
      relayState = true;
    } else if (command == '0') {
      relayState = false;
    }
    digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
    Serial.println(relayState ? "Relay ON" : "Relay OFF");
  }

  // Arduino control over serial
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == '1') {
      digitalWrite(RELAY_PIN, HIGH); // Turn on relay
    } else if (command == '0') {
      digitalWrite(RELAY_PIN, LOW); // Turn off relay
    }
  }
}
