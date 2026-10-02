# Embedded Health & Environment Monitoring System

A software-simulated embedded monitoring system developed in **C** to demonstrate real-time sensor communication, data processing, system monitoring, and alarm control.

The system simulates communication with temperature and IMU sensors and processes the received data to determine the overall system condition.

## 🚀 Project Overview

This project was developed to bring together the embedded concepts learned throughout my Embedded Systems learning roadmap.

The system simulates:

* Temperature sensor monitoring
* IMU sensor monitoring
* I²C communication
* SPI communication
* Timer-based events
* Sensor initialization
* Sensor data processing
* System status monitoring
* Buzzer/alarm control
* UART-based data output

The current implementation is **software simulated in C**. A future version can be implemented using a microcontroller and physical sensors.

## ⚙️ System Working

The monitoring process follows these steps:

1. A timer event triggers the monitoring cycle.
2. The system reads temperature sensor data using **I²C**.
3. I²C communication status and sensor acknowledgement are checked.
4. The temperature data is processed.
5. The system reads IMU data using **SPI**.
6. X, Y, and Z-axis data are processed.
7. Sensor conditions are evaluated.
8. The overall system status is determined.
9. The buzzer is controlled according to the system condition.
10. The monitoring information is displayed through UART-style output.

## 📡 Communication Protocols

### I²C

I²C is used to simulate communication with the temperature sensor.

The implementation demonstrates:

* Device addressing
* Register addressing
* ACK/NACK
* Register read operations
* Sensor initialization
* Communication status checking

### SPI

SPI is used to simulate communication with the IMU sensor.

The implementation demonstrates:

* SPI communication
* Sensor register access
* X, Y and Z-axis data
* Communication status checking
* IMU data processing

### UART

UART is used to display the processed sensor information and system status.

Example:

```text
Temperature: 25
X: 2
Y: 0
Z: 4
System Status: Normal
Buzzer Off!!!
```

## ⏱️ Timer-Based Monitoring

A timer event is simulated to periodically initiate the sensor monitoring process.

Example:

```text
Timer Event has Occured
Reading Temperature.....
Sensor does acknowledge
I2C Communication: Success
Processing Data....
Sensor Status: Normal
Reading IMU....
SPI Communication: Working
Processing Data....
IMU Status: Normal
```

## 🚨 System Status & Alarm

The system evaluates the processed sensor data and determines whether the system is operating under normal conditions.

For a normal condition:

```text
System Status: Normal
Buzzer Off!!!
```

If abnormal conditions are detected, the system can activate the buzzer to indicate an alarm condition.

## 🧠 Embedded Concepts Demonstrated

This project demonstrates practical implementation of:

* Embedded C
* Pointers
* Structures
* Bitwise operations
* Macros
* `volatile` variables
* Sensor registers
* Status registers
* Communication status flags
* I²C
* SPI
* UART
* Timers
* Sensor initialization
* Sensor data processing
* Conditional alarm control

## 📊 Sample Output

```text
Timer Event has Occured

Reading Temperature.....
Sensor does acknowledge
I2C Communication: Success
Processing Data....
Sensor Status: Normal

Reading IMU....
SPI Communication: Working
Processing Data....
IMU Status: Normal

Temperature: 25
X: 2
Y: 0
Z: 4

System Status: Normal
Buzzer Off!!!
```

## 🎯 Learning Outcomes

Through this project, I gained practical experience in:

* Developing embedded applications using C
* Understanding sensor communication
* Working with I²C and SPI concepts
* Handling sensor registers and status flags
* Processing sensor data
* Using timer-driven monitoring
* Implementing system status logic
* Controlling an alarm based on system conditions
* Integrating multiple embedded concepts into one application
* Using Git and GitHub for project version control

## 🔮 Future Improvements

The software simulation can be extended into a real hardware implementation using:

* ESP32 or STM32
* Temperature sensor
* IMU sensor
* OLED display
* Buzzer
* UART communication
* Python-based data logging
* Real-time monitoring dashboard

The next stage of the project will focus on replacing the simulated sensors and communication interfaces with **actual hardware peripherals**.

## 👨‍💻 Author

**Dhruv Chavan**

B.E. Electronics and Communication Engineering
Siddaganga Institute of Technology, Tumakuru
