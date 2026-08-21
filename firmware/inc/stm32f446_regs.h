#ifndef STM32F446_REGS_H
#define STM32F446_REGS_H

#include <stdint.h>

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
    volatile uint32_t FLTR;
} I2C_Regs;

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    uint32_t res0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t res1;
    uint32_t res2;
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    uint32_t res3;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    uint32_t res4;
    uint32_t res5;
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    uint32_t res6;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    uint32_t res7;
    uint32_t res8;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    uint32_t res9;
    uint32_t res10;   
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
    volatile uint32_t PLLSAICFGR;
    volatile uint32_t DCKCFGR;
    volatile uint32_t CKGATENR;
    volatile uint32_t DCKCFGR2;
} RCC_Regs;

typedef struct {
    volatile uint32_t MODER; 
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDER;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
} GPIO_Regs;

typedef struct {
    volatile uint32_t SR; 
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} UART_Regs;


#define RCC   ((RCC_Regs  *) 0x40023800)

#define I2C1  ((I2C_Regs  *) 0x40005400)
#define I2C2  ((I2C_Regs  *) 0x40005800)
#define I2C3  ((I2C_Regs  *) 0x40005C00)

#define GPIOA ((GPIO_Regs *) 0x40020000)
#define GPIOB ((GPIO_Regs *) 0x40020400)
#define GPIOC ((GPIO_Regs *) 0x40020800)

#define USART2 ((UART_Regs *) 0x40004400)
#define UART4  ((UART_Regs *) 0x40004C00)
#define UART5  ((UART_Regs *) 0x40005000)

#endif