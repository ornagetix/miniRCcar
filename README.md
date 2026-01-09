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

- Web-based control interface hosted on the ESP32-C3
- Real-time motor and steering control via. JWT
- WiFi access point hosted on device
- Compact Hot Wheels–scale chassis

## System Architecture

The system consists of three primary layers:

- **Embedded Controller**  
  ESP32-C3 handling control logic, WiFi networking, and web hosting

- **Control/Logic Layer**  
  Motor driver and servo logic translating web inputs into physical motion

- **User/Web Interface**  
  Lightweight HTML/CSS/JS controller page served directly from the ESP32

> Architecture and wiring are detailed in the wiring diagram below.

## Hardware

- Microcontroller: seeed studio XIAO ESP32-C3
- Chassis: Modified Hot Wheels car (Volkswagen Golf Mk7)
    - Chassis is modified from Hot Wheels car, body is 3D printed
- Drive Motor: Dual-shaft N20 DC brushed motor
- Steering: AGFRC C1.5CLS micro linear servo
- Motor Driver: *DRV8833* (breakout board)
- Power: 55mAh lithium-polymer battery (3.7V)

## Wiring Diagram

The following diagram shows all electrical connections between the ESP32-C3, motor driver, servo, and power system.

![wiring diagram](/images/wiring_diagram.svg)


## Software Stack

- PlatformIO
  - Embedded Arduino/C++ framework, compact libraries 
- HTML / CSS / JavaScript
  - Web-based control interface

## Repository Structure

```text
├── src/            # Firmware source code
├── include/        # Header files
├── data/           # Web server files (HTML/CSS/JS)
├── images/         # Wiring diagrams, images, and 
screenshots
├── cad/            # .STEP files of CAD models
├── platformio.ini  # Build configuration
└── README.md
```

## CAD
I dimentioned the currently constructed car at the time and designed my own, custom body relative to the car's current dimensions in Onshape.

