#include <Arduino.h> // arduino core library
#include <ESP32Servo.h> // servo class
#include <WiFi.h> // wifi library
//#include <WebServer.h> // web server library

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

// set web server port
//WebServer server(80);

// creates servo object for servo (to attach servo & use methods)
Servo servo;

// function prototype(s)
void setMotor(int speed);

void setup() {
  // starts serial monitor
  Serial.begin(115200);

  // initialize motor PWM channels
  ledcSetup(in1, motorFreq, motorRes);
  ledcSetup(in2, motorFreq, motorRes);
  ledcAttachPin(in1, in1);
  ledcAttachPin(in2, in2);

  // initialize servo pin
  servo.attach(servo_pin);
  // reset servo to zero
  servo.write(0);

  // start wifi connection in AP mode
  /*
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  */
}

void loop() {
  // put your main code here, to run repeatedly:

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

void setMotor(int speed) {
  if (speed > 0 && speed <= 255) {
    ledcWrite(in1, speed);
    ledcWrite(in2, 0);;
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