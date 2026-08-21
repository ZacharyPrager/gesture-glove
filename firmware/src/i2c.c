#include <stm32f446_regs.h>
#include <i2c.h>
#include <rcc.h>
#include <clock.h>
#include <gpio.h>
#include <stdint.h>

#define I2C_TIMEOUT 100000

#define POLL(reg, flag) \
    do { \
        uint32_t _t = I2C_TIMEOUT; \
        while (!((reg) & (flag))) { \
            if (--_t == 0) return I2C_ERR_TIMEOUT; \
        } \
    } while (0)

#define WAIT_FREE() \
    do { \
        uint32_t _t = I2C_TIMEOUT; \
        while (I2C1->SR2 & SR2_BUSY) { \
            if (--_t == 0) return I2C_ERR_TIMEOUT; \
        } \
    } while (0)

void I2C_init(void) {
    RCC->APB1ENR |= APB1ENR_I2C1EN;
    RCC->AHB1ENR |= AHB1ENR_GPIOBEN;

    /* PB8 = SCL (D15), PB9 = SDA (D14) — AF4, open-drain, pull-up, fast speed */
    GPIOB->MODER &= ~GPIO_MODER_CLEAR(SCL_PIN);
    GPIOB->MODER &= ~GPIO_MODER_CLEAR(SDA_PIN);
    GPIOB->MODER |= GPIO_MODER_ALT_FUNC(SCL_PIN);
    GPIOB->MODER |= GPIO_MODER_ALT_FUNC(SDA_PIN);
    GPIOB->OTYPER |= GPIO_OTYPER_OPEN_DRAIN(SCL_PIN);
    GPIOB->OTYPER |= GPIO_OTYPER_OPEN_DRAIN(SDA_PIN);
    GPIOB->OSPEEDER &= ~GPIO_OSPEEDER_HIGH(SCL_PIN);
    GPIOB->OSPEEDER &= ~GPIO_OSPEEDER_HIGH(SDA_PIN);
    GPIOB->OSPEEDER |= GPIO_OSPEEDER_FAST(SCL_PIN);
    GPIOB->OSPEEDER |= GPIO_OSPEEDER_FAST(SDA_PIN);
    GPIOB->PUPDR &= ~GPIO_PUPDR_CLEAR(SCL_PIN);
    GPIOB->PUPDR &= ~GPIO_PUPDR_CLEAR(SDA_PIN);
    GPIOB->PUPDR |= GPIO_PUPDR_PULLUP(SCL_PIN);
    GPIOB->PUPDR |= GPIO_PUPDR_PULLUP(SDA_PIN);
    GPIOB->AFRH &= ~GPIO_AFRH_CLEAR(SCL_PIN);
    GPIOB->AFRH &= ~GPIO_AFRH_CLEAR(SDA_PIN);
    GPIOB->AFRH |= GPIO_AFRH_AF4(SCL_PIN);
    GPIOB->AFRH |= GPIO_AFRH_AF4(SDA_PIN);

    /* SWRST clears any stuck bus state before re-enabling the peripheral */
    I2C1->CR1 |= CR1_SWRST;
    I2C1->CR1 &= ~CR1_SWRST;
    I2C1->CR2 = (APB1_MHZ & CR2_FREQ);
    I2C1->CCR = 210;            /* 100 kHz Sm: f_PCLK1 / (2 × CCR) = 42 MHz / 420 */
    I2C1->TRISE = 43;           /* max rise time 1000 ns: floor(1.0 µs × 42 MHz) + 1 */
    I2C1->CR1 |= CR1_PE;
}

int I2C_MasterWrite(uint8_t data, uint8_t slave_addr) {
    WAIT_FREE();
    I2C1->CR1 |= CR1_START;
    POLL(I2C1->SR1, SR1_SB);

    I2C1->DR = (slave_addr << 1);
    POLL(I2C1->SR1, SR1_ADDR);
    (void)(I2C1->SR2);          /* reading SR2 clears the ADDR flag */

    I2C1->DR = data;
    POLL(I2C1->SR1, SR1_BTF);

    I2C1->CR1 |= CR1_STOP;
    return 0;
}

int I2C_MasterRead(uint8_t slave_addr) {
    WAIT_FREE();
    I2C1->CR1 |= CR1_START;
    POLL(I2C1->SR1, SR1_SB);

    I2C1->DR = ((slave_addr << 1) | 1);
    POLL(I2C1->SR1, SR1_ADDR);
    I2C1->CR1 &= ~CR1_ACK;     /* NACK the only incoming byte before clearing ADDR */
    (void)(I2C1->SR2);          /* clears ADDR flag, releasing SCL */

    I2C1->CR1 |= CR1_STOP;
    POLL(I2C1->SR1, SR1_RxNE);

    uint8_t data = (uint8_t)I2C1->DR;
    I2C1->CR1 |= CR1_ACK;      /* restore ACK for subsequent transactions */
    return (int)data;
}

int I2C_WriteReg(uint8_t slave_addr, uint8_t data, uint8_t reg) {
    WAIT_FREE();
    I2C1->CR1 |= CR1_START;
    POLL(I2C1->SR1, SR1_SB);
    I2C1->DR = (slave_addr << 1);
    POLL(I2C1->SR1, SR1_ADDR);
    (void)(I2C1->SR2);
    I2C1->DR = reg;
    POLL(I2C1->SR1, SR1_TxE);
    I2C1->DR = data;
    POLL(I2C1->SR1, SR1_BTF);
    I2C1->CR1 |= CR1_STOP;
    return 0;
}

int I2C_BurstRead(uint8_t slave_addr, uint8_t reg, uint8_t *buf, uint8_t len) {
    if (len == 0) return 0;

    /* Write phase: send register address to set the device's internal pointer */
    WAIT_FREE();
    I2C1->CR1 |= CR1_START;
    POLL(I2C1->SR1, SR1_SB);
    I2C1->DR = (slave_addr << 1);
    POLL(I2C1->SR1, SR1_ADDR);
    (void)(I2C1->SR2);
    I2C1->DR = reg;
    POLL(I2C1->SR1, SR1_TxE);

    /* Repeated START switches to read phase without releasing the bus */
    I2C1->CR1 |= CR1_START;
    POLL(I2C1->SR1, SR1_SB);
    I2C1->DR = ((slave_addr << 1) | 1);
    POLL(I2C1->SR1, SR1_ADDR);

    if (len == 1) {
        I2C1->CR1 &= ~CR1_ACK;
        (void)(I2C1->SR2);
        I2C1->CR1 |= CR1_STOP;
        POLL(I2C1->SR1, SR1_RxNE);
        buf[0] = (uint8_t)I2C1->DR;
    } else if (len == 2) {
        /* POS=1 shifts ACK/NACK control to the next byte in the shift register,
         * allowing both bytes to be NACKed before either lands in DR (RM0390 §27.3.3) */
        I2C1->CR1 |= CR1_POS;
        I2C1->CR1 &= ~CR1_ACK;
        (void)(I2C1->SR2);
        POLL(I2C1->SR1, SR1_BTF);
        I2C1->CR1 |= CR1_STOP;
        buf[0] = (uint8_t)I2C1->DR;
        buf[1] = (uint8_t)I2C1->DR;
        I2C1->CR1 &= ~CR1_POS;
    } else {
        /* ACK all bytes up to the final two; wait for BTF with the last pair held
         * in DR and the shift register so STOP is issued without a race condition */
        I2C1->CR1 |= CR1_ACK;
        (void)(I2C1->SR2);
        for (uint8_t i = 0; i < len - 3; i++) {
            POLL(I2C1->SR1, SR1_RxNE);
            buf[i] = (uint8_t)I2C1->DR;
        }
        /* BTF: DR = byte[len-3], shift reg = byte[len-2], SCL held low */
        POLL(I2C1->SR1, SR1_BTF);
        I2C1->CR1 &= ~CR1_ACK;
        buf[len - 3] = (uint8_t)I2C1->DR; /* releasing DR moves byte[len-2] into it */
        I2C1->CR1 |= CR1_STOP;
        buf[len - 2] = (uint8_t)I2C1->DR;
        POLL(I2C1->SR1, SR1_RxNE);
        buf[len - 1] = (uint8_t)I2C1->DR;
    }

    I2C1->CR1 |= CR1_ACK;
    return 0;
}

int I2C_ReadReg(uint8_t slave_addr, uint8_t reg) {
    WAIT_FREE();
    I2C1->CR1 |= CR1_START;
    POLL(I2C1->SR1, SR1_SB);
    I2C1->DR = (slave_addr << 1);
    POLL(I2C1->SR1, SR1_ADDR);
    (void)(I2C1->SR2);
    I2C1->DR = reg;
    POLL(I2C1->SR1, SR1_TxE);

    I2C1->CR1 |= CR1_START;    /* repeated START */
    POLL(I2C1->SR1, SR1_SB);
    I2C1->DR = ((slave_addr << 1) | 1); 
    POLL(I2C1->SR1, SR1_ADDR);
    I2C1->CR1 &= ~CR1_ACK;     /* NACK the single incoming byte */
    (void)(I2C1->SR2);          /* clears ADDR flag */
    I2C1->CR1 |= CR1_STOP;
    POLL(I2C1->SR1, SR1_RxNE);

    uint8_t data = (uint8_t)I2C1->DR;
    I2C1->CR1 |= CR1_ACK;      /* restore ACK for subsequent transactions */
    return (int)data;
}
