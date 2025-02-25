#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

/* Reset and Clock Control base address */
#define RCC_BASE 0x40023800

/* GPIO base addresses */
#define GPIOB_BASE 0x40020400
#define GPIOC_BASE 0x40020800

/* GPIO clock enable register */
#define RCC_AHB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x30))

/* I2C */
#define RCC_APB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x40)) 

/* Mode register */
#define GPIOC_MODER (*(volatile uint32_t *)(GPIOC_BASE + 0x00))

#endif
