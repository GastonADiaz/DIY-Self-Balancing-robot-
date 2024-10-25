# Table of Contents

- 🗂️[Introduction](#introduction)
  - 🎯[Overview and Objective](#overview-and-objective)
- 🛠️[Components Used](#components-used)
  - :page_facing_up:[List of Hardware Components](#list-of-hardware-components)
  - 💻[List of Software Tools](#list-of-software-tools)
- :shipit:[Mechanical Design](#mechanical-design)
  - 🛠️[3D Printed Parts](#3D-Printed-Parts)
- 🔌[Electronics](#electronics)
  - 📐[Circuit Diagram](#circuit-diagram)
  - 🔧[Wiring Details](#wiring-details)
- 💻[Firmware and Software](#firmware-and-software)
  - 🧩[Key Code Sections](#key-code-sections)
  - 🔄[PID Control Explanation](#pid-control-explanation)
   - ⚙️[Calibration Procedures](#calibration-procedures)
- :exclamation:[Troubleshooting](#troubleshooting)
  - ⚠️[Common Issues and Solutions](#common-issues-and-solutions)
- 🔮[Future Improvements](#future-improvements)
  - 🔧[Potential Add-ons](#potential-add-ons)
- 📚[Bibliography](#bibliography)
  - 🔍[Related Work and Resources](#related-work-and-resources)
- 🙏[Acknowledgments](#acknowledgments)

# Introduction

## Overview and Objective

This project addresses the challenge of building a self-balancing robot that maintains its stability in an upright position using two wheels. The robot is based on a series of components, including Nema 17 stepper motors, A4988 motor drivers, an MPU6050 gyro-accelerometer sensor, and an HC-05 Bluetooth module, all managed by an ATmega328p microcontroller.

Additionally, the project incorporates control of the robot via a mobile application. We use the EZ-GUI Ground Station app, typically employed for drones, but we utilize it to manipulate the self-balancing robot through a joystick interface and make custom configurations.

The central objective of this project is to implement a balance control system that allows the robot to remain upright on its own. To achieve this, the system utilizes feedback from the MPU6050 sensor, which measures the tilt angle or "pitch angle." Through a closed-loop control system with a PID (Proportional, Integral, and Derivative) controller, the robot adjusts motor speeds based on the measured angle, correcting any deviations and minimizing balance error. This approach enables the robot to dynamically adapt to variations and effectively maintain its stability.

We would also like to acknowledge the firmware "BalancingWii," which significantly assisted in the development of this project.

## Balancing robot working in real life

![Video del robot en al vida real](URL)

# Components Used

## List of Components

| Quantity | Component                                         | Description                                       |
|----------|---------------------------------------------------|---------------------------------------------------|
| 7        | 3D Printed Parts                                  | 2 wheels, 2 NEMA 17 motor mounts, 3 general structure parts, 4 light diffusers |
| 1        | Perforated Board                                  | For electronics mounting                          |
| 2        | NEMA 17 Stepper Motors                            | Motor type used for the robot                    |
| 1        | MPU6050                                           | Gyroscope and accelerometer module               |
| 2        | A4988 Drivers                                    | Stepper motor drivers                            |
| 1        | ATmega328p (Arduino Nano)                        | Microcontroller                                  |
| 1        | 7805T Voltage Regulator                            | Regulates voltage to 5V                          |
| 1        | 9V to 12V Power                                  | Rechargeable battery or power supply              |
| 1        | On/Off Switch                                     | Power switch                                     |
| 13       | Male Pins                                         | For connecting stepper motor coils to the drivers and LEDs |
| 80       | Female Pins                                       | For connecting various components                 |
| 1        | 2-Pin Terminal Block                              | For power connection                             |
| 2        | Heat Sinks                                        | For cooling the A4988 drivers                    |
| 2        | 100µF Capacitors                                  | 16V capacitors                                   |
| 2        | 220µF Capacitors                                  | 16V capacitors                                   |
| 8        | XH2.54 Connectors                                 | 2 connectors with 4 pins and 2 connectors with 6 pins for stepper motor wiring |
| 1        | 1 Meter M8 Threaded Rod                           | For structural support                           |
| 24       | M8 Hex Nuts                                       | For threaded rod connections                     |
| 12       | M4 Hex Nuts                                       | For securing components to the structure         |
| 12       | M4 Phillips Head Bolts (13mm)                    | For mounting motor supports and electronics board |
| 8        | M3 Phillips Head Bolts (8mm)                     | For securing stepper motor mounts                |
| 2        | GND and Vin Cables                                | Power supply cables for the entire circuit       |
| 1        | HC-05 Bluetooth Module                            | For mobile application control                    |
| 10       | Heat Shrink Tubing                                | For soldering and joining wires                   |
| 4        | Green LEDs                                        | For indicating status                             |
| 4        | 220Ω Resistors                                    | For current limiting on the LEDs                  |
| 3        | 1kΩ Resistors                                     | For voltage division to provide 3.3V to the RX pin of the HC-05 |
| 4        | Cable Ties                                        | For securing cables                               |

## Principal Tools

| Quantity | Tool                   | Description                         |
|----------|------------------------|-------------------------------------|
| 1        | Soldering Iron         | For soldering connections           |
| 1        | Desoldering Pump       | For removing solder                 |
| 1        | Multimeter (Tester)    | For measuring voltage and continuity |
| 1        | Solder wire                | For making electrical joints        |
| 1        | Screwdriver            | For fastening screws                |

## List of Software Tools

| Software             | Description                                                                                              |
|----------------------|----------------------------------------------------------------------------------------------------------|
| SolidWorks 2021      | I used SolidWorks 2021 to design the 3D printed parts, model various components, and utilize its toolbox for bolts, nuts, etc. |
| Wokwi                | I used Wokwi to create and simulate electronic schematics and code, with the added benefit of simulating without needing physical connections. |
| Arduino IDE          | I used Arduino IDE to write and upload the code to the ATmega328p microcontroller.                      |
| Easy Eda Designer    | I used Easy Eda Designer for PCB creation and electronic schematics, as it is a very tidy software for designing PCBs. It allows exporting traces for PCB milling or sending the Gerber file for manufacturing. |
| EZ-GUI Ground Station | I used the EZ-GUI Ground Station APK for mobile control of the robot, allowing manipulation through a joystick interface. |


## Mechanical Design

In this section, I will describe the mechanical design of the robot, including the 3D printed parts and the overall assembly. The designs were created using SolidWorks 2021, which allowed me to visualize the dimensions needed and plan the hardware required, such as screws and other components. The toolbox in SolidWorks also helped in determining the quantity of parts needed and in assembling the pieces to see how everything fits together.

<p align="center">
  <img src="URL_TO_ALL_PARTS_IMAGE" alt="All Parts" width="500"/>
</p>

### 3D Printed Parts

1. **Base Plate of the Structure**  
   This part is designed to be the base of the balancing robot. It connects with the stepper motors and features 6 holes on each side for screws to secure the NEMA 17 motor mounts. Additionally, there are 4 holes for the 8mm threaded rod that supports the structure.

2. **Support for the NEMA 17 Stepper Motors**  
   This piece functions similarly to metal brackets for NEMA 17 motors. However, by printing it, we reduce costs while maintaining the same efficiency for our project. It also includes 2 extra holes compared to standard brackets, allowing for more secure mounting with up to 6 screws.

3. **Central Plate of the Structure**  
   This part includes 4 holes for the 8mm threaded rod and 4 additional holes to mount the electronic board. It serves as a key component in securing the electronics in place.

4. **Upper Plate of the Structure**  
   This piece is designed to be the top of the robot’s structure. It has 4 holes for the 8mm threaded rod and is a simple yet essential part of the assembly, providing the top support for the robot.

5. **Wheels**  
   These are the wheel designs used for the robot. Initially, another type of wheel was planned, but this design was chosen for better performance and suitability for the project.

6. **Light Diffusers**  
   The light diffusers are designed to illuminate a LED and are shaped like arrows to indicate the direction of the motor wheels. When both wheels rotate clockwise, the LED will point forward, and when both wheels rotate counterclockwise, the LED will point backward.
   
7. **Assembly of the Balancing Robot**  
   This image shows the overall assembly created in SolidWorks. It combines all the 3D printed parts, demonstrating how they fit together and providing a complete view of the robot's mechanical structure.

# Electronics

## Overview

In this section, I will describe the electronics used in the project. I utilized Wokwi to present the schematic in a more legible and understandable format for anyone. Proteus was primarily used to visualize the PCB design and its 3D model, which helped in understanding how the soldering would look and in planning the components layout.

## Circuit Diagram

I used Wokwi to create a clear and easy-to-understand schematic diagram. Below is the schematic created using Wokwi:

<p align="center">
  <img src="https://github.com/user-attachments/assets/fa456a7a-35cf-47c7-a003-72cface94aaa" alt="Circuit Diagram" width="600"/>
  <br />
  <i>Wokwi connection diagram</i>
</p>

## Wiring Details

The following details explain the purpose of each color used in the wiring connections:

- 🔴 **Red**: Represents 3.3V output pin from the ESP32S.
- ⚫ **Black**: Represents GND.
- 🔵 **Blue**: Represents the microstep pins (MS1, MS2, MS3) of the A4988 stepper motor drivers.
- 🟢 **Light Green**: Represents signals from the ESP32 to control motors steps and direction (STEP and DIR pins of the A4988).
- 🌲 **Dark Green**: Represents a bridge connection.
- 🌫️ **Gray**: Represents the stepper motors coils 1A, 1B, 2A, 2B.
- 🟦 **Cyan**: Represents the I2C communication for the MPU6050.
- 🟠 **Orange**: Represents the power supply (9V, up to 35V).
- 🌸 **Magenta**: Represents 5V output from the 7805 voltage regulator.

## PCB Creation with Proteus

Proteus was used for creating the PCB and its 3D model. Due to the lack of some components in Proteus's default libraries, I had to create many components from scratch. This software allowed me to design the PCB layout and visualize it in 3D before finalizing the design. The red welding paths represent the top layer of the PCB, and the blue welding paths represent the bottom layer. Proteus also provided the dimensions of the PCB and the distances between centers, which were crucial for the final assembly.

Here are the images of the PCB design and its 3D model:

<p align="center">
  <img src="https://github.com/user-attachments/assets/79096ccc-3fa6-4492-ac77-cbdbe538e71b" alt="PCB Design" width="500"/>
  <br />
  <i>PCB Design</i>
</p>

Proteus provides us with the PCB format in 3D, using the IGES format. This file can be visualized and used in SolidWorks.

<p align="center">
  <img src="https://github.com/user-attachments/assets/44c0c4b2-4772-419c-98cc-3821e84b6755" alt="3D PCB Model" width="500"/>
  <br />
  <i>3D PCB Model</i>
</p>

## Actual PCB Board

Below are images of the actual PCB board, showing both the top and bottom sides after soldering:

<p align="center">
  <img src="https://github.com/user-attachments/assets/5d0efb57-b90c-4437-b425-606e10ea5f66" alt="PCB Top Side" width="300"/>
  <br />
  <i>PCB Top Side</i>
</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/f5e66837-b46d-4049-ab97-5ef159dcb5b5" alt="PCB Bottom Side" width="300"/>
  <br />
  <i>PCB Bottom Side</i>
</p>

To simplify the circuit, I used fewer wires by implementing solder paths between components on the bottom side of the PCB. On the top side, I utilized jumper wires to make connections more straightforward.
<br />
The bottom part didn't turn out so well, since the solder paths are too close together, but the important thing is that it works well.

# Firmware and Software

## Key Code Sections

# PID Controller Explanation for the Balancing Robot

<p align="center">
  <img src="https://github.com/user-attachments/assets/d0d2d64f-d56f-4ac9-8e9b-93eef6e6527b" alt="Closed-Loop Diagram of the System with PID" width="800"/>
  <br />
  <i>Closed-Loop Diagram of the System with PID</i>
</p>

## Explanation of the Diagram

**Setpoint (Desired Value):** This is the value that I want the system to reach. In this case, I want to keep the roll angle at 0° for the balancing robot.

**Error \[ e(t) \]:** This is the difference between the desired value (setpoint) and the value measured at the current moment.
<br />
I calculate it as:
<p align="center">
  <img src="https://github.com/user-attachments/assets/8e19f12b-d797-4c35-a1e8-8c9fc2ff4ff8" alt="Error e(t)" width="400"/>
  <br />
</p>

**PID Controller:** This controller adjusts the control signal based on the error \[ e(t) \] and consists of three components:
- **Proportional (P):** This depends on the current value of the error. If the error is large, the proportional action will be large.
- **Integral (I):** This depends on the accumulation of error over time. If the error persists, the integral action will increase to eliminate the residual error.
- **Derivative (D):** This depends on the rate of change of the error. If the error is changing rapidly, the derivative action will adjust to prevent overshoot.

The output of the PID controller is a combination of these three actions:
<p align="center">
  <img src="https://github.com/user-attachments/assets/ede1709f-e9bb-47e2-9d30-48fe14708ab0" alt="PID Output" width="700"/>
  <br />
</p>
Kp, Ki and Kd are the gains received by the proportional, integral and derivative part.<br /><br />

**Nema 17 Motors:** These motors receive the control signal adjusted by the PID and adjust the rotational speed to try to bring the roll angle to the desired value.

**Measured Value:** This is the current measurement of the system. In my case, it's the roll angle measured by the MPU6050 sensor.

**Feedback:** I feed the measured roll angle back to the PID controller, which calculates the new error and adjusts the control signal accordingly. I repeat this process continuously to keep the system at the desired value.

## Operating Cycle

The entire cycle works as follows:
1. I measure the current roll angle (Measured Value) using the MPU6050.
2. I calculate the error \[ e(t) \] between the desired angle (Setpoint) and the measured angle.
3. The PID controller adjusts the control signal based on the current error, accumulated error, and its rate of change.
4. I send the adjusted control signal to the Nema 17 motors to correct the roll angle.
5. The motors change the position, and the MPU6050 sensor measures the angle again, and the cycle repeats.

## Calculations 

**Error Derivative:** To calculate the derivative of the error using finite differences:
<p align="center">
  <img src="https://github.com/user-attachments/assets/1d80682a-84ac-4dd7-aeaf-7163dce9d125" alt="Error Derivative" width="250"/>
  <br />
</p>
where [ Δt ] is the time between each sample:
<p align="center">
  <img src="https://github.com/user-attachments/assets/b9df8ebd-d527-4c52-b9a0-78cb418e4f08" alt="Delta t for Derivative" width="250"/>
  <br />
</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/fa2fc768-635d-4ee3-8184-2891e846149c" alt="Error Integral" width="250"/>
  <br />
</p>

**Error Integral:** I sum the integral of the error at each interval over time, accumulating the error.
<br />
I calculate the integral as:
<p align="center">
  <img src="https://github.com/user-attachments/assets/30b46d2e-977b-4d35-9758-673d9ecb2a6c" alt="Current Integral Calculation" width="500"/>
  <br />
</p>

## Calibration Procedures

# Troubleshooting

##  Common Issues and Solutions

**1. Wheel Slipperiness:**
   
One of the main challenges encountered in this project was related to the wheels. The 3D-printed wheels were very slippery on certain surfaces, such as ceramic and wood.

Solution:
To enhance grip and friction, we added strips of EVA rubber around the entire perimeter of the wheels. This significantly improved the wheel's traction on slippery surfaces.

<p align="center">
  <img src="https://github.com/user-attachments/assets/cdbac65d-0ae3-4329-a908-35c7331d9e8d" width="800"/>
  <br />
  <i>wheels with eva rubber</i>
</p>

**2. Wheel Attachment Stability:**
   
Another issue with the wheels was that the screws used to attach them were insufficient. Over time, vibrations from the motor caused the screws to loosen and come out.

<p align="center">
  <img src="https://github.com/user-attachments/assets/d6155298-deed-40aa-9031-5f9497a1d47d" width="300"/>
  <br />
  <i>After a long time, the wheels would gradually come off due to the vibrations of the engines.</i>
</p>

Solution:
To resolve this, we applied adhesive to secure the axle parts. This greatly improved stability, and the wheels no longer detached.

**3. MPU6050 Drift:**
   
We also faced challenges with the MPU6050 sensor, which exhibited drift in the angle measurements.

Solution:
By using accelerometer data instead of gyroscope data, we were able to calculate drift-free angles through trigonometric calculations.

**4. Sensor Noise:**
   
The sensor produced noisy readings due to vibrations of the motors.

Solution:
To mitigate this noise, I implemented a Kalman filter, which effectively smoothed the signals.

<p align="center">
  <img src="" alt="Angles measured without using a filter" width="800"/>
  <br />
  <i>Angles measured without using a filter</i>
</p>
<p align="center">
  <img src="" alt="Angles measured with a Kalman filter" width="800"/>
  <br />
  <i>Angles measured with a Kalman filter</i>
</p>

# Future Improvements

##  Potential Add-ons

# Bibliography

All the references used in the development of this project will be compiled in a text file, which will include all the links we utilized as guides throughout the process.

# Acknowledgments

I would like to extend my sincere gratitude to several individuals and organization for this project

- **Guillermo Daniel Duarte**: A special thank you to my colleague for his invaluable assistance and support throughout this project. Your help was crucial to its completion.

- **Professor Cristian Leandro Lukasiewicz**: I am deeply grateful to Professor Lukasiewicz for overseeing our Supervised Professional Practice (PPS) and providing guidance and support throughout the process.

- **National University of Lomas de Zamora, Faculty of Engineering**: for opening the doors to a rich academic environment that has allowed me to pursue my studies and acquire valuable knowledge.

- **To all readers**: I hope you find this project both interesting and useful.

![Logo facultad con color](https://github.com/user-attachments/assets/e53a8451-da3c-4043-81e9-76fe114df523)

<div align="center">

<b><i>Best regards, and have a great day!</i></b>

</div>
