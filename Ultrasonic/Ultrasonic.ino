#define trigPin1 6
#define echoPin1 7
#define trigPin2 8
#define echoPin2 9
#define trigPin3 10
#define echoPin3 11

void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
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

  if (distance1 < 5 || distance2 < 5 || distance3 < 5) {
    Serial.println("Stop"); // Print stop message if any distance is less than 5 cm
  } else {
    Serial.print("Distance 1: ");
    Serial.print(distance1);
    Serial.print(" cm, Distance 2: ");
    Serial.print(distance2);
    Serial.print(" cm, Distance 3: ");
    Serial.print(distance3);
    Serial.println(" cm");
  }

  delay(1000); // Delay for readability
}
