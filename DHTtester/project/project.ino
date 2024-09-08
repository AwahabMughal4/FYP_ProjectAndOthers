#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHT_PIN 2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

const int RELAY_PIN = 9;  
const float TEMPERATURE_THRESHOLD = 36;  
const float HUMIDITY_THRESHOLD = 24;     

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float humidity = 0;
float temperature = 0;

unsigned long lastSensorReadTime = 0;
const unsigned long sensorReadInterval = 2000;  
void setup() {
  Serial.begin(9600);
  Serial.println(F("Sensor Data"));
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  
  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();  
  delay(2000);  
  display.clearDisplay();  
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastSensorReadTime >= sensorReadInterval) {
   
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();  

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    lastSensorReadTime = currentMillis; 
  }

  static float lastDisplayedTemperature = 0;
  static float lastDisplayedHumidity = 0;

  if (temperature != lastDisplayedTemperature || humidity != lastDisplayedHumidity) {
    display.clearDisplay();
    display.setTextSize(2); 
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0); 

    
    display.print(F("Temp: "));
    display.print(temperature);
    display.println(F("°C"));

    display.print(F("Hum: "));
    display.print(humidity);
    display.println(F("%"));
    display.display(); 

    lastDisplayedTemperature = temperature;
    lastDisplayedHumidity = humidity;
  }

  if (temperature >= TEMPERATURE_THRESHOLD || humidity >= HUMIDITY_THRESHOLD) {
    Serial.println(F("Temperature or humidity threshold reached. Activating relay."));
    delay(1000);
    digitalWrite(RELAY_PIN, LOW);  
    
  } else {
    Serial.println(F("Both temperature and humidity below thresholds. Deactivating relay."));
    digitalWrite(RELAY_PIN, HIGH);  
  }
}
