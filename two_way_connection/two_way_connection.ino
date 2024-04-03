#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "mabzone.net";
const char* password = "Cisco@#0912";
const int esp8266_port = 80; // Choose a port for the ESP8266 server
const int raspberry_pi_port = 12345; // Choose a port for the Raspberry Pi server
const char* raspberry_pi_ip = "192.168.1.181"; // Replace with the Raspberry Pi's IP address

WiFiServer esp8266_server(esp8266_port);
WiFiClient esp8266_client;
WiFiClient raspberry_pi_client;

void setup() {
  Serial.begin(115200);
  delay(2000);

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

  // Start the ESP8266 server
  esp8266_server.begin();
  Serial.println("ESP8266 Server started");
}

void loop() {
  // Check for incoming connections from Raspberry Pi client
  if (!raspberry_pi_client.connected()) {
    raspberry_pi_client.connect(raspberry_pi_ip, raspberry_pi_port);
    if (raspberry_pi_client.connected()) {
      Serial.println("Connected to Raspberry Pi");
    }
  }

  // Check for incoming connections from Raspberry Pi server
  if (!esp8266_client.connected()) {
    esp8266_client = esp8266_server.available();
    if (esp8266_client.connected()) {
      Serial.println("Connected to Raspberry Pi client");
    }
  }

  // Check for data from Raspberry Pi client
  if (esp8266_client.available()) {
    String data = esp8266_client.readStringUntil('\n');
    Serial.println("Received from Raspberry Pi client: " + data);
  }

  // Check for data from Raspberry Pi server
  if (raspberry_pi_client.available()) {
    String data = raspberry_pi_client.readStringUntil('\n');
    Serial.println("Received from Raspberry Pi server: " + data);
  }

  // Check for user input
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    // Send data to Raspberry Pi server
    raspberry_pi_client.println(data);
    Serial.println("Sent to Raspberry Pi server: " + data);
  }
}
