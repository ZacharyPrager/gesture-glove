#include <stdint.h>
#include <i2c.h>
#include <clock.h>
#include <uart.h>
#include <sensor.h>

int main() {

    clock_init();
    I2C_init();
    UART_Init();

    // D3=PB3, D4=PB5, D5=PB4 on Nucleo F446RE
    uint8_t pins[3] = {3, 5, 4};
    for (int i = 0; i < 3; i++) {
        GPIO_InitOutput(GPIOB, pins[i]);
    }

    UART_SendByte('S');  // UART alive, entering init loop
    while (MPU6050_CycleWrite(GYRO_FS_500, ACCEL_FS_4G, pins, GPIOB) != 0) {
        UART_SendByte('F');  // CycleWrite failed, retrying
        I2C_init();
    }
    UART_SendByte('K');  // init succeeded, entering read loop

    MPU6050_Data data[3];
    uint8_t *data_ptr = (uint8_t *)data;

    while (1) {
        if (MPU6050_CycleRead(data, pins, GPIOB) != 0) {
            I2C_init();  // recover stuck bus
            continue;
        }

        // sync word so monitor.py can align to packet boundaries
        UART_SendByte(0xAA);
        UART_SendByte(0x55);
        // 3 sensors × 14 bytes
        UART_SendBuffer(data_ptr, 42);
    }

    return 0;
}
