#include <ESP32Servo.h> // servo class
#define in1 D0
#define in2 D1
#define servo_pin D2

// creates servo object for servo (to attach servo & use methods)
Servo servo;

void setup() {
  // put your setup code here, to run once:

  // initialize motor pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // initialize servo pin
  servo.attach(servo_pin);
  // reset servo to zero
  servo.write(0);

  // starts serial monitor
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // MOTOR TEST CODE
  analogWrite(in1, 255);
  digitalWrite(in2, LOW);

  // SERVO TEST CODE
  servo.write(50);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(120);
  delay(1000);
  servo.write(90);
  delay(1000);
}

void setMotor(int speed) {
  if (speed > 0 && speed <= 255) {
    analogWrite(in1, speed);
    digitalWrite(in2, LOW);
  } else if (speed < 0 && speed >= -255) {
    digitalWrite(in1, LOW);
    analogWrite(in2, speed);
  } else if (speed == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  } else {
    Serial.println("invalid speed");
  }
}