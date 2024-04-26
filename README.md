# Smart Vehicle Safety and Comfort Enhancement System

Welcome to the Smart Vehicle Safety and Comfort Enhancement System project repository. This repository contains the documentation and code for developing a system that enhances vehicle safety and occupant comfort by integrating fault tracing of wiring harnesses, detection of invisible center medians, and monitoring cabin air quality.

## Project Overview
In today's automotive landscape, ensuring vehicle safety and enhancing occupant comfort are paramount concerns. This project aims to address these concerns by implementing cutting-edge sensor technologies and advanced data processing algorithms.

## Features
1. *Fault Tracing of Wiring Harnesses:*
   - Sensors are used to detect faults in wiring harnesses (short circuits, open circuits).
   - Data processing algorithms analyze sensor data to pinpoint fault locations.
   - Fault alerts are displayed on the vehicle dashboard.

2. *Avoiding Median Accidents:*
   - Sensors and cameras detect invisible center medians to prevent accidents.
   - An audible warning system alerts the driver of potential hazards.

3. *Air Quality Monitoring and Improvement:*
   - Air quality sensors monitor pollutant levels in the vehicle cabin.
   - An air purification system integrated with the HVAC system improves cabin air quality.

## Technologies Used
- Arduino Uno board
- Various sensors
- Display modules (LCD, OLED, TFT)
- Connecting wires (jumper wires, breadboard wires)
- Power supply components (USB cable, external power supply)
- Computer running Arduino IDE for programming
- 4WD Robotic Smart Car Kit

## Sensors Used
- Voltage Sensor VCC<25V
- Current Sensor HW872A
- Ultrasonic Sensor HC-SR04
- Dust Sensor GP2Y1010AU0F
- Temperature and Humidity Sensor DHT22
- Gas Sensor (Organic compounds like CO, CO2, Methane) MQ-135

## Modules Used
- Motor Driver L293D
- TFT Display Shield 3'5 MAR3501 0x9341
- OLED 0.96 inch I2C/IIC 128 X 64
  
## Repository Structure
- */hardware_setup:* Contains documentation related to hardware setup and component integration.
- */software_development:* Includes Arduino sketches and code for data processing algorithms.
- */docs:* User manuals, wiring diagrams, and project documentation.
- */examples:* Example sketches and test code for individual components.
- */images:* Images of project setup, wiring, and components.

## Getting Started
1. *Hardware Setup:* Follow instructions in /hardware_setup to connect components to the Arduino Uno board.
2. *Software Development:* Use Arduino IDE to upload sketches from /software_development onto the Arduino.
3. *Testing and Calibration:* Run example sketches from /examples to test individual components and calibrate sensors.
4. *Documentation:* Refer to /docs for detailed project documentation, including user manuals and wiring diagrams.

## Contributing
Contributions to this project are welcome. If you have ideas for improvements or would like to contribute code or documentation, please feel free to fork this repository and submit pull requests.

## Authors
- Atharv Sharma - Project Lead & Developer
- G Neeraj - Sensor Integration & Testing
- Soham Pujari - Display Module Configuration & Optimization 
