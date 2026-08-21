#include <gpio.h>
#include <stm32f446_regs.h>
#include <stdint.h>

void GPIO_InitOutput(GPIO_Regs *port, uint8_t pin) {
    port->MODER  &= ~GPIO_MODER_CLEAR(pin);
    port->MODER  |=  GPIO_MODER_OUTPUT(pin);
    port->OTYPER &= ~GPIO_OTYPER_OPEN_DRAIN(pin); /* push-pull */
    port->PUPDR  &= ~GPIO_PUPDR_CLEAR(pin);        /* no pull  */
}

void GPIO_SetPin(GPIO_Regs *port, uint8_t pin) {
    port->BSRR = GPIO_BSRR_SET(pin);
}

void GPIO_ClearPin(GPIO_Regs *port, uint8_t pin) {
    port->BSRR = GPIO_BSRR_RESET(pin);
}
