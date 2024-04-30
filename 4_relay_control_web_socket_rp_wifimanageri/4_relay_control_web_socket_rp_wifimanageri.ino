#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> // Include the WiFiManager library

const int raspberry_pi_port = 5000; // Choose a port for the Raspberry Pi server
const int esp8266_port = 80;        // Choose a port for the ESP8266 server
const char *raspberry_pi_ip = "192.168.1.181"; // Replace with the Raspberry Pi's IP address

const int relayPins[] = {D1, D2, D3, D4}; // GPIO pins connected to relays
const int numRelays = 4;                  // Total number of relays

WiFiClient esp8266_client;
WiFiClient raspberry_pi_client;
WiFiServer esp8266_server(esp8266_port);

void setup() {
  Serial.begin(115200);
  delay(500);

  // Initialize WiFiManager
  WiFiManager wifiManager;
  
  // Uncomment the following line to reset settings (for debugging)
  wifiManager.resetSettings();
  
  // Connect to WiFi network or start configuration portal
  if (!wifiManager.autoConnect("ESP8266AP")) {
    Serial.println("Failed to connect and hit timeout");
    delay(3000);
    // Reset and try again, or continue with default settings
    ESP.reset();
    delay(5000);
  }
  // If you get here, you are connected to WiFi
  Serial.println("WiFi connected");

  // Connect to Raspberry Pi server
  Serial.println("Connecting to Raspberry Pi server");
  if (!raspberry_pi_client.connect(raspberry_pi_ip, raspberry_pi_port)) {
    Serial.println("Connection failed.");
  } else {
    Serial.println("Connected to Raspberry Pi");
  }

  // Start ESP8266 server
  esp8266_server.begin();
  Serial.println("ESP8266 Server started");

  // Initialize relay pins as output
  for (int i = 0; i < numRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
  }
}

void loop() {
  // Check for data from Raspberry Pi server
  if (raspberry_pi_client.available()) {
    String data = raspberry_pi_client.readStringUntil('\n');
    Serial.println("Received from Raspberry Pi server: " + data);
    // Process the received data here if needed
  }

  // Check for incoming connections from ESP8266 client
  WiFiClient esp_client = esp8266_server.available();
  if (esp_client) {
    while (esp_client.connected()) {
      if (esp_client.available()) {
        String data = esp_client.readStringUntil('\n');
        Serial.println("Received from ESP8266 client: " + data);
        // Control relays based on received command
        for (int i = 0; i < numRelays; i++) {
          if (data == "1" + String(i + 1)) {
            digitalWrite(relayPins[i], HIGH); // Turn relay ON
            Serial.println("Relay " + String(i + 1) + " turned ON");
          } else if (data == "0" + String(i + 1)) {
            digitalWrite(relayPins[i], LOW); // Turn relay OFF
            Serial.println("Relay " + String(i + 1) + " turned OFF");
          }
        }
      }
    }
    esp_client.stop();
    Serial.println("ESP8266 client disconnected");
  }
}
