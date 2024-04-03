#include <ESP8266WiFi.h>
#include <WiFiManager.h>          // Include the Wi-FiManager library

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  
  // Initialize Wi-Fi manager
  WiFiManager wifiManager;
  
  // Uncomment the following line if you want to reset settings in case of configuration portal failure
  // wifiManager.resetSettings();
  
  // Start Wi-Fi manager
  wifiManager.autoConnect("ESP8266AP"); // Start a Wi-Fi access point if configuration fails

  // Print local IP address
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Send a standard HTTP response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  // Output the sensor data here
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>ESP8266 P2P Communication</title></head>");
  client.println("<body>");
  client.println("<h1>Hello from ESP8266!</h1>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
}
