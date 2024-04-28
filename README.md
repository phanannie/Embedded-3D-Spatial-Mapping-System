# 3D Lidar Scanning and Mapping System

Welcome to the Advanced 3D Lidar Mapping System project repository. This project was developed as part of an Engineering Design Project and it leverages cutting-edge technology to capture 360-degree scans of environments, creating precise 3D models.

<p align="center">
  <img src="https://github.com/phanannie/3D-Lidar-Scanning-System/assets/108703625/20613482-fe35-47db-bdb9-a843c0991233" alt="Lidar System Hardware" width="600"/>
  <br>
  <em>The Lidar system hardware setup, using a microcontroller with connected sensors and motor.</em>
</p>

### 3D Scan Output

<p align="center">
  <img src="https://github.com/phanannie/3D-Lidar-Scanning-System/assets/108703625/f6d73ac6-8d19-4564-b35b-d69642bebe57" alt="3D Scan Output - Top View" width="600"/>
  <br>
  <img src="https://github.com/phanannie/3D-Lidar-Scanning-System/assets/108703625/56839a69-1a6f-495f-8747-a7f735c19777" alt="3D Scan Output - Perspective View" width="600"/>
  <br>
  <em>Example of a 3D scan output showing the structural wireframe of a hallway.</em>
</p>

## Features

- Full 360-degree scanning capability for comprehensive environmental mapping.
- Accurate distance measurements using the Time-of-Flight (ToF) sensor.
- Data management powered by Texas Instruments MSP432E401Y microcontroller.
- Data communication facilitated via I2C and UART protocols.
- 3D visualization using the Open3D Python library for detailed spatial analysis.

## Getting Started

To get your Lidar system up and running, follow these instructions.

### Prerequisites

You should have the following hardware and software ready:

- Texas Instruments MSP432E401Y microcontroller
- UNL2003 stepper motor controller
- VL53L1X Time-of-Flight sensor
- Python 3.6 or later
- Open3D library
- pySerial library

### Installation

1. Clone this repository to your local machine:

   ```bash
   git clone [https://github.com/your-username/3D-Lidar-Scanning-and-Mapping-System.git](https://github.com/phanannie/3D-Lidar-Scanning-System.git)
