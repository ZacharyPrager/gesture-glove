#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>
#include <mpu6050.h>
#include <gpio.h>
#include <stm32f446_regs.h>



int MPU6050_CycleRead(MPU6050_Data *data, uint8_t pins[3],GPIO_Regs *port);
int MPU6050_CycleWrite(MPU6050_GyroFS gyro_fs, MPU6050_AccelFS accel_fs, uint8_t pins[3], GPIO_Regs *port);

#endif