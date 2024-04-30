#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

ESP8266WebServer server(80); // Create a web server on port 80

int ledPin = D1; // Assuming the LED is connected to GPIO pin D1

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Define routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient(); // Handle incoming client requests
}

void handleRoot() {
  server.send(200, "text/html", "<h1>ESP8266 Web Server</h1><p><a href='/on'>Turn On LED</a></p><p><a href='/off'>Turn Off LED</a></p>");
}

void handleOn() {
  digitalWrite(ledPin, HIGH); // Turn on the LED
  server.send(200, "text/plain", "LED turned on");
}

void handleOff() {
  digitalWrite(ledPin, LOW); // Turn off the LED
  server.send(200, "text/plain", "LED turned off");
}
