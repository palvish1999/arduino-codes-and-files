#define BLYNK_TEMPLATE_ID "TMPL4B7YNTnkU"
#define BLYNK_TEMPLATE_NAME "relay state"
//#define BLYNK_AUTH_TOKEN "OEd2tnd7YHk5c-AAXhN9-3L2aV209RuQ"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266HTTPClient.h>  // Include the HTTP Client library

#define BLYNK_AUTH_TOKEN "OEd2tnd7YHk5c-AAXhN9-3L2aV209RuQ"  // Update with your Blynk Auth Token
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "mabzone.net";  // Update with your Wi-Fi network name
char pass[] = "Cisco@#0912";     // Update with your Wi-Fi password

#define RELAY_PIN D1  // Digital pin to which the relay is connected
#define FLOW_IN_PIN D2  // Digital pin to which the flow in sensor is connected
#define FLOW_OUT_PIN D3  // Digital pin to which the flow out sensor is connected

BlynkTimer timer;

void turnRelayOn() {
  digitalWrite(RELAY_PIN, HIGH);
}

void turnRelayOff() {
  digitalWrite(RELAY_PIN, LOW);
}

void setup() {
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  pinMode(RELAY_PIN, OUTPUT);
  turnRelayOff();

  // Initialize flow sensor pins
  pinMode(FLOW_IN_PIN, INPUT);
  pinMode(FLOW_OUT_PIN, INPUT);

  timer.setInterval(10000L, []() {
    if (!Blynk.connected()) {
      Serial.println("Disconnected from Blynk server, attempting to reconnect...");
      Blynk.connect();
    }
    
    // Insert data into MS SQL Server
    insertDataToSqlServer();
  });
}

void loop() {
  Blynk.run();
  timer.run();
}

void insertDataToSqlServer() {
  float flowIn = digitalRead(FLOW_IN_PIN); // Replace with actual code to read flow in sensor
  float flowOut = digitalRead(FLOW_OUT_PIN); // Replace with actual code to read flow out sensor
  int relayState = digitalRead(RELAY_PIN);

  // Your MS SQL Server 2019 database information
  String serverAddress = "192.168.1.16"; // Replace with your server address
  String dbUsername = "palvish"; // Replace with your database username
  String dbPassword = "palvish"; // Replace with your database password
  String dbName = "PunchData"; // Replace with your database name
  
  // Convert flowIn and flowOut to String
  String flowInStr = String(flowIn);
  String flowOutStr = String(flowOut);

  // Construct the SQL query string
  String query = "INSERT INTO pump_control_data (relay_state, flow_in, flow_out) VALUES (" + String(relayState) + ", " + flowInStr + ", " + flowOutStr + ")";

  // Create HTTP client instance
  HTTPClient http;

  // Specify the server address, port, and URI
  http.begin(Client, "http://" + serverAddress + ":27017/");

  // Set the authorization header
  http.setAuthorization(dbUsername.c_str(), dbPassword.c_str());

  // Set content type header
  http.addHeader("Content-Type", "application/json");

  // Execute the SQL query
  int httpResponseCode = http.POST(query);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("HTTP Error: ");
    Serial.println(httpResponseCode);
  }

  // End HTTP connection
  http.end();
}
