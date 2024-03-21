#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Replace with your WiFi credentials
const char* ssid = "mabzone.net";
const char* password = "Cisco@#0912";

// Replace with your API endpoint
const char* apiEndpoint = "http://localhost:8080";

// Define the pins connected to the relays
const int relayPins[] = {D1, D2, D3, D4};
const int numRelays = sizeof(relayPins) / sizeof(relayPins[0]);

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Initialize GPIO pins for relays
  for (int i = 0; i < numRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW); // Initialize all relays to LOW (off)
  }
}

void loop() {
  // Create JSON object
  StaticJsonDocument<200> jsonDocument;
  
  // Add relay statuses to JSON object
  for (int i = 0; i < numRelays; i++) {
    jsonDocument[String("relay") + String(i + 1)] = digitalRead(relayPins[i]) == HIGH ? "HIGH" : "LOW";
  }

  // Convert JSON object to string
  String jsonString;
  serializeJson(jsonDocument, jsonString);
  Serial.println(jsonString);

  // Send JSON data to API endpoint
  WiFiClient client;
  HTTPClient http;
  http.begin(client, apiEndpoint);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(jsonString);
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error sending request. HTTP Response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();

  delay(5000); // Adjust delay as needed
}
