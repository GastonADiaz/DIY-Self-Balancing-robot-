# Table of Contents

- [Introduction](#introduction)
  - [Overview and Objective](#overview-and-objective)
- [Components Used](#components-used)
  - [List of Hardware Components](#list-of-hardware-components)
  - [List of Software Tools](#list-of-software-tools)
- [Mechanical Design](#mechanical-design)
  - [Description of the Mechanical Structure](#description-of-the-mechanical-structure)
  - [CAD Drawings or Diagrams](#cad-drawings-or-diagrams)
- [Electronics](#electronics)
  - [Circuit Diagram](#circuit-diagram)
  - [Wiring Details](#wiring-details)
- [Firmware and Software](#firmware-and-software)
  - [Key Code Sections](#key-code-sections)
  - [PID Control Explanation](#pid-control-explanation)
   - [Calibration Procedures](#calibration-procedures)
- [Troubleshooting](#troubleshooting)
  - [Common Issues and Solutions](#common-issues-and-solutions)
- [Future Improvements](#future-improvements)
  - [Potential Add-ons](#potential-add-ons)
- [Bibliography](#bibliography)
  - [Related Work and Resources](#related-work-and-resources)
- [Acknowledgments](#acknowledgments)

# Introduction

## Overview and Objective

# Components Used

## List of Hardware Components


| Quantity | Component                                         | Description                                       |
|----------|---------------------------------------------------|---------------------------------------------------|
| 7        | 3D Printed Parts                                  | 2 wheels, 2 NEMA 17 motor mounts, 3 general structure parts |
| 1        | Perforated Board                                  | For electronics mounting                          |
| 2        | NEMA 17 Stepper Motors                            | Motor type used for the robot                    |
| 1        | MPU6050                                           | Gyroscope and accelerometer module               |
| 2        | A4988 Drivers                                    | Stepper motor drivers                            |
| 1        | ESP32S                                            | Microcontroller                                  |
| 1        | 7805 Voltage Regulator                            | Regulates voltage to 5V                          |
| 1        | 9V to 12V Power                            | Battery or power supply                          |
| 1        | On/Off Switch                                     | Power switch                                     |
| 8        | Male Pins                                         | For connecting stepper motor coils to the drivers |
| 80       | Female Pins                                       | For connecting various components                |
| 1        | 2-Pin Terminal Block                              | For power connection                           |
| 2        | Heat Sinks                                        | For cooling the A4988 drivers                    |
| 2        | 100µF Capacitors                                  | 16V capacitors                                    |
| 2        | 220µF Capacitors                                  | 16V capacitors                                    |
| 8        | XH2.54 Connectors                                 | 2 connectors with 4 pins and 2 connectors with 6 pins for stepper motor wiring |
| 1        | 1 Meter M8 Threaded Rod                           | For structural support                           |
| 24       | M8 Hex Nuts                                       | For threaded rod connections                     |
| 12       | M4 Hex Nuts                                       | For securing components to the structure         |
| 12       | M4 Phillips Head Bolts (13mm)                     | For mounting motor supports and electronics board      |
| 8        | M3 Phillips Head Bolts (8mm)                      | For securing stepper motor mounts |
| 2        | GND and Vin Cables                                | Power supply cables for the entire circuit       |

## List of Software Tools

| Software             | Description                                                                                              |
|----------------------|----------------------------------------------------------------------------------------------------------|
| SolidWorks 2021      | I used SolidWorks 2021 to design the 3D printed parts, model various components, and utilize its toolbox for bolts, nuts, etc. |
| Proteus 8 Professional | I used Proteus 8 Professional for creating electronic schematics, designing the PCB layout, and generating a 3D model of the PCB. |
| Wokwi                | I used Wokwi to create and simulate electronic schematics and code, with the added benefit of simulating without needing physical connections. |
| Arduino IDE          | I used Arduino IDE to write and upload the code to the ESP32S microcontroller. |

# Mechanical Design

##  Description of the Mechanical Structure
## CAD Drawings or Diagrams

# Electronics

##  Circuit Diagram
## Wiring Details

# Firmware and Software

## Key Code Sections
## PID Control Explanation
###  Calibration Procedures

# Troubleshooting

##  Common Issues and Solutions

# Future Improvements

##  Potential Add-ons

# Bibliography
## Related Work and Resources

# Acknowledgments
