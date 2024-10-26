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
  <img src="https://github.com/user-attachments/assets/a7945219-1224-44c9-b3aa-714410899a26" alt="All Parts" width="1080"/>
  <br />
  <i>3D printed parts</i>
</p>

### 3D Printed Parts

1. **Base Plate of the Structure**<br />
  This part is designed to be the base of the balancing robot. It connects with the stepper motors and features 6 holes on each side for screws to secure the NEMA 17 motor mounts. Additionally, there are 4 holes for the 8mm threaded rod that supports the structure.

2. **Support for the NEMA 17 Stepper Motors**<br />
  This piece functions similarly to metal brackets for NEMA 17 motors. However, by printing it, we reduce costs while maintaining the same efficiency for our project. It also includes 2 extra holes compared to standard brackets, allowing for more secure mounting with up to 6 screws.

3. **Central Plate of the Structure**<br />
   This part includes 4 holes for the 8mm threaded rod and 4 additional holes to mount the electronic board. It serves as a key component in securing the electronics in place.

4. **Upper Plate of the Structure**<br />
   This piece is designed to be the top of the robot’s structure. It has 4 holes for the 8mm threaded rod and is a simple yet essential part of the assembly, providing the top support for the robot.
   
5. **Wheels** <br />
   These are the wheel designs used for the robot. Initially, another type of wheel was planned, but this design was chosen for better performance and suitability for the project.

6. **Light Diffusers**  
   The light diffusers are designed to illuminate a LED and are shaped like arrows to indicate the direction of the motor wheels. When both wheels rotate clockwise, the LED will point forward, and when both wheels rotate counterclockwise, the LED will point backward.
   
### Assembly of the Balancing Robot  
   This image shows the overall assembly created in SolidWorks. It combines all the 3D printed parts, demonstrating how they fit together and providing a complete view of the robot's mechanical structure.

<p align="center">
  <img src="URL_TO_ALL_PARTS_IMAGE" alt="All Parts" width="500"/>  
</p>

# Electronics

## Overview

In this section, I will describe the electronics used in the project. I utilized Wokwi to present the schematic in a more legible and understandable format for anyone. EasyEDA was primarily used to visualize the PCB design, which helped in understanding how the soldering would look and in planning the location of components

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

## PCB Creation with EasyEDA

First, I used **[EasyEDA Designer](https://easyeda.com/es)** to create the overall schematic, connecting the pins of the respective components with their labels to make it more readable. I divided the design into three parts:

1. **Power Supply**: This section includes the circuit necessary to power the Arduino through the **Vin** port, supplying it with 5V.
   
2. **Arduino Nano**: Here, you can find the labels and pins used for the Arduino Nano.

3. **Other Modules**: In the third section, we can see other modules such as the **HC-05**, **MPU6050**, **A4988**, and some male pins that will be used on the board.

<p align="center">
  <img src="https://github.com/user-attachments/assets/369b3427-a6c5-4c78-a5b3-54cd036ac573" alt="Esquematico General" width="1356"/>
  <br />
  <i>Main schematic</i>
</p>

Next, we move on to the PCB creation, where we place the components' locations and the soldering paths for better organization when creating it in real life. In the following image, we can see the soldering paths from the top view (Red color 🔴)  as well as the bottom view (Blue color 🔵). There are also measurement dimensions in case anyone is interested in replicating it.

<p align="center">
  <img src="https://github.com/user-attachments/assets/47c0d878-c64d-43a2-8a1f-1f5fe39b1686" alt="PCB Full" width="1082"/>
  <br />
  <i>PCB with measurements and both solder paths fused</i>
</p>

Finally, here is how a printed circuit board would look, both from the top and bottom views. I did not include 3D components because I prefer to show the silkscreen.

<p align="center">
  <img src="https://github.com/user-attachments/assets/a6ce2983-9f52-4f02-8786-072640b37c0d" alt="PCB_Superior_e_Inferior" width="1828"/>
  <br />
  <i>PCB Top and Bottom View</i>
</p>

# Important code explanations

## Arduino Nano Connection Pins

### I2C:
- A4 - SDA
- A5 - SCL

```
#define I2C_PULLUPS_ENABLE         PORTC |= 1<<4; PORTC |= 1<<5;   // PIN A4 & A5 (SDA & SCL)
```

### Motor Driver Pins:
- D5 - STEP1 (PORTD 5)
- D6 - STEP2 (PORTD 6)
- D7 - DIR1 (PORTD 7)
- D8 - DIR2 (PORTB 0)
- D4 - ENABLE (for both)
  
```
uint8_t DRIVER_PIN[5] = {5, 6, 7, 8, 4};   // STEP1 (PORTD 5), STEP2 (PORTD 6), DIR1 (PORTD 7), DIR2 (PORTB 0), ENABLE
```
## Configuration

These are the optional settings you can modify for each balancing robot in the `config.h` file:

The first important configuration is the orientation of the MPU6050. You can change this in this section by setting it to either "ROLL" or "PITCH." In my case, I use "PITCH."

```
#define CURRENT_AXIS    PITCH       // it is possible to choose ROLL or PITCH axis as current.
```

Another crucial setting for the balancing robot is the adjustment of values based on its performance. Comments indicate typical values that usually work well:

```
#define MAX_SPEED           350    // should be <= 500 // Con 350 va bien 
#define MAX_TARGET_ANGLE    130    // where 10 = 1 degree, should be <= 15 degree (i.e. <= 150) 
#define MAX_STEERING        90     // should be <= 100

#define RISE_SPEED_K        1.0f   // this coefficient means how faster robot will be during the auto rising...  should be >= 0.5 but <= 2.0
```

Another configuration pertains to the HC-05 Bluetooth module. To use it, it must be set to a baud rate of 115200, as shown in the following lines of code:

```
#define SERIAL0_COM_SPEED 115200
#define SERIAL1_COM_SPEED 115200
#define SERIAL2_COM_SPEED 115200
#define SERIAL3_COM_SPEED 115200
```

By default, Bluetooth modules come configured to 9600 baud. To change this, you need to enter the following command in the serial terminal while the module is in AT mode :
```
AT+UART=115200,0,0
```
If for any reason you need to modify how the left and right motors are managed, you can do so in the Interrupt Service Routine (ISR) located in `Output.cpp`. This ISR is responsible for controlling the STEP and DIR signals for both motors.

The ISR is defined as follows:
```
ISR(TIMER1_COMPA_vect) {
}
```

# Troubleshooting

## Common Issues and Solutions

**1. Wheel Slipperiness:**
   
One of the main challenges encountered in this project was related to the wheels. The 3D-printed wheels were very slippery on certain surfaces, such as ceramic and wood.

**Solution:**
To enhance grip and friction, we added strips of EVA rubber around the entire perimeter of the wheels. This significantly improved the wheel's traction on slippery surfaces.

<p align="center">
  <img src="https://github.com/user-attachments/assets/cdbac65d-0ae3-4329-a908-35c7331d9e8d" width="800"/>
  <br />
  <i>wheels with EVA rubber</i>
</p>

**2. Wheel Attachment Stability:**
   
Another issue with the wheels was that the screws used to attach them were insufficient. Over time, vibrations from the motor caused the screws to loosen and come out.

<p align="center">
  <img src="https://github.com/user-attachments/assets/d6155298-deed-40aa-9031-5f9497a1d47d" width="300"/>
  <br />
  <i>After a long time, the wheels would gradually come off due to the vibrations of the motors.</i>
</p>

**Solution:**
To resolve this, we applied adhesive to secure the axle parts. This greatly improved stability, and the wheels no longer detached.

**3. A4988 Driver Potentiometer Adjustment:**

Another issue was related to the potentiometer on the A4988 driver. When set to a low level (around 0.2V), the wheels would barely move, especially under load.

**Solution:**
By adjusting the potentiometer to approximately 1V, we found that both wheels operated smoothly, resolving the issue of the wheels stalling when they encountered resistance. This adjustment made a significant difference in performance.

<p align="center">
  <img src="https://github.com/user-attachments/assets/c8cfda08-785e-4efa-86fa-b75a345f93db" width="423"/>
  <br />
  <i>Adjustment of the A4988 driver potentiometer</i>
</p>

**4. Bluetooth Module Connection During Upload:**

When uploading code to the Arduino Nano, the Bluetooth module must be disconnected. This is necessary because the module uses the RX and TX pins of the Arduino for communication.

**Solution:**
When you upload code, the Arduino needs exclusive access to the RX (receive) and TX (transmit) pins to communicate with the computer. If the Bluetooth module is connected, it may interfere with this process, preventing the upload from completing successfully. To ensure a smooth upload, always disconnect the Bluetooth module before loading new code onto the Arduino Nano.

# Future Improvements

##  Potential Add-ons


I. **18650 Battery Power Source:**
   Incorporating 18650 batteries as a power source could enhance the robot's mobility. In my case, I currently use a 12V power supply, as the batteries are quite expensive in my country. The batteries would allow for greater freedom of movement without the risk of cables tangling during turns.

II. **Camera Integration:**
   Adding a camera to the balancing robot would enable remote observation, as if the robot were exploring areas. This feature could facilitate mapping of environments.

III. **Ultrasonic Sensor Module:**
   Integrating an ultrasonic sensor would help the robot avoid collisions with walls or obstacles, enhancing its navigation capabilities.

IV. **Improved Printed Circuit Board (PCB):**
   While I initially used a perforated board, there are PDF files available for creating a more professional-looking PCB using either the marker or toner transfer methods. Additionally, you could consider sending the design to a manufacturer like PCBWay or other reputable providers.

V. **Custom Software Development:**
   Creating a complete application and software from scratch, without relying on existing libraries or pre-made applications, would be a significant undertaking. However, the current setup provides a solid foundation for such an endeavor.

# Bibliography

All the references used in the development of this project will be compiled in a text file, which will include all the links we utilized as guides throughout the process.

# Acknowledgments

I would like to extend my sincere gratitude to several individuals and organizations for this project.

- **Guillermo Daniel Duarte**: A special thank you to my colleague for his invaluable assistance and support throughout this project. Your help was crucial to its completion.

- **Professor Cristian Leandro Lukasiewicz**: I am deeply grateful to Professor Lukasiewicz for overseeing our Supervised Professional Practice (PPS) and providing guidance and support throughout the process.

- **National University of Lomas de Zamora, Faculty of Engineering**: For opening the doors to a rich academic environment that has allowed me to pursue my studies and acquire valuable knowledge.

- **Mahowik**: A heartfelt thanks to Mahowik for the fantastic firmware provided in the [BalancingWii](https://github.com/mahowik/BalancingWii). Your work has greatly contributed to the success of this project.

- **To all readers**: I hope you find this project both interesting and useful.

![Logo facultad con color](https://github.com/user-attachments/assets/e53a8451-da3c-4043-81e9-76fe114df523)

<div align="center">

<b><i>Best regards, and have a great day!</i></b>

</div>
