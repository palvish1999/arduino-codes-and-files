#define BLYNK_TEMPLATE_ID "TMPL4B7YNTnkU"
#define BLYNK_TEMPLATE_NAME "relay state"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

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
  });
}

void loop() {
  Blynk.run();
  timer.run();

  // Read flow sensor values
  float flowIn = readFlowSensor(FLOW_IN_PIN); // Replace with actual function to read flow in sensor
  float flowOut = readFlowSensor(FLOW_OUT_PIN); // Replace with actual function to read flow out sensor

  //Serial.print(flowIn);
 // Serial.print(flowOut);
  // Convert flow sensor values to flow rates in L/min (example conversion)
  float flowInRate = convertToLitersPerMinute(flowIn);
  float flowOutRate = convertToLitersPerMinute(flowOut);

  // Send flow rates to Blynk
  Blynk.virtualWrite(V1, flowInRate); // Assuming V1 is the virtual pin for flow in rate
  Blynk.virtualWrite(V2, flowOutRate); // Assuming V2 is the virtual pin for flow out rate

  Serial.print(flowInRate);
  Serial.print(flowOutRate); 
}

float readFlowSensor(int pin) {
  // Function to read flow sensor value from specified pin
  // Replace with actual implementation to read flow sensor value
  // Example: return analogRead(pin);
  return 0.0; // Add a placeholder return statement
}

float convertToLitersPerMinute(float sensorValue) {
  // Function to convert sensor value to flow rate in liters per minute
  // Replace with actual conversion formula based on sensor specifications
  // Example: return sensorValue * 0.1; // Assuming sensor output is linear and calibration factor is 0.1
  return 0.0; // Add a placeholder return statement
}

BLYNK_WRITE(V0) {
  int relayState = param.asInt();
  if (relayState == HIGH) {
    turnRelayOn();
  } else {
    turnRelayOff();
  }
}
