#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

const char* ssid = "mabzone.net";
const char* password = "Cisco@#0912";

WebSocketsServer webSocket = WebSocketsServer(81); // Create a WebSocket server on port 81

const int relayPin = D1; // Define the pin connected to the relay

void setup() {
  pinMode(relayPin, OUTPUT); // Set the relay pin as an output
  
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi
  Serial.println();
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Start the WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop(); // Handle WebSocket events
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);
      if (strcmp((char*)payload, "on") == 0) {
        digitalWrite(relayPin, HIGH); // Turn on the relay
      } else if (strcmp((char*)payload, "off") == 0) {
        digitalWrite(relayPin, LOW); // Turn off the relay
      }
      break;
    default:
      break;
  }
}
