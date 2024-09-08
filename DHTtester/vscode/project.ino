#include <DHT.h>

// Define pin for DHT sensor
#define DHT_PIN 2
#define DHT_TYPE DHT11

// Initialize DHT sensor object
DHT dht(DHT_PIN, DHT_TYPE);

// Pin for controlling the relay
const int RELAY_PIN = 9;  // Adjust this value if you're using a different pin

// Temperature and humidity thresholds to trigger the relay
const float TEMPERATURE_THRESHOLD = 25.0;  // Adjust this value as needed
const float HUMIDITY_THRESHOLD = 70.0;  // Adjust this value as needed

void setup() {
  Serial.begin(9600);
  Serial.println(F("Sensor Data"));

  // Set relay pin as output and initially turn it off (deactivated)
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Ensure relay is initially inactive

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  // Delay for sensor readings
  delay(2000);

  // Read sensor data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();  // Assuming Celsius (dht.readTemperature(true) for Fahrenheit)

  // Error handling for sensor readings
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Display sensor readings
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C"));

  // Check sensor readings and control the relay (consider both temperature and humidity)
  if (temperature >= TEMPERATURE_THRESHOLD || humidity >= HUMIDITY_THRESHOLD) {
    Serial.println(F("Temperature or humidity threshold reached. Activating relay."));
    digitalWrite(RELAY_PIN, LOW);  // Turn on the relay (open the circuit)
  } else {
    Serial.println(F("Both temperature and humidity below thresholds. Deactivating relay."));
    digitalWrite(RELAY_PIN, HIGH);  // Keep the relay off (closed circuit)
  }
}
