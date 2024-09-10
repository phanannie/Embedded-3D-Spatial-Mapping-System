# Embedded 3D Spatial Mapping System

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

## Configuration

Follow these steps to prepare the hardware and software for use:

1. Configure `data_collect.py` with the correct parameters, such as the starting x-coordinate and the COM port for your microcontroller.
2. Use Keil uVision5 to compile the code and flash it to the microcontroller.
3. Ensure all connections between the microcontroller, stepper motor, and ToF sensor are secure.

## Usage

To collect and visualize data, follow these steps:

1. Connect the microcontroller to your computer via USB.
2. Open the Keil project and flash the program to the microcontroller.
3. After flashing, press the RESET button on the microcontroller.
4. Press the J1 button on the MSP microcontroller to start the scanning process.
5. Execute the `data_collect.py` script to begin data acquisition.
6. Once data collection is complete, run the `3d_plot.py` script to visualize the collected data as a 3D model.
