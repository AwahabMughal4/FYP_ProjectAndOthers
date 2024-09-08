#define BLYNK_TEMPLATE_ID "TMPL69U1-y-Wq"
#define BLYNK_TEMPLATE_NAME "Distance Measurement"
#define BLYNK_AUTH_TOKEN "ThhHfTiyI4rD39fUdvc_FOqgrH086O0N"// Replace with your Blynk auth token
#define BLYNK_PRINT Serial

char ssid[] = "IoTs";
char pass[] = "password";

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h> // Use this library

// Ultrasonic sensor pins
#define TRIGGER_PIN 33
#define ECHO_PIN 32

// Number of readings for averaging (increased to 10)
const int numReadings = 10; 

// Array to store readings and variable for sum
int readings[numReadings];
int sum = 0;

// Function to calculate distance in centimeters
int duration; // Declare duration variable

int calculateDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2); // Trigger pulse for 2 microseconds
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); // Maintain high for 10 microseconds (optional)
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2; // Speed of sound in cm/us / 2 (round trip)
}


void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Initialize Blynk connection
  delay(2000); // Optional delay for initialization
}

void loop() {
  Blynk.run(); // Handle Blynk communication

  // Take multiple readings and calculate average
  for (int i = 0; i < numReadings; i++) {
    readings[i] = calculateDistance();
    sum += readings[i];
  }
  int averageDistance = sum / numReadings;

  Serial.print("Average Distance (cm): ");
  Serial.println(averageDistance); // Print to serial monitor for debugging

  Blynk.virtualWrite(V0, averageDistance); // Send averaged distance to Blynk
  delay(100); // Lower delay for faster sampling (adjust as needed)
  sum = 0; // Reset sum for next averaging cycle
}