The Onshape document can be viewed [here.](https://cad.onshape.com/documents/029913163f88ca92eb8538c8/w/90c467ae5afbd02c9b09910f/e/cb22bba638a81b7ee942d32d?renderMode=0&uiState=695bdc0cbcff4f574783838d)

![original car construction](/images/car_cad.png)
![body designed around car](/images/body_cad.png)

# Bill of Materials
| Item Name | Sales Price | Retailer | Sales Price + Sales Tax (6%) |  |
| --- | --- | --- | --- | --- |
| Hot Wheels Car (Volkswagen Golf MK7) | n/a |  | n/a |  |
| [seeed studio XIAO ESP32C3 (Microcontroller)](https://www.amazon.com/Seeed-Studio-XIAO-ESP32C3-Microcontroller/dp/B0B94JZ2YF?crid=2WX7GDJZQILGI&dib=eyJ2IjoiMSJ9.6JsYSDWy6Q9SSKTZkvWQC4Z94ZvfMa3MksFtayC58njJbqfsIWiR5V875ff-xxPeuYAul9b1n5ZT7taWoKDk-EkPwSKjfl-0Vwg9zZb0T6EZqEw_J8SZUYNuVtZNz5BASk-TQ7aD9jucywSwXJW-y9KFWxVpOav0Zq1BZtQdq3wRMjHPIn9wSTg2BJ57tE-HuSCjSwxckCHnJapUpX9G4zeqJchFl1bCLteb5IqDmQY.F-VYTF1PBL1iA-CROnfmlf5F54WoGic5Lhhc0n61i1o&dib_tag=se&keywords=xiao%2Besp32c3&qid=1741565380&sprefix=xiao%2Besp32%2Caps%2C83&sr=8-3&th=1)  | 9.9 | Amazon | 10.494 |  |
| [Old DC Motor (extracted from servo)](https://www.aliexpress.us/item/3256806385982254.html?spm=a2g0o.productlist.main.1.2dc05927thOitu&algo_pvid=f597be2e-3b93-4f2f-8b5c-9e634b9a79bd&algo_exp_id=f597be2e-3b93-4f2f-8b5c-9e634b9a79bd-0&pdp_ext_f=%7B%22order%22%3A%224746%22%2C%22eval%22%3A%221%22%7D&pdp_npi=4%40dis%21USD%212.33%210.99%21%21%212.33%210.99%21%402103209b17415675672897007e0c9c%2112000037705759120%21sea%21US%210%21ABX&curPageLogUid=LRGvEG9FcxoF&utparam-url=scene%3Asearch%7Cquery_from%3A)  | 0.99 | AliExpress | 1.0494 |  |
| Current DC Motor (page doesn't exist now) | 2.29 | AliExpress | 2.5648 | *bought 2 because one broke (1.10 + 1.19) |
| [AGFRC C1.5CLS micro linear servo (right)](https://www.aliexpress.us/item/3256806392339708.html?spm=a2g0o.productlist.main.37.3d862d18HdkCC1&algo_pvid=5130b087-dfe4-4899-8689-9d9d4965c0a4&algo_exp_id=5130b087-dfe4-4899-8689-9d9d4965c0a4-18&pdp_ext_f=%7B%22order%22%3A%22421%22%2C%22eval%22%3A%221%22%7D&pdp_npi=4%40dis%21USD%2113.38%211.05%21%21%2196.44%217.58%21%402101ec1f17414765297436770e5ac4%2112000037718242671%21sea%21US%210%21ABX&curPageLogUid=6ytbi3n0k2AB&utparam-url=scene%3Asearch%7Cquery_from%3A)  | 11.69 | AliExpress | 13.0928 | *bought 2 because one broke (4.61 + 7.08) |
| [DRV8833 motor driver (breakout board)](https://www.aliexpress.us/item/3256805965029595.html?spm=a2g0o.productlist.main.7.34477c46EYeMW0&aem_p4p_detail=202503091746546738835444100100001602837&algo_pvid=b87e81be-d22d-42ac-a532-aac2ce7ea393&algo_exp_id=b87e81be-d22d-42ac-a532-aac2ce7ea393-3&pdp_ext_f=%7B%22order%22%3A%22132%22%2C%22eval%22%3A%221%22%7D&pdp_npi=4%40dis%21USD%214.82%211.32%21%21%2134.77%219.54%21%402101d9ee17415676142977131ea0fc%2112000038896101922%21sea%21US%210%21ABX&curPageLogUid=x8JDriD0A5nO&utparam-url=scene%3Asearch%7Cquery_from%3A&search_p4p_id=202503091746546738835444100100001602837_1) | 1.43 | AliExpress | 1.5158 | ^ got expensive quickly wow |
| [55mAh lithium-polymer battery (3.7V)](https://www.aliexpress.us/item/3256806678850434.html?spm=a2g0o.productlist.main.69.63b15fabVqmTQb&algo_pvid=0603ecb0-834d-46d1-a87f-35ea367f858a&algo_exp_id=0603ecb0-834d-46d1-a87f-35ea367f858a-34&pdp_ext_f=%7B%22order%22%3A%2246%22%2C%22eval%22%3A%221%22%7D&pdp_npi=4%40dis%21USD%217.28%213.78%21%21%2152.49%2127.26%21%402103246617415701889416269ef782%2112000038556424102%21sea%21US%210%21ABX&curPageLogUid=X61QhphZ1swz&utparam-url=scene%3Asearch%7Cquery_from%3A#nav-review) | 7.28 | AliExpress | 7.7168 |  |
| [SS12D00 SPDT switch](https://www.aliexpress.us/item/2255801021214741.html?spm=a2g0o.productlist.main.3.5ea14facaIhaw3&algo_pvid=46f218fb-59f1-409b-a617-1481b08bfb8e&algo_exp_id=46f218fb-59f1-409b-a617-1481b08bfb8e-1&pdp_ext_f=%7B%22order%22%3A%223394%22%2C%22eval%22%3A%221%22%7D&pdp_npi=4%40dis%21USD%211.07%210.99%21%21%211.07%210.99%21%40210308a417415676555271175e4f6d%2110000015300780421%21sea%21US%210%21ABX&curPageLogUid=dJEEZ5rjXqHD&utparam-url=scene%3Asearch%7Cquery_from%3A) | 0.99 | AliExpress | 1.0494 |  |
| [32-gauge wire](https://www.aliexpress.us/item/3256803980811288.html?spm=a2g0o.productlist.main.9.8fb8a156pFJSxF&algo_pvid=b59c430f-8255-4c1b-8b67-351a82e6d78e&algo_exp_id=b59c430f-8255-4c1b-8b67-351a82e6d78e-4&pdp_ext_f=%7B%22order%22%3A%221700%22%2C%22eval%22%3A%221%22%7D&pdp_npi=4%40dis%21USD%210.89%210.89%21%21%210.89%210.89%21%40210337bc17415676938392327eb3f9%2112000038547718076%21sea%21US%210%21ABX&curPageLogUid=3Kogmb8Xt2ZG&utparam-url=scene%3Asearch%7Cquery_from%3A) | 0.89 | AliExpress | 0.9434 |  |
| Total | 35.46 | w/ Sales Tax | 38.4264 |  |
| *all items are 1 count |  |  |  |  |