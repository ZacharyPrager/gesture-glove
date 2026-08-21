#ifndef GPIO_H
#define GPIO_H

#include <stm32f446_regs.h>
#include <stdint.h>

// Mode Register
#define GPIO_MODER_CLEAR(pin)        (3U << ((pin) * 2))
#define GPIO_MODER_ALT_FUNC(pin)     (2U << ((pin) * 2))
#define GPIO_MODER_OUTPUT(pin)       (1U << ((pin) * 2))
#define GPIO_MODER_INPUT(pin)        (0U << ((pin) * 2))

// Output Type Register
#define GPIO_OTYPER_OPEN_DRAIN(pin)  (1U << (pin))
#define GPIO_OTYPER_PUSH_PULL(pin)   (0U << (pin))

// Output Speed Register
#define GPIO_OSPEEDER_HIGH(pin)      (3U << ((pin) * 2))
#define GPIO_OSPEEDER_FAST(pin)      (2U << ((pin) * 2))
#define GPIO_OSPEEDER_MEDIUM(pin)    (1U << ((pin) * 2))
#define GPIO_OSPEEDER_LOW(pin)       (0U << ((pin) * 2))

// Pull-Up/Pull-Down Register
#define GPIO_PUPDR_CLEAR(pin)        (3U << ((pin) * 2))
#define GPIO_PUPDR_PULLDOWN(pin)     (2U << ((pin) * 2))
#define GPIO_PUPDR_PULLUP(pin)       (1U << ((pin) * 2))
#define GPIO_PUPDR_NONE(pin)         (0U << ((pin) * 2))

// Input Data Register
#define GPIO_IDR(pin)                (1U << (pin))

// Output Data Register
#define GPIO_ODR(pin)                (1U << (pin))

/* BSRR allows atomic set/reset with a single write — upper 16 bits clear, lower 16 set */
#define GPIO_BSRR_SET(pin)           (1U << (pin))
#define GPIO_BSRR_RESET(pin)         (1U << ((pin) + 16))

// Alternate Function Register Low
#define GPIO_AFRL_CLEAR(pin)         (0xFU << ((pin) * 4))
#define GPIO_AFRL_AF4(pin)           (4U << ((pin) * 4))
#define GPIO_AFRL_AF7(pin)           (7U << ((pin) * 4))

// Alternate Function Register High
#define GPIO_AFRH_CLEAR(pin)         (0xFU << (((pin) - 8) * 4))
#define GPIO_AFRH_AF4(pin)           (4U << (((pin) - 8) * 4))
#define GPIO_AFRH_AF7(pin)           (7U << (((pin) - 8) * 4))

void GPIO_InitOutput(GPIO_Regs *port, uint8_t pin);
void GPIO_SetPin(GPIO_Regs *port, uint8_t pin);
void GPIO_ClearPin(GPIO_Regs *port, uint8_t pin);

#endif