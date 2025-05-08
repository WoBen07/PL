#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>
#include <BH1750.h>

#define SDA_PIN 18
#define SCL_PIN 35

Adafruit_SHT31 sht30 = Adafruit_SHT31();
BH1750 lightMeter;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!sht30.begin(0x44)) {
    Serial.println("Couldn't find SHT30");
    while (1) delay(1);
  }

  if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("Couldn't find BH1750");
    while (1) delay(1);
  }

  Serial.println("Sensors initialized.");
}

void loop() {
  float temperature = sht30.readTemperature();
  float humidity = sht30.readHumidity();
  float lux = lightMeter.readLightLevel();

  Serial.printf("Temp: %.2f °C, Humidity: %.2f %%, Light: %.2f lx\n",
                temperature, humidity, lux);

  delay(5000);
}
