#include <Arduino.h> // arduino core library
#include <ESP32Servo.h> // servo class

#include <WiFi.h> // wifi library
#include <AsyncTCP.h> // async tcp library
#include <ESPAsyncWebServer.h> // web server library
#include <AsyncWebSocket.h> // websocket library

#include <FS.h> // main filesystem library
#include <LittleFS.h> // littlefs filesystem library

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
void onWSEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

void setup() {
  // starts serial monitor
  Serial.begin(115200);
  delay(5000); // Give time for serial monitor to connect
  Serial.println("\n5s wait for media & serial connection..."); // wait for serial monitor to connect via USB

  // initialize motor PWM channels
  ledcSetup(in1, motorFreq, motorRes);
  ledcSetup(in2, motorFreq, motorRes);
  ledcAttachPin(in1, in1);
  ledcAttachPin(in2, in2);

  servo.attach(servo_pin); // initialize servo pin
  servo.write(50); // reset servo to default position

  // setup LittleFS file system
  if (!LittleFS.begin() && !LittleFS.begin(true)) {
    Serial.println("An error has occurred while mounting LittleFS");
  } else {
    Serial.println("LittleFS mounted successfully!");
  }

  File f = LittleFS.open("/index.html", "r");
  if (!f) {
    Serial.println("Webpage not found in LittleFS");
  } else {
    Serial.println("Webpage exists in LittleFS!");
    f.close();
  }
  
  // setup access point
  Serial.println("Setting up car access point...");
  WiFi.softAP(ssid, password);
  Serial.println("Car access point started!\n");

  // add web files from /data folder to LittleFS
  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

  // setup & start web socket
  ws.onEvent(onWSEvent);
  server.addHandler(&ws);
  server.begin();
  Serial.println("Web server started!");
}

// websocket event handler
// handles events like connect, disconnect, and sending motor & servo commands
void onWSEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
  switch (type) {
    case WS_EVT_CONNECT: // client connected
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT: // client disconnected
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA: // data received from client (computer sends commands)
      // motor and servo control code
      Serial.printf("WebSocket client #%u sent data: %s\n", client->id(), (char*)data);

      // data is sent as a string in the format: "M:speed" or "S:angle"
      // M = motor command, S = servo command
      // speed range: -255 to 255
      // angle range: 0 to 180
      if (data[0] == 'M') { // motor command
        int speed = atoi((char*)data + 2); // convert string to integer (skip first 2 chars)
        setMotor(speed); // set motor speed
      } else if (data[0] == 'S') { // servo command
        int angle = atoi((char*)data + 2); // convert string to integer (skip first 2 chars)
        steerAngle(angle); // set servo angle
      }

      // echo the same message back to the client for confirmation
      client->text((char*)data);
      break;
    default:
      break;
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