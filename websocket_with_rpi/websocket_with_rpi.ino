#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "mabzone.net";
const char* password = "Cisco@#0912";
const int raspberry_pi_port = 12345; // Choose a port for the Raspberry Pi server
const int esp8266_port = 80; // Choose a port for the ESP8266 server
const char* raspberry_pi_ip = "192.168.1.181"; // Replace with the Raspberry Pi's IP address

WiFiClient esp8266_client;
WiFiClient raspberry_pi_server;
WiFiServer esp8266_server(esp8266_port);

const int relayPin = D1; // GPIO pin connected to relay

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Initialize relay pin as output
  pinMode(relayPin, OUTPUT);

  esp8266_server.begin();
  Serial.println("ESP8266 Server started");

  // Connect to Raspberry Pi server
  Serial.println("Connecting to Raspberry Pi server");
  if (!raspberry_pi_server.connect(raspberry_pi_ip, esp8266_port)) {
    Serial.println("Connection failed.");
  } else {
    Serial.println("Connected to Raspberry Pi");
  }
}

void loop() {
  // Check for data from Raspberry Pi server
  if (raspberry_pi_server.available()) {
    String data = raspberry_pi_server.readStringUntil('\n');
    Serial.println("Received from Raspberry Pi server: " + data);

  }
    // Control relay based on received command
  WiFiClient esp_client = esp8266_server.available();
  if (esp_client) {
    while (esp_client.connected()) {
      if (esp_client.available()) {
        String data = esp_client.readStringUntil('\n');
        Serial.println("Received from raspberrypi server: " + data);
        // Control relay based on received command
        if (data == "1") {
          digitalWrite(relayPin, HIGH); // Turn relay ON
          Serial.println("Relay turned ON");
        } else if (data == "0") {
          digitalWrite(relayPin, LOW); // Turn relay OFF
          Serial.println("Relay turned OFF");
        } else {
          Serial.println("Invalid command");
        }
      }
    }
    esp_client.stop();
    Serial.println("ESP8266 client disconnected");
  }

  // Add any additional logic here if needed
}
