#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int voltagePin = A2; // Analog pin for voltage sensor
const int currentPin = A1; // Analog pin for current sensor
const int buzzerPin = 2; // Digital pin for buzzer

void setup() {
  Serial.begin(9600); // Initialize Serial Monitor
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as OUTPUT
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Initialize OLED display
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display(); // Clear the display buffer
  delay(2000); // Delay for stabilization
  display.clearDisplay(); // Clear the display buffer
}

void loop() {
  float voltage = readVoltage();
  float current = readCurrent();

  display.clearDisplay(); // Clear the display buffer

  // Set text size and color
  display.setTextSize(1); // Small font size
  display.setTextColor(SSD1306_WHITE); // White text color

  // Print voltage reading
  display.setCursor(0, 0); // Set cursor position for voltage
  display.print("Voltage: ");
  display.print(voltage, 2);
  display.println(" V");

  // Print current reading
  display.setCursor(0, 20); // Set cursor position for current
  display.print("Current: ");
  display.print(current, 2);
  display.println(" A");

  // Add a separator line
  display.drawLine(0, 40, SCREEN_WIDTH, 40, SSD1306_WHITE);

  // Check voltage conditions and print warning messages
  if (voltage < 5.0) {
    display.setCursor(0, 50);
    display.println("Warning: Low Voltage Detected!");
    // Emit continuous beep beep sound for low voltage
    playContinuousBeep();
  } else if (voltage > 12.0) {
    display.setCursor(0, 50);
    display.println("Warning: High Voltage Detected!");
    // Emit continuous beep beep sound for high voltage
    playContinuousBeep();
  } else {
    display.setCursor(0, 50);
    display.println("Smart Vehicle System");
    noTone(buzzerPin); // Turn off the buzzer
  }

  display.display(); // Display the content
  delay(1000); // Delay for stability
}

float readVoltage() {
  int sensorValue = analogRead(voltagePin);
  float voltage = sensorValue * (5.0 / 1023.0) * (25.0 / 5.0); // Convert analog reading to voltage
  return voltage;
}

float readCurrent() {
  int sensorValue = analogRead(currentPin);
  float current = sensorValue * (5.0 / 1023.0); // Convert analog reading to current
  return current;
}

void playContinuousBeep() {
  for (int i = 0; i < 6; i++) { // Emit 6 beeps
    tone(buzzerPin, 1000); // Start emitting beep at 1000 Hz
    delay(200); // Beep duration
    noTone(buzzerPin); // Turn off the beep
    delay(200); // Interval between beeps
  }
}
