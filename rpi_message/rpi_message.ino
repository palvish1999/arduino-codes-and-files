#include <ESP8266WiFi.h>
#include <ArduinoWebsockets.h>
#include <WebSocketsClient.h>

const char* ssid = "mabzone.net";
const char* password = "Cisco@#0912";
const char* serverAddress = "192.168.1.181";
int serverPort = 5000;

WebSocketsClient client;

//void onEventsCallback(WebsocketsEvent event, String data) {
//  if (event == WebsocketsEvent::ConnectionOpened) {
 //   Serial.println("Connected to server");
//  }
//}

void setup() {
  Serial.begin(115200);
  delay(100);

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Connect to WebSocket server
  Serial.println("Connecting to WebSocket server...");
  client.begin(serverAddress, serverPort, "/");
//  client.onEvent(onEventsCallback);
}

void loop() {
  client.loop();

  // Check for incoming WebSocket messages
//  if (client.available()) {
    //WebsocketsMessage message = client.readMessage();
   // Serial.println("Received message: " + message.data());
 // }
}
