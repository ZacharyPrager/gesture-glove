/* Cycles through 3 MPU6050s sharing the I2C bus by toggling their AD0 pins:
 * LOW → 0x68 (active), HIGH → 0x69 (idle). */
#include <sensor.h>
#include <stdint.h>
#include <mpu6050.h>
#include <gpio.h>
#include <stm32f446_regs.h>

int MPU6050_CycleRead(MPU6050_Data *data, uint8_t pins[3], GPIO_Regs *port) {
    /* S0 at 0x69 (pins[0] HIGH), S1+S2 at 0x68 (pins[1]+pins[2] LOW) — only S0 sees 0x69 */
    GPIO_SetPin(port, pins[0]);
    GPIO_ClearPin(port, pins[1]);
    GPIO_ClearPin(port, pins[2]);
    int ret = MPU6050_ReadAll(MPU6050_ADDR_HIGH, &data[0]);
    if (ret != 0) return ret;

    /* S1: pull pins[1] LOW, raise pins[2] HIGH — only S1 at 0x68 */
    GPIO_SetPin(port, pins[2]);
    ret = MPU6050_ReadAll(MPU6050_ADDR_LOW, &data[1]);
    if (ret != 0) return ret;

    /* S2: raise pins[1] HIGH, pull pins[2] LOW — only S2 at 0x68 */
    GPIO_SetPin(port, pins[1]);
    GPIO_ClearPin(port, pins[2]);
    ret = MPU6050_ReadAll(MPU6050_ADDR_LOW, &data[2]);
    if (ret != 0) return ret;

    GPIO_SetPin(port, pins[2]);
    return 0;
}

int MPU6050_CycleWrite(MPU6050_GyroFS gyro_fs, MPU6050_AccelFS accel_fs, uint8_t pins[3], GPIO_Regs *port) {
    /* S0 at 0x69, S1+S2 at 0x68 — only S0 sees 0x69 */
    GPIO_SetPin(port, pins[0]);
    GPIO_ClearPin(port, pins[1]);
    GPIO_ClearPin(port, pins[2]);
    int ret = MPU6050_Init(MPU6050_ADDR_HIGH, gyro_fs, accel_fs);
    if (ret != 0) return ret;

    /* S1: pins[1] LOW, pins[2] HIGH — only S1 at 0x68 */
    GPIO_SetPin(port, pins[2]);
    ret = MPU6050_Init(MPU6050_ADDR_LOW, gyro_fs, accel_fs);
    if (ret != 0) return ret;

    /* S2: pins[1] HIGH, pins[2] LOW — only S2 at 0x68 */
    GPIO_SetPin(port, pins[1]);
    GPIO_ClearPin(port, pins[2]);
    ret = MPU6050_Init(MPU6050_ADDR_LOW, gyro_fs, accel_fs);
    if (ret != 0) return ret;

    GPIO_SetPin(port, pins[2]);
    return 0;
}
