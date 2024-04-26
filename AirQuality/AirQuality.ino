#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "MQ135.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 4      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22 // DHT 22 (AM2302)

#define RLOAD 22.0

#define SCREEN_WIDTH  128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT_Unified dht(DHTPIN, DHTTYPE);
MQ135 gasSensor = MQ135(A2);

int measurePin = A0; // Connect dust sensor to Arduino A0 pin
int ledPower = 2;    // Connect 3 led driver pins of dust sensor to Arduino D2

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

uint32_t delayMS;

void setup()
{
  Serial.begin(9600);
  // Initialize DHT device.
  dht.begin();
  pinMode(ledPower, OUTPUT);
  pinMode(A2, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print(F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print(F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print(F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print(F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print(F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print(F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));

  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print(F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print(F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print(F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print(F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print(F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print(F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));

  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop()
{
  // DHT sensor reading
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature))
  {
    Serial.println(F("Error reading temperature!"));
  }
  else
  {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity))
  {
    Serial.println(F("Error reading humidity!"));
  }
  else
  {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  // Dust sensor reading
  digitalWrite(ledPower, LOW); // Power on the LED
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin); // Read the dust value
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH); // Turn the LED off
  delayMicroseconds(sleepTime);

  // Map 0 - 5V to 0 - 1023 integer values and calculate voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);

  // Calculate dust density using linear equation
  dustDensity = 170 * calcVoltage - 0.1;

  Serial.print(F("Dust Density: "));
  Serial.print(dustDensity); // Unit: ug/m3
  Serial.println(F(" ug/m3"));

  // Gas sensor reading
  int val = analogRead(A2);
  Serial.print("raw = ");
  Serial.println(val);
  float ppm = gasSensor.getPPM();
  Serial.print("ppm: ");
  Serial.println(ppm);

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(18, 43);
  display.println("CO2");
  display.setCursor(63, 43);
  display.println("(PPM)");
  display.setTextSize(2);
  display.setCursor(28, 5);
  display.println(ppm);
  display.display();
  display.clearDisplay();

  delay(1000); // Delay before next reading
}