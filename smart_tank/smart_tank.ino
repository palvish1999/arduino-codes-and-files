// Include the necessary libraries
#include <ESP8266WiFi.h>

// Pin definitions
#define FLOW_SENSOR_PIN D1         // Pin connected to the flow sensor
#define ULTRASONIC_TRIG_PIN D2     // Pin connected to the ultrasonic sensor trigger
#define ULTRASONIC_ECHO_PIN D3     // Pin connected to the ultrasonic sensor echo
#define RELAY_PIN D4               // Pin connected to the relay module

// Flow sensor variables
volatile int flowPulseCount = 0;
float flowRate = 0;

// Ultrasonic sensor variables
long duration;
int distance;

// WiFi credentials
const char* ssid = "mabzone.net";
const char* password = "Cisco@#0912";

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);

  // Connect to WiFi
  //connectToWiFi();
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize pins
  pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
  pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  
  
  // Attach interrupt to flow sensor pin
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, FALLING);
}


 


void loop() {
  // Calculate flow rate in liters per minute
  flowRate = (flowPulseCount / 7.5) / 1000;

  // Print flow rate
  Serial.print("Flow Rate: ");
  Serial.print(flowRate);
  Serial.println(" L/min");

  // Measure water level using ultrasonic sensor
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm

  // Print water level
  Serial.print("Water Level: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Control motor based on water level and flow rate
  if (distance < 80 && flowRate < 0.1) { // Adjust threshold distance as needed
    // Water level is below threshold and no incoming water supply, turn on the motor
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    // Water level is at threshold or incoming water supply detected, turn off the motor
    digitalWrite(RELAY_PIN, LOW);
  }

  // Reset flow pulse count
  flowPulseCount = 0;

  // Wait for a moment
  delay(1000);
}

// Function to handle flow sensor interrupts
void pulseCounter() {
  flowPulseCount++;
}

// Function to connect to WiFi
