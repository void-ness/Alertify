## Introduction
Alertify is a smart visual alerting system. It can listen to your phone notifications in real-time and generate a visual alert to notify you about the same. It is currently in prototype stage, built to make the alerting systems accessible for deaf and hard-of-hearing individuals

## Technologies Used
- **Hardware**:
  - Arduino UNO - microcontroller
  - HC-05 - Bluetooth Module
  - Single color LEDs - for visualizing alerts
  - Jumper wires, breadboard - for making connections
    
- **Software**:
  - MIT App Inventor - A no-code mobile app development tool 
  - Taifun Notification-Listening-Service Extension - for listening to notifications
 
## Repository Overview
1. v2.ino - it contains the source code for the Arduino program. It needs to be loaded on the Arduino board for it to work properly.
2. SmartLamp.apk - it is an Android-based application to connect to the Arduino prototype. It supports functionality for listening to notifications and sending an alert to the Arduino via Bluetooth
3. SmartLamp.aia - a source code file for the mobile application. It can be imported into the MIT App Inventor as a project, for making further changes. The notification-listening-service extension needs to be imported separately.

## Future Work
The prototype can be improved by utilizing any WiFi enabled board instead of relying on Bluetooth-based communication. Secondly, RGB LEDs can be used in place of single color LEDs. At last, the application can be refactored to utilize background processes, so that it can listen to notifications even when the application is closed.
