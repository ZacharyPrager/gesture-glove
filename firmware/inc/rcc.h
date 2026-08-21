#ifndef RCC_H
#define RCC_H

#include <stm32f446_regs.h>
#include <stdint.h>

// Control Register
#define CR_PLLSAION   (1 << 28)
#define CR_PLLI2SON   (1 << 26)
#define CR_PLLON      (1 << 24)
#define CR_CSSON      (1 << 19)
#define CR_HSEBYP     (1 << 18)
#define CR_HSEON      (1 << 16)
#define CR_HSITRIM4   (1 << 7)
#define CR_HSITRIM3   (1 << 6)
#define CR_HSITRIM2   (1 << 5)
#define CR_HSITRIM1   (1 << 4)
#define CR_HSITRIM0   (1 << 3)
#define CR_HSION      (1 << 0)

// PLL Configuration Register
#define PLLCFGR_PLLSRC   (1 << 22)

// Clock Configuration Register
#define CFGR_MCO2_1       (1 << 31)
#define CFGR_MCO2_0       (1 << 30)
#define CFGR_MCO1_1       (1 << 22)
#define CFGR_MCO1_0       (1 << 21)
#define CFGR_I2SSRC       (1 << 23)

// Clock Interrupt Register
#define CIR_CSSC          (1 << 23)
#define CIR_PLLSAIRDYC    (1 << 22)
#define CIR_PLLI2CSIRDYC  (1 << 21)
#define CIR_PLLRDYC       (1 << 20)
#define CIR_HSERDYC       (1 << 19)
#define CIR_HSIRDYC       (1 << 18)
#define CIR_LSERDYC       (1 << 17)
#define CIR_LSIRDYC       (1 << 16)

// AHB1 Peripheral Reset Register
#define AHB1RSTR_OTGHS      (1 << 29)
#define AHB1RSTR_DMA2RST    (1 << 22)
#define AHB1RSTR_DMA1RST    (1 << 21)
#define AHB1RSTR_CRCRST     (1 << 12)
#define AHB1RSTR_GPIOHRST   (1 << 7)
#define AHB1RSTR_GPIOERST   (1 << 4)
#define AHB1RSTR_GPIODRST   (1 << 3)
#define AHB1RSTR_GPIOCRST   (1 << 2)
#define AHB1RSTR_GPIOBRST   (1 << 1)
#define AHB1RSTR_GPIOARST   (1 << 0)

// AHB2 Peripheral Reset Register
#define AHB2RSTR_OTGFSRST   (1 << 7)

// AHB3 Peripheral Reset Register
#define AHB3RSTR_FMCRST     (1 << 0)

// APB1 Peripheral Reset Register
#define APB1RSTR_PWRRST     (1 << 28)
#define APB1RSTR_I2C3RST    (1 << 23)
#define APB1RSTR_I2C2RST    (1 << 22)
#define APB1RSTR_I2C1RST    (1 << 21)
#define APB1RSTR_USART2RST  (1 << 17)
#define APB1RSTR_SPI3RST    (1 << 15)
#define APB1RSTR_SPI2RST    (1 << 14)
#define APB1RSTR_WWDGRST    (1 << 11)
#define APB1RSTR_TIM5RST    (1 << 3)
#define APB1RSTR_TIM4RST    (1 << 2)
#define APB1RSTR_TIM3RST    (1 << 1)
#define APB1RSTR_TIM2RST    (1 << 0)

// APB2 Peripheral Reset Register
#define APB2RSTR_LTDCRST    (1 << 26)
#define APB2RSTR_SAI1RST    (1 << 22)
#define APB2RSTR_SPI4RST    (1 << 13)
#define APB2RSTR_SPI1RST    (1 << 12)
#define APB2RSTR_USART6RST  (1 << 5)
#define APB2RSTR_USART1RST  (1 << 4)
#define APB2RSTR_TIM11RST   (1 << 18)
#define APB2RSTR_TIM10RST   (1 << 17)
#define APB2RSTR_TIM9RST    (1 << 16)
#define APB2RSTR_TIM8RST    (1 << 1)
#define APB2RSTR_TIM1RST    (1 << 0)

// AHB1 Peripheral Clock Enable Register
#define AHB1ENR_OTGHSEN     (1 << 29)
#define AHB1ENR_DMA2EN      (1 << 22)
#define AHB1ENR_DMA1EN      (1 << 21)
#define AHB1ENR_CRCEN       (1 << 12)
#define AHB1ENR_GPIOHEN     (1 << 7)
#define AHB1ENR_GPIOEEN     (1 << 4)
#define AHB1ENR_GPIODEN     (1 << 3)
#define AHB1ENR_GPIOCEN     (1 << 2)
#define AHB1ENR_GPIOBEN     (1 << 1)
#define AHB1ENR_GPIOAEN     (1 << 0)

// AHB2 Peripheral Clock Enable Register
#define AHB2ENR_OTGFSEN     (1 << 7)

// AHB3 Peripheral Clock Enable Register
#define AHB3ENR_FMCEN       (1 << 0)

// APB1 Peripheral Clock Enable Register
#define APB1ENR_PWREN       (1 << 28)
#define APB1ENR_I2C3EN      (1 << 23)
#define APB1ENR_I2C2EN      (1 << 22)
#define APB1ENR_I2C1EN      (1 << 21)
#define APB1ENR_USART2EN    (1 << 17)
#define APB1ENR_SPI3EN      (1 << 15)
#define APB1ENR_SPI2EN      (1 << 14)
#define APB1ENR_WWDGEN      (1 << 11)
#define APB1ENR_TIM5EN      (1 << 3)
#define APB1ENR_TIM4EN      (1 << 2)
#define APB1ENR_TIM3EN      (1 << 1)
#define APB1ENR_TIM2EN      (1 << 0)

// APB2 Peripheral Clock Enable Register
#define APB2ENR_LTDCEN      (1 << 26)
#define APB2ENR_SAI1EN      (1 << 22)
#define APB2ENR_SPI4EN      (1 << 13)
#define APB2ENR_SPI1EN      (1 << 12)
#define APB2ENR_USART6EN    (1 << 5)
#define APB2ENR_USART1EN    (1 << 4)
#define APB2ENR_TIM11EN     (1 << 18)
#define APB2ENR_TIM10EN     (1 << 17)
#define APB2ENR_TIM9EN      (1 << 16)
#define APB2ENR_TIM8EN      (1 << 1)
#define APB2ENR_TIM1EN      (1 << 0)

// AHB1 Peripheral Low Power Clock Enable Register
#define AHB1LPENR_GPIOHLPEN (1 << 7)
#define AHB1LPENR_GPIOELPEN (1 << 4)
#define AHB1LPENR_GPIODLPEN (1 << 3)
#define AHB1LPENR_GPIOCLPEN (1 << 2)
#define AHB1LPENR_GPIOBLPEN (1 << 1)
#define AHB1LPENR_GPIOALPEN (1 << 0)

// AHB2 Peripheral Low Power Clock Enable Register
#define AHB2LPENR_OTGFSLPEN (1 << 7)

// AHB3 Peripheral Low Power Clock Enable Register
#define AHB3LPENR_FMCLPEN   (1 << 0)

// APB1 Peripheral Low Power Clock Enable Register
#define APB1LPENR_PWRLPEN   (1 << 28)
#define APB1LPENR_I2C3LPEN  (1 << 23)
#define APB1LPENR_I2C2LPEN  (1 << 22)
#define APB1LPENR_I2C1LPEN  (1 << 21)
#define APB1LPENR_TIM2LPEN  (1 << 0)

// APB2 Peripheral Low Power Clock Enable Register
#define APB2LPENR_USART6LPEN (1 << 5)
#define APB2LPENR_USART1LPEN (1 << 4)
#define APB2LPENR_TIM1LPEN   (1 << 0)

// Backup Domain Control Register
#define BDCR_BDRST        (1 << 16)
#define BDCR_RTCEN        (1 << 15)
#define BDCR_RTCSEL1      (1 << 9)
#define BDCR_RTCSEL0      (1 << 8)
#define BDCR_LSEBYP       (1 << 2)
#define BDCR_LSERDY       (1 << 1)
#define BDCR_LSEON        (1 << 0)

// Clock Control and Status Register
#define CSR_LPWRRSTF      (1U << 31)
#define CSR_WWDGRSTF      (1 << 30)
#define CSR_IWDGRSTF      (1 << 29)
#define CSR_SFTRSTF       (1 << 28)
#define CSR_PORRSTF       (1 << 27)
#define CSR_PINRSTF       (1 << 26)
#define CSR_BORRSTF       (1 << 25)
#define CSR_RMVF          (1 << 24)
#define CSR_LSIRDY        (1 << 1)
#define CSR_LSION         (1 << 0)

// Spread Spectrum Clock Generation Register
#define SSCGR_SSCGEN      (1U << 31)

// PLLI2S Configuration Register
#define PLLI2SCFGR_PLLI2SON (1 << 26)

// PLLSAI Configuration Register
#define PLLSAICFGR_PLLSAION (1 << 28)

// Dedicated Clock Configuration Register
#define DCKCFGR_TIMPRE     (1 << 24)

// Clock Gating Enable Register
#define CKGATENR_AHB2RSTR  (1 << 3)

// Dedicated Clock Configuration Register 2
#define DCKCFGR2_I2C3SEL1  (1 << 23)
#define DCKCFGR2_I2C3SEL0  (1 << 22)
#define DCKCFGR2_I2C2SEL1  (1 << 21)
#define DCKCFGR2_I2C2SEL0  (1 << 20)
#define DCKCFGR2_I2C1SEL1  (1 << 19)
#define DCKCFGR2_I2C1SEL0  (1 << 18)

#endif