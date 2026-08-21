#ifndef UART_H
#define UART_H

#include <stdint.h>

// USART2 TX = PA2, AF7 (wired to ST-Link VCP on Nucleo)
#define UART_TX_PIN  2

// Status Register
#define SR_TXE  (1 << 7)   // Transmit data register empty
#define SR_TC   (1 << 6)   // Transmission complete

// Control Register 1
#define UART_CR1_UE  (1 << 13)  // USART enable
#define UART_CR1_TE  (1 << 3)   // Transmitter enable

// BRR for 115200 baud @ 42 MHz APB1
// USARTDIV = 42,000,000 / (16 * 115200) = 22.786
// Mantissa = 22 (0x16), Fraction = round(0.786 * 16) = 13 (0xD)
// Actual baud = 42,000,000 / (16 * 22.8125) = 115,068 — 0.11% error
#define UART_BRR_115200  0x016D

void UART_Init(void);
void UART_SendByte(uint8_t byte);
void UART_SendBuffer(const uint8_t *buf, uint16_t len);

#endif
