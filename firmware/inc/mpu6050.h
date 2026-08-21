#ifndef MPU6050_H
#define MPU6050_H

#include <stdint.h>

// I2C address — AD0 pin 
#define MPU6050_ADDR_LOW  0x68
#define MPU6050_ADDR_HIGH 0x69

// Registers
#define MPU6050_REG_SMPLRT_DIV    0x19
#define MPU6050_REG_CONFIG        0x1A
#define MPU6050_REG_GYRO_CONFIG   0x1B
#define MPU6050_REG_ACCEL_CONFIG  0x1C
#define MPU6050_REG_ACCEL_XOUT_H  0x3B
#define MPU6050_REG_TEMP_OUT_H    0x41
#define MPU6050_REG_GYRO_XOUT_H   0x43
#define MPU6050_REG_PWR_MGMT_1    0x6B
#define MPU6050_REG_WHO_AM_I      0x75
#define MPU6050_WHO_AM_I_VAL      0x68

// Return codes
#define MPU6050_ERR_NOT_FOUND  (-2)

// Gyro full-scale range (written directly to GYRO_CONFIG[4:3])
typedef enum {
    GYRO_FS_250  = 0x00,   // ±250  °/s — 131   LSB/(°/s)
    GYRO_FS_500  = 0x08,   // ±500  °/s — 65.5  LSB/(°/s)
    GYRO_FS_1000 = 0x10,   // ±1000 °/s — 32.8  LSB/(°/s)
    GYRO_FS_2000 = 0x18,   // ±2000 °/s — 16.4  LSB/(°/s)
} MPU6050_GyroFS;

// Accelerometer full-scale range (written directly to ACCEL_CONFIG[4:3])
typedef enum {
    ACCEL_FS_2G  = 0x00,   // ±2g  — 16384 LSB/g
    ACCEL_FS_4G  = 0x08,   // ±4g  — 8192  LSB/g
    ACCEL_FS_8G  = 0x10,   // ±8g  — 4096  LSB/g
    ACCEL_FS_16G = 0x18,   // ±16g — 2048  LSB/g
} MPU6050_AccelFS;

typedef struct {
    int16_t ax, ay, az;    // raw accelerometer counts
    int16_t temp_raw;      // raw temperature counts
    int16_t gx, gy, gz;    // raw gyroscope counts
} MPU6050_Data;

// Returns 0 on success, I2C_ERR_TIMEOUT or MPU6050_ERR_NOT_FOUND on error
int MPU6050_Init(uint8_t addr, MPU6050_GyroFS gyro_fs, MPU6050_AccelFS accel_fs);

// Burst-reads all 14 sensor bytes in one I2C transaction
int MPU6050_ReadAll(uint8_t addr, MPU6050_Data *data);

// Converts raw temperature to degrees Celsius
float MPU6050_TempCelsius(int16_t temp_raw);

#endif
