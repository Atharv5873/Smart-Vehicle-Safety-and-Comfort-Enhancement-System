#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AFMotor.h>

AF_DCMotor motor1(1); // Create motor objects for all four motors
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

#define trigPin1 6   // Ultrasonic sensor 1 trigger pin
#define echoPin1 7   // Ultrasonic sensor 1 echo pin
#define trigPin2 8   // Ultrasonic sensor 2 trigger pin
#define echoPin2 9   // Ultrasonic sensor 2 echo pin
#define trigPin3 10  // Ultrasonic sensor 3 trigger pin
#define echoPin3 11  // Ultrasonic sensor 3 echo pin

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_RESET -1  // OLED reset pin

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Initialize OLED display object

const int voltagePin = A2; // Analog pin for voltage sensor
const int currentPin = A1; // Analog pin for current sensor
const int buzzerPin = 2;   // Digital pin for buzzer

void setup() {
  Serial.begin(9600); // Initialize Serial communication
  pinMode(trigPin1, OUTPUT); // Set ultrasonic sensor pins as input/output
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Initialize OLED display
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display(); // Clear the display buffer
  delay(2000);       // Delay for stabilization
  display.clearDisplay(); // Clear the display buffer
  Serial.println("Vehicle Started");
}

void loop() {
  long duration1, distance1, duration2, distance2, duration3, distance3;
  
  // Sensor 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;
  
  // Sensor 2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;
  
  // Sensor 3
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 * 0.034 / 2;

  // Check if any distance reading is less than 10 cm
  if (distance1 < 10 || distance2 < 10 || distance3 < 10) {
    Serial.println("Stop"); // Print stop message if any distance is less than 10 cm
    // Stop all motors
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  } else {
    // Run all motors forward
    motor1.setSpeed(255); // Set motor speeds
    motor2.setSpeed(255);
    motor3.setSpeed(255);
    motor4.setSpeed(255);
    
    motor1.run(FORWARD); // Run motors forward
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }

  // Read voltage and current
  float voltage = readVoltage();
  float current = readCurrent();

  // Clear display and print voltage and current
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Voltage: ");
  display.print(voltage, 2);
  display.println(" V");
  display.setCursor(0, 20);
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
  for (int i = 0; i < 6; i++) { // Emit 6 beepsou
    tone(buzzerPin, 1000); // Start emitting beep at 1000 Hz
    delay(200); // Beep duration
    noTone(buzzerPin); // Turn off the beep
    delay(200); // Interval between beeps
  }
}
