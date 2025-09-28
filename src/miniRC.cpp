#include <Arduino.h> // arduino core library
#include <ESP32Servo.h> // servo class

#include <WiFi.h> // wifi library
#include <AsyncTCP.h> // async tcp library
#include <ESPAsyncWebServer.h> // websocket web server library

#include <LittleFS.h> // littlefs file system library

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

// setup web socket
AsyncWebServer server(80); // web server on port 80
AsyncWebSocket ws("/ws"); // websocket endpoint (path is /ws)

// creates servo object for servo (to attach servo & use methods)
Servo servo;

// function prototypes
void setMotor(int speed);
void steerAngle(int angle);
void testLoop();

void setup() {
  // starts serial monitor
  Serial.begin(115200);
  delay(5000); // Give time for serial monitor to connect
  Serial.println("5s wait for media & serial connection..."); // wait for serial monitor to connect via USB

  // setup LittleFS file system
  if(!LittleFS.begin()){
    Serial.println("An error has occurred while mounting LittleFS");
    return;
  }
  Serial.println("LittleFS mounted successfully");

  // initialize motor PWM channels
  ledcSetup(in1, motorFreq, motorRes);

  ledcSetup(in2, motorFreq, motorRes);
  ledcAttachPin(in1, in1);
  ledcAttachPin(in2, in2);

  // initialize servo pin
  servo.attach(servo_pin);
  // reset servo to zero
  servo.write(50);
  
  // setup access point
  Serial.println("Setting up car access point...");
  WiFi.softAP(ssid, password);
  Serial.println("Car access point started!\n");
}

// websocket event handler
// handles events like connect, disconnect, and sending motor & servo commands
void onWSEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
  if(type == WS_EVT_CONNECT){
    Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
  } else if(type == WS_EVT_DISCONNECT){
    Serial.printf("WebSocket client #%u disconnected\n", client->id());
  } else if(type == WS_EVT_DATA){
    // motor and servo control code
    
    // echo the received message back to the client
    client->text((char*)data);
  }
}

bool infoPrinted = false; // value to ensure info is printed only once
void loop() {
  // print access point info only once
  if (!infoPrinted) {
    //delay(5000); // wait for access point to initialize
    Serial.print("Car SSID: ");
    Serial.println(WiFi.softAPSSID());
    Serial.print("Car IPv4 address: ");
    Serial.println(WiFi.softAPIP());
    infoPrinted = true;
  }

  // motor and servo test code looped
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