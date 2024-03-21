#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


//#define BLYNK_TEMPLATE_ID "TMPL4lFTqHgoR"
//#define BLYNK_TEMPLATE_NAME "flow sensor data"
#define BLYNK_AUTH_TOKEN "oWTM8CEc9MPrFN4vVXupTqN5C8RIGTmk"



//char auth[] = "YourAuthToken"; // Blynk authentication token
char ssid[] = "mabzone.net";  // Your WiFi SSID
char pass[] = "Cisco@#0912"; // Your WiFi password

#define FLOW_SENSOR_PIN D1 // Pin connected to YF-S201 flow sensor

volatile int flowFrequency; // Measures flow frequency
unsigned int flowMilliLitres; // Measures flow in millilitres
unsigned long totalMilliLitres; // Measures total flow in millilitres
unsigned long oldTime;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(FLOW_SENSOR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), flowPulse, FALLING);

  oldTime = millis();
}

void loop()
{
  Blynk.run();
  unsigned long currentTime = millis();
  // Every second, calculate and display flow rate and total flow
  if (currentTime - oldTime > 1000)
  {
    float flowRate = ((1000.0 / (currentTime - oldTime)) * flowFrequency) / 7.5;
    float totalLitres = totalMilliLitres / 1000.0;
    Serial.print("Flow rate: ");
    Serial.print(flowRate);
    Serial.print(" L/min");
    Serial.print("  Total flow: ");
    Serial.print(totalLitres);
    Serial.println(" Litres");
    oldTime = currentTime;
  }
}

void flowPulse()
{
  flowFrequency++;
  flowMilliLitres = (flowFrequency / 7.5); // Calculate flow in millilitres
  totalMilliLitres += flowMilliLitres;
  Blynk.virtualWrite(V1, totalMilliLitres); // Send total flow to Blynk
}
