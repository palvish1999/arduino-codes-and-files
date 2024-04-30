#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "mabzone.net";
const char* password = "Cisco@#0912";
const int raspberry_pi_port = 12345; // Choose a port for the Raspberry Pi server
const int esp8266_port = 80; // Choose a port for the ESP8266 server
const char* raspberry_pi_ip = "192.168.1.181"; // Replace with the Raspberry Pi's IP address

WiFiClient esp8266_client;
WiFiClient raspberry_pi_client;
WiFiServer esp8266_server(esp8266_port);

void handleUpdateWiFi(WiFiClient client) {
  String ssid = client.readStringUntil('\n');
  String password = client.readStringUntil('\n');

  // Remove trailing newline characters
  ssid.trim();
  password.trim();

  // Update WiFi credentials
  if (ssid.length() > 0 && password.length() > 0) {
    WiFi.begin(ssid.c_str(), password.c_str());
    delay(1000);
    if (WiFi.status() == WL_CONNECTED) {
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/plain");
      client.println();
      client.println("WiFi credentials updated successfully!");
    } else {
      client.println("HTTP/1.1 500 Internal Server Error");
      client.println("Content-Type: text/plain");
      client.println();
      client.println("Failed to update WiFi credentials");
    }
  } else {
    client.println("HTTP/1.1 400 Bad Request");
    client.println("Content-Type: text/plain");
    client.println();
    client.println("Invalid request: SSID and password are required");
  }

  client.stop(); // Close the connection
}

void setup() {
  Serial.begin(115200);
  delay(500);

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
    // Wait for data to be available
    while (!esp_client.available()) {
      delay(1);
    }

    // Read the first line of HTTP request
    String request = esp_client.readStringUntil('\r');
    esp_client.flush();

    // Check if it's an update WiFi request
    if (request.indexOf("/update_wifi") != -1) {
      handleUpdateWiFi(esp_client);
    }

    esp_client.stop();
    Serial.println("ESP8266 client disconnected");
  }
}
