#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup() {
  Serial.begin(9600);
  Serial.println("Vehicle Started");
}

void loop() {
  // Run all motors forward
  motor1.setSpeed(speed(100));
  motor2.setSpeed(speed(100));
  motor3.setSpeed(speed(100));
  motor4.setSpeed(speed(100));
  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  // Delay for a while
  delay(2000);

  // Brake all motors
  //motor1.run(RELEASE);
  //motor2.run(RELEASE);
  //motor3.run(RELEASE);
  //motor4.run(RELEASE);

  // Delay for a while
  delay(2000);
}

int speed(int percent)
{
  return map(percent, 0, 100, 0,255);
}