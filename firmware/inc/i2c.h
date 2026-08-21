#ifndef I2C_H
#define I2C_H

#include <stm32f446_regs.h>
#include <stdint.h>

// Pins for I2C1 — D15=PB8 (SCL), D14=PB9 (SDA) on Nucleo F446RE Arduino header
#define SCL_PIN 8
#define SDA_PIN 9

/* bit definitions */ 

// Control Register 1
#define CR1_SWRST (1U << 15)
#define CR1_ALERT (1U << 13)
#define CR1_PEC (1U << 12)
#define CR1_POS (1U << 11)
#define CR1_ACK (1U << 10)
#define CR1_STOP (1U << 9)
#define CR1_START (1U << 8)
#define CR1_NOSTRETCH (1U << 7)
#define CR1_ENGC (1U << 6)
#define CR1_ENPEC (1U << 5)
#define CR1_ENARP (1U << 4)
#define CR1_SMBTYPE (1U << 3)
#define CR1_SMBUS (1U << 1)
#define CR1_PE (1U << 0)

// Control Register 2
#define CR2_LAST (1U << 12)
#define CR2_DMAEN (1U << 11)
#define CR2_ITBUFEN (1U << 10)
#define CR2_ITEVTEN (1U << 9)
#define CR2_ITERREN (1U << 8)
#define CR2_FREQ (0x3FU)

// Own Address Register 1 & 2
#define OAR1_ADDMODE (1U << 15)
#define OAR1_BIT14 (1U << 14)
#define OAR2_ENDUAL (1U << 0)

// Status Register 1
#define SR1_SMBALERT (1U << 15)
#define SR1_TIMEOUT (1U << 14)
#define SR1_PECERR (1U << 12)
#define SR1_OVR (1U << 11)
#define SR1_AF (1U << 10)
#define SR1_ARLO (1U << 9)
#define SR1_BERR (1U << 8)
#define SR1_TxE (1U << 7)
#define SR1_RxNE (1U << 6)
#define SR1_STOPF (1U << 4)
#define SR1_ADD10 (1U << 3)
#define SR1_BTF (1U << 2)
#define SR1_ADDR (1U << 1)
#define SR1_SB (1U << 0)

// Status Register 2
#define SR2_DUALF (1U << 7)
#define SR2_SMBHOST (1U << 6)
#define SR2_SMBDEFAULT (1U << 5)
#define SR2_GENCALL (1U << 4)
#define SR2_TRA (1U << 2)
#define SR2_BUSY (1U << 1)
#define SR2_MSL (1U << 0)

// Clock Control Register
#define CCR_FS (1U << 15)
#define CCR_DUTY (1U << 14)

// FLTR
#define FLTR_ANOFF (1U << 4)

// Return codes
#define I2C_ERR_TIMEOUT  (-1)

// Function Prototypes
void I2C_init(void);
int I2C_MasterWrite(uint8_t data, uint8_t slave_addr);
int I2C_MasterRead(uint8_t slave_addr);
int I2C_WriteReg(uint8_t slave_addr, uint8_t data, uint8_t reg);
int I2C_ReadReg(uint8_t slave_addr, uint8_t reg);

// This function reads many bytes of data at a time, and stores them at a buffer location
int I2C_BurstRead(uint8_t slave_addr, uint8_t reg, uint8_t *buf, uint8_t len);

#endif