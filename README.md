# STM32 Gesture Glove

> A bare-metal STM32 wearable controller that uses MPU6050 IMU sensors to translate hand motion into real-time mouse movement.

## Overview

This project is a wearable gesture-control system built from the ground up using **bare-metal C** on an **STM32** microcontroller.

Multiple **MPU6050 accelerometer/gyroscope sensors** capture hand movement. The STM32 reads and processes the sensor data, then converts the detected motion into mouse input.

The goal is to create a low-level, real-time human-computer interface without relying on an RTOS or high-level embedded framework.
