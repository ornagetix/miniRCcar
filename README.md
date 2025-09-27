# miniRCcar
### A Hot Wheels car transformed into a miniature remoter-controlled car (via. web server) using an ESP32C3.

This repository contains all of the code used for this project, including:

* Motor and servo control/logic
* Web server logic
* Controller webpage

To connect to the car:
1. Turn on the car (of course)
2. Connect the car to a <ins>serial monitor</ins> 
> [!IMPORTANT]
> The car has a **5-second delay** before executing any setup to allow time to connect via USB.
3. Connect to the <ins>Car SSID</ins> given by the serial monitor using your device's WiFi configuration interface 
4. Test the connection using the `ping` command with the given <ins>Car IPv4 address</ins>
> [!NOTE]
> Looks similar to a default gateway like `192.168.X.1`