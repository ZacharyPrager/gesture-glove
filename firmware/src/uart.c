#include <uart.h>
#include <stm32f446_regs.h>
#include <rcc.h>
#include <gpio.h>
#include <stdint.h>

void UART_Init(void) {
    RCC->APB1ENR |= APB1ENR_USART2EN;
    RCC->AHB1ENR |= AHB1ENR_GPIOAEN;

    /* PA2 = USART2_TX, AF7, push-pull */
    GPIOA->MODER &= ~GPIO_MODER_CLEAR(UART_TX_PIN);
    GPIOA->MODER |=  GPIO_MODER_ALT_FUNC(UART_TX_PIN);
    GPIOA->AFRL  &= ~GPIO_AFRL_CLEAR(UART_TX_PIN);
    GPIOA->AFRL  |=  GPIO_AFRL_AF7(UART_TX_PIN);

    USART2->BRR = UART_BRR_115200;
    USART2->CR1 = UART_CR1_TE | UART_CR1_UE;
}

void UART_SendByte(uint8_t byte) {
    while (!(USART2->SR & SR_TXE));
    USART2->DR = byte;
}

void UART_SendBuffer(const uint8_t *buf, uint16_t len) {
    for (uint16_t i = 0; i < len; i++) {
        UART_SendByte(buf[i]);
    }
}
