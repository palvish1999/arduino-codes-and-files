#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

const char* ssid = "mabzone.net";
const char* password = "Cisco@#0912";
const char* webSocketServer = "192.168.1.181";
const int webSocketPort = 5000; // WebSocket port on Raspberry Pi

// Define relay pin
const int relayPin = D1;

WiFiClient client;
WebSocketsClient webSocketClient;

void setup() {
    Serial.begin(9600);
    delay(100);
    

    // Initialize relay pin as an output
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW); // Ensure relay is initially off

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    if (client.connect(webSocketServer, webSocketPort)) {
        Serial.println("Connected to WebSocket server");
    }
}

void loop() {
    if (client.connected()) {
        // Check if there is data available from the WebSocket server
        while (client.available()) {
            String data = client.readStringUntil('\n');
            Serial.println("Received data from Raspberry Pi: " + data);
            // Process data as needed

            // Check if the received data contains relay control commands
            if (data == "turnOnRelay") {
                digitalWrite(relayPin, HIGH); // Turn on relay
                Serial.println("Relay turned on");
            } else if (data == "turnOffRelay") {
                digitalWrite(relayPin, LOW); // Turn off relay
                Serial.println("Relay turned off");
            }
        }

        // Send data to Raspberry Pi
        String dataToSend = "Hello from Arduino!";
        webSocketClient.sendTXT(dataToSend);
        delay(1000);
    } else {
        Serial.println("Connection to WebSocket server failed!");
        delay(5000);
    }
}
