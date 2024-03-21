// Include the required libraries
#include <ESP8266WiFi.h>

// Define the pin connections
const int pirPin = D1; // PIR sensor output connected to pin D1
const int buzzerPin = D2; // Buzzer connected to pin D2

// Define WiFi credentials
const char* ssid = "mabzone.net";
const char* password = "Cisco@#0912";

// Initialize the WiFi client object
WiFiClient client;

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(115200);

  // Initialize the PIR sensor pin as input
  pinMode(pirPin, INPUT);

  // Initialize the buzzer pin as output
  pinMode(buzzerPin, OUTPUT);

  // Connect to WiFi network
  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read the PIR sensor value
  int pirValue = digitalRead(pirPin);

  if (pirValue == HIGH) {
    // Motion detected
    Serial.println("Motion Detected!");
    activateBuzzer();
    delay(1000); // Delay to avoid continuous triggering
  }
}

void activateBuzzer() {
  // Activate the buzzer
  digitalWrite(buzzerPin, HIGH);
  delay(500); // Buzz for 0.5 seconds
  digitalWrite(buzzerPin, LOW);
}
