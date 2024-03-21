#include<ESP8266WiFi.h>   //   include ESP8266 library
const char* ssid= "mabzone.net";    // wifi name
const char* pass= "Cisco@#0912";  // wifi password


void setup() {
  Serial.begin(115200);   // Initialaztion Serial monitor  with 115200 bps
  WiFi.begin(ssid,pass);  // Wifi Initialization with SSID and PASSWORD
  Serial.print("Connecting to ");
  Serial.print(ssid);  // Print connecting to Wifi name
 // here is waiting to connect internet
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println(" ");
  Serial.println("connected succesfully");
  Serial.print("IP Sddrss is  ");
  Serial.println(WiFi.localIP());  // print IP address of Node MCU
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
