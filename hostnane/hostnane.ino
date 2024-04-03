#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "mabzone.net";
const char* password = "Cisco@#0912";
const char* serverAddress = "http://192.168.1.179/upload"; // Change this to the Raspberry Pi's IP address

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Read the text file
  File file = SPIFFS.open("‪C:\\Users\\s.palvish\\Desktop\\esp8266.txt", "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }
  
WiFiClient wifiClient;
   
HTTPClient http;

  // Use the HTTPClient begin function with URL
  if (!http.begin(wifiClient,serverAddress)) {
    Serial.println("Failed to begin HTTP connection");
    return;
  }

  // Send the file contents as POST request
  int httpCode = http.POST(file.readString());
  if (httpCode > 0) {
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  
  delay(5000); // Send every 5 seconds (adjust as needed)
}
