#include <mpu6050.h>
#include <i2c.h>
#include <stdint.h>

int MPU6050_Init(uint8_t addr, MPU6050_GyroFS gyro_fs, MPU6050_AccelFS accel_fs) {
    int ret;

    // Verify device is present
    ret = I2C_ReadReg(addr, MPU6050_REG_WHO_AM_I);
    if (ret < 0) return ret;
    if (ret != MPU6050_WHO_AM_I_VAL) return MPU6050_ERR_NOT_FOUND;

    // Wake up using internal oscillator — gyro PLL not yet settled at this point
    ret = I2C_WriteReg(addr, 0x00, MPU6050_REG_PWR_MGMT_1);
    if (ret < 0) return ret;

    // Wait ~30ms for gyro to stabilise after wake-up
    for (volatile int i = 0; i < 1000000; i++);


    // Digital low-pass filter: 42 Hz gyro / 44 Hz accel bandwidth
    ret = I2C_WriteReg(addr, 0x03, MPU6050_REG_CONFIG);
    if (ret < 0) return ret;

    // Sample rate: 1 kHz / (1 + 9) = 100 Hz
    ret = I2C_WriteReg(addr, 0x09, MPU6050_REG_SMPLRT_DIV);
    if (ret < 0) return ret;

    ret = I2C_WriteReg(addr, (uint8_t)gyro_fs, MPU6050_REG_GYRO_CONFIG);
    if (ret < 0) return ret;

    ret = I2C_WriteReg(addr, (uint8_t)accel_fs, MPU6050_REG_ACCEL_CONFIG);
    if (ret < 0) return ret;

    return 0;
}

int MPU6050_ReadAll(uint8_t addr, MPU6050_Data *data) {
    
    uint8_t buf[14];

    // [0-1]=AX, [2-3]=AY, [4-5]=AZ, [6-7]=TEMP, [8-9]=GX, [10-11]=GY, [12-13]=GZ
    int ret = I2C_BurstRead(addr, MPU6050_REG_ACCEL_XOUT_H, buf, 14);
    if (ret < 0) return ret;

    data->ax       = (int16_t)((buf[0]  << 8) | buf[1]);
    data->ay       = (int16_t)((buf[2]  << 8) | buf[3]);
    data->az       = (int16_t)((buf[4]  << 8) | buf[5]);
    data->temp_raw = (int16_t)((buf[6]  << 8) | buf[7]);
    data->gx       = (int16_t)((buf[8]  << 8) | buf[9]);
    data->gy       = (int16_t)((buf[10] << 8) | buf[11]);
    data->gz       = (int16_t)((buf[12] << 8) | buf[13]);

    return 0;
}

float MPU6050_TempCelsius(int16_t temp_raw) {
    return (temp_raw / 340.0f) + 36.53f;
}
