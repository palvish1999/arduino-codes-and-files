const int relayPin = D1; // Pin connected to the relay

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Set relay off initially
  
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    
    // Toggle relay state based on user input
    if (input == '1') {
      digitalWrite(relayPin, HIGH); // Set relay ON
      Serial.println("Relay turned ON");
    } else if (input == '0') {
      digitalWrite(relayPin, LOW); // Set relay OFF
      Serial.println("Relay turned OFF");
    } else {
      Serial.println("Invalid input. Enter '1' to turn ON, '0' to turn OFF.");
    }
  }
}
