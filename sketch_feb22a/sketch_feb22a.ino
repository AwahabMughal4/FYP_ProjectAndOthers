// HelloESP32.ino

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 bps
}

void loop() {
  Serial.println("Hello"); // Print "Hello" to the Serial Monitor
  delay(1000); // Wait for 1 second
}
