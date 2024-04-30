#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

// Replace with your WiFi credentials
const char* ssid = "mabzone.net";
const char* password = "Cisco@#0912";

// Flask server endpoint
const char* serverHost = "0.0.0.0";
const int serverPort = 5000;
const char* endpoint = "/data";

WiFiClient wifiClient;

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
}

void loop() {
  // Send data via HTTP GET
  sendDataGet();

  // Send data via HTTP POST
  sendDataPost();

  delay(5000);
}

void sendDataGet() {
  HTTPClient http;

  String url = "http://" + String(serverHost) + ":" + String(serverPort) + endpoint;
  url += "?param1=value1&param2=value2";

  http.begin(wifiClient,url);

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP GET request successful, Response:");
    Serial.println(response);
  } else {
    Serial.print("Error on HTTP GET request: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void sendDataPost() {
  HTTPClient http;

  String url = "http://" + String(serverHost) + ":" + String(serverPort) + endpoint;

  http.begin(wifiClient,url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String postData = "param1=vkgu&param2=jhuy";

  int httpResponseCode = http.POST(postData);
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP POST request successful, Response:");
    Serial.println(response);
  } else {
    Serial.print("Error on HTTP POST request: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
