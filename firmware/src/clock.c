#include <clock.h>
#include <stm32f446_regs.h>
#include <rcc.h>

#define FLASH_ACR  (*((volatile uint32_t *)0x40023C00))

void clock_init(void) {
    RCC->CR |= CR_HSION;
    while (!(RCC->CR & (1 << 1)));

    /* 5 WS required at 168 MHz, 3.3 V; enable prefetch + instruction/data caches */
    FLASH_ACR = (5 << 0) | (1 << 8) | (1 << 9) | (1 << 10);

    /* HSI(16 MHz) / M(8) * N(168) / P(2) = 168 MHz SYSCLK
       VCO(336 MHz) / Q(7) = 48 MHz USB                      */
    RCC->PLLCFGR = (8   <<  0) |   /* PLLM = 8      */
                   (168 <<  6) |   /* PLLN = 168    */
                   (0   << 16) |   /* PLLP = 2 (00) */
                   (0   << 22) |   /* PLLSRC = HSI  */
                   (7   << 24);    /* PLLQ = 7      */

    RCC->CR |= CR_PLLON;
    while (!(RCC->CR & (1 << 25)));

    /* AHB = /1 → 168 MHz, APB1 = /4 → 42 MHz, APB2 = /2 → 84 MHz */
    RCC->CFGR |= (0 << 4)  |   /* HPRE  = /1 */
                 (5 << 10) |   /* PPRE1 = /4 */
                 (4 << 13);    /* PPRE2 = /2 */

    RCC->CFGR |= (2 << 0);
    while (((RCC->CFGR >> 2) & 0x3) != 2);
}
