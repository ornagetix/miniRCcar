#include <Arduino.h> // arduino core library
#include <ESP32Servo.h> // servo class
#include <WiFi.h> // wifi library
#include <AsyncTCP.h> // async tcp library
#include <ESPAsyncWebServer.h> // websocket web server library

// define motor pins and PWM channels
#define in1 2
#define in2 3
#define motorFreq 5000
#define motorRes 8

// setup motor and servo pins
#define servo_pin 4

// setup WiFi credentials
const char* ssid     = "miniRCcar";
const char* password = "screwdriver123";

// creates servo object for servo (to attach servo & use methods)
Servo servo;

// function prototype(s)
void setMotor(int speed);
void testLoop();

void setup() {
  // starts serial monitor
  Serial.begin(115200);
  Serial.println("Test print");

  // initialize motor PWM channels
  ledcSetup(in1, motorFreq, motorRes);
  ledcSetup(in2, motorFreq, motorRes);
  ledcAttachPin(in1, in1);
  ledcAttachPin(in2, in2);

  // initialize servo pin
  servo.attach(servo_pin);
  // reset servo to zero
  servo.write(0);

  // setup access point
  /*
  Serial.println("Setting up car access point...");
  WiFi.softAP(ssid, password);
  Serial.println("Car access point started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  */
}

void loop() {
  // method to test motor and servo
  testLoop();
}

/*
  sets motor speed and direction
  speed range: -255 to 255
  negative speed = reverse direction
  positive speed = forward direction
  zero speed = stop motor
*/
void setMotor(int speed) {
  if (speed > 0 && speed <= 255) {
    ledcWrite(in1, speed);
    ledcWrite(in2, 0);
  } else if (speed < 0 && speed >= -255) {
    ledcWrite(in1, 0);
    ledcWrite(in2, speed);
  } else if (speed == 0) {
    ledcWrite(in1, 0);
    ledcWrite(in2, 0);
  } else {
    Serial.println("invalid speed");
  }
}

// sets the servo/steering angle
void steerAngle(int angle) {
  if (angle >= 0 && angle <= 180) {
    servo.write(angle);
  } else {
    Serial.println("invalid angle");
  }
}

void testLoop() {
  // motor and servo test code
  setMotor(255);
  servo.write(50);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(120);
  delay(1000);
  servo.write(90);
  delay(1000);
} 