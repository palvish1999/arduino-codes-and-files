#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

ESP8266WebServer server(80); // Create a web server on port 80

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Define API endpoint
  server.on("/api/data", HTTP_GET, [](){
    // Create a JSON object
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["sensor"] = "temperature";
    jsonDoc["value"] = 25.5;

    // Serialize JSON object to a string
    String response;
    serializeJson(jsonDoc, response);

    // Send JSON response
    server.send(200, "application/json", response);
  });

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient(); // Handle incoming client requests
}
