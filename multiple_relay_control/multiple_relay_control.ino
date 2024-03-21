#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

const char* ssid = "mabzone.net";
const char* password = "Cisco@#0912";

WebSocketsServer webSocket = WebSocketsServer(81); // Create a WebSocket server on port 81

const int relayPin1 = D1; // Define the pin connected to relay 1
const int relayPin2 = D2; // Define the pin connected to relay 2
const int relayPin3 = D3; // Define the pin connected to relay 3
const int relayPin4 = D4; // Define the pin connected to relay 4

void setup() {
  pinMode(relayPin1, OUTPUT); // Set the relay pins as outputs
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  
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
      if (strcmp((String*)payload, "on1") == 0) {
        digitalWrite(relayPin1, HIGH); // Turn on relay 1
      } else if (strcmp((String*)payload, "off1") == 0) {
        digitalWrite(relayPin1, LOW); // Turn off relay 1
      } else if (strcmp((char*)payload, "on2") == 0) {
        digitalWrite(relayPin2, HIGH); // Turn on relay 2
      } else if (strcmp((char*)payload, "off2") == 0) {
        digitalWrite(relayPin2, LOW); // Turn off relay 2
      } else if (strcmp((char*)payload, "on3") == 0) {
        digitalWrite(relayPin3, HIGH); // Turn on relay 3
      } else if (strcmp((char*)payload, "off3") == 0) {
        digitalWrite(relayPin3, LOW); // Turn off relay 3
      } else if (strcmp((char*)payload, "on4") == 0) {
        digitalWrite(relayPin4, HIGH); // Turn on relay 4
      } else if (strcmp((char*)payload, "off4") == 0) {
        digitalWrite(relayPin4, LOW); // Turn off relay 4
      }
      break;
    default:
      break;
  }
}
