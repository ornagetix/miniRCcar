# miniRCcar

### A Hot Wheels car transformed into a miniature, WiFi-controlled RC car using an ESP32-C3

This repository documents the design and development of a compact, rear-wheel-drive mini RC car built from a modified Hot Wheels chassis.

The car is controlled wirelessly through a web-based interface hosted directly on the ESP32-C3, requiring no external apps.

![picture of finished car](/images/car_picture.JPG)

## Overview
I remember coming along [this](https://www.youtube.com/watch?v=nx7Ih79KevE) tutorial online by [Max Imagination](https://www.youtube.com/@MaxImagination) a while back about creating a miniature RC car using components solely housed inside of the metal body of Hot Wheels car. 

His project intrigued me so much that I decided to attempt and create my own iteration of a miniature RC car using a similar manufacturing process: I took apart one of my own Hot Wheels cars at home, carved down the plastic chassis, and added my own components on it. I even tried creating a custom metal body by adding my own paint finish; however, the metal body didn't fit with the chassis anyway, leading me to improvise by designing my own body in Onshape and 3D printing it myself.

I took great inspiration from the tutorial while also using my skills in electronics that I learned when I built an electric vehicle for Science Olympiad, designing my own steering mechanism and wiring system. The tutorial initially included a camera integrated on the car as well, but I didn't see a point for it as it would only decrease the poor battery life of the car even more (the drive motor of the car uses significant amounts of current). 

**All of the code is written solely by myself with the help of AI.**

Despite many aspects of the car being based off the tutorial, this project was still a very extensive learning curve for me. The goal of this project was for me to learn and explore embedded systems, wireless control, and mechanical integration all incorporated together.  
The ESP32-C3 serves as both the real-time controller and the web server, enabling direct browser-based control of steering and throttle.

This repository contains the **entire development history**, including iterative firmware changes, hardware integration, and testing.

## Features

- Web-based controller hosted on the ESP32-C3
- Real-time motor and steering control
- Self-hosted WiFi access point
- Compact Hot Wheels–scale chassis
- Modular firmware structure
- Full commit history documenting development progress

## System Architecture

The system consists of three primary layers:

- **Embedded Controller**  
  ESP32-C3 handling control logic, WiFi networking, and web hosting

- **Control Layer**  
  Motor driver and servo logic translating web inputs into physical motion

- **User Interface**  
  Lightweight HTML/CSS/JS controller page served directly from the ESP32

> Architecture and wiring are detailed in the wiring diagram below.

## Hardware

- Microcontroller: seeed studio XIAO ESP32-C3
- Chassis: Modified Hot Wheels car (Volkswagen Golf Mk7)
    - Body is 3D printed
- Drive Motor: Modified N20 DC brushed motor
- Steering: Micro linear servo
- Motor Driver: *DRV8833* (breakout board)
- Power: Lithium-polymer battery (55mAh)

## Wiring Diagram

The following diagram shows all electrical connections between the ESP32-C3, motor driver, servo, and power system.

![wiring diagram](/images/wiring_diagram.svg)


## Software Stack

- PlatformIO
- Embedded C++
- ESP32 Arduino framework
- HTML / CSS / JavaScript (web controller UI)

## Repository Structure

```text
├── src/            # Firmware source code
├── include/        # Header files
├── data/           # Web server files (HTML/CSS/JS)
├── images/         # Wiring diagrams, images, and screenshots
├── platformio.ini  # Build configuration
└── README.md
```

## CAD
I dimentioned the currently constructed car at the time and designed my own, custom body relative to the car's current dimensions in Onshape.

The Onshape document can be viewed [here.](https://cad.onshape.com/documents/029913163f88ca92eb8538c8/w/90c467ae5afbd02c9b09910f/e/cb22bba638a81b7ee942d32d?renderMode=0&uiState=695bdc0cbcff4f574783838d)

![original car construction](/images/car_cad.png)
![body designed around car](/images/body_cad.png)