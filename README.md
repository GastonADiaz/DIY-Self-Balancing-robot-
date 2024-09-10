# Table of Contents

- [Introduction](#introduction)
  - [Overview and Objective](#overview-and-objective)
- [Components Used](#components-used)
  - [List of Hardware Components](#list-of-hardware-components)
  - [List of Software Tools](#list-of-software-tools)
- [Mechanical Design](#mechanical-design)
  - [3D Printed Parts](#3D-Printed-Parts)
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


## Mechanical Design

In this section, I will describe the mechanical design of the robot, including the 3D printed parts and the overall assembly. The designs were created using SolidWorks 2021, which allowed me to visualize the dimensions needed and plan the hardware required, such as screws and other components. The toolbox in SolidWorks also helped in determining the quantity of parts needed and in assembling the pieces to see how everything fits together.

### 3D Printed Parts

- **Base plate of the structure**  
  <p align="center">
    <img src="https://github.com/user-attachments/assets/35c78bf3-f76d-4250-b9da-80598849e8c8" alt="Image 1" width="300" style="border: 20px solid #a215e8;/>
  </p>  
  This part is designed to be the base of the balancing robot. It connects with the stepper motors and features 6 holes on each side for screws to secure the NEMA 17 motor mounts. Additionally, there are 4 holes for the 8mm threaded rod that supports the structure.

- **Support for the nema 17 stepper motors**  
  <p align="center">
    <img src="https://github.com/user-attachments/assets/1ba8db90-4b60-4c7e-983f-6352d15cbbc4"alt="Image 2" width="300" />
  </p>  
  This piece functions similarly to metal brackets for NEMA 17 motors. However, by printing it, we reduce costs while maintaining the same efficiency for our project. It also includes 2 extra holes compared to standard brackets, allowing for more secure mounting with up to 6 screws.

- **Central plate of the structure**  
  <p align="center">
    <img src="https://github.com/user-attachments/assets/329a52f9-5e00-43ab-9c70-090f463529dc" alt="Image 3" width="300" />
  </p>  
  This part includes 4 holes for the 8mm threaded rod and 4 additional holes to mount the electronic board. It serves as a key component in securing the electronics in place.

- **Upper plate of the structure**  
  <p align="center">
    <img src="https://github.com/user-attachments/assets/3ee3df82-ac13-4035-ba25-cf51f8f19bed" alt="Image 4" width="300" />
  </p>  
  This piece is designed to be the top of the robot’s structure. It has 4 holes for the 8mm threaded rod and is a simple yet essential part of the assembly, providing the top support for the robot.

- **Wheels**  
  <p align="center">
    <img src="https://github.com/user-attachments/assets/faa2bd36-064a-4dc6-b487-238db89fe1aa" alt="Image 5" width="300" />
  </p>  
  These are the wheel designs used for the robot. Initially, another type of wheel was planned (visible in the SolidWorks files), but this design was chosen for better performance and suitability for the project.

- **Assembly of the balancing robot**  
  <p align="center">
    <img src="https://github.com/user-attachments/assets/bb6f93f4-b620-439c-8791-9fb99ded0409" alt="Image 6" width="500" />
  </p>  
  This image shows the overall assembly created in SolidWorks. It combines all the 3D printed parts, demonstrating how they fit together and providing a complete view of the robot's mechanical structure.

By using SolidWorks, I was able to accurately measure and fit all components, ensuring that everything was properly aligned and functional. The toolbox feature in SolidWorks was particularly useful for planning the hardware requirements and visualizing the final assembly.


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
