# gesture-glove
Bare-metal STM32 gesture-control glove using MPU6050 IMU sensors for real-time mouse control.
STM32 Gesture Glove

A bare-metal embedded system that uses STM32 microcontrollers and MPU6050 IMU sensors to track hand motion and translate gestures into real-time mouse movement.

Overview

This project explores wearable human-computer interaction using low-level embedded programming and inertial sensing.

The glove collects motion data from MPU6050 sensors, processes the sensor readings on an STM32, and converts the detected movement into mouse input.

Current prototype: The system successfully tracks hand movement and controls the mouse cursor, with ongoing work focused on improving filtering, calibration, and cursor stability.

Features
Bare-metal C firmware on STM32
MPU6050 accelerometer/gyroscope integration
Real-time motion tracking
Gesture-based mouse control
Sensor data processing and calibration
Low-level peripheral communication
Wearable hardware prototype
Hardware
STM32
MPU6050 IMU sensors
Custom glove/wearable assembly
USB connection for computer interface
Software
C
STM32 bare-metal development
I²C communication
Accelerometer & gyroscope data processing
Embedded firmware
System Architecture
       Hand Movement
            │
            ▼
     ┌──────────────┐
     │ MPU6050 IMUs │
     └──────┬───────┘
            │
           I²C
            │
            ▼
     ┌──────────────┐
     │     STM32    │
     │              │
     │ Sensor       │
     │ Processing   │
     │ Calibration  │
     └──────┬───────┘
            │
            ▼
      Mouse Movement
            │
            ▼
       Computer Cursor
How It Works
The MPU6050 sensors measure acceleration and angular velocity.
The STM32 communicates with the sensors over I²C.
Raw IMU measurements are collected and processed in firmware.
Motion data is mapped to cursor movement.
The resulting input is sent to the computer to control the mouse.
Demo
<!-- Add demo video/GIF here -->

Demo: The current prototype demonstrates real-time hand-motion tracking and mouse control.

Note: Cursor movement is currently somewhat jittery due to sensor noise and filtering limitations. Improving sensor fusion, calibration, and filtering is a planned next step.

Future Improvements
 Improve sensor calibration
 Implement better filtering/sensor fusion
 Reduce cursor jitter
 Improve gesture recognition
 Optimize motion-to-cursor mapping
 Add additional gestures
 Improve power management
 Design a more compact PCB-based implementation
What I Learned

This project provided hands-on experience with:

Bare-metal embedded C
STM32 peripherals
I²C communication
IMU sensor integration
Real-time sensor processing
Hardware/software debugging
Wearable embedded systems
