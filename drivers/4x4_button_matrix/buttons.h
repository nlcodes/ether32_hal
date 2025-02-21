#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>

#define RCC_BASE 0x40023800
#define GPIOB_BASE 0x40020400

#define RCC_AHB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define GPIOB_MODER (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_PUPDR (*(volatile uint32_t *)(GPIOB_BASE + 0x0C))

/* Input register for gpiob
 * Read only register which represents HIGH or LOW electrical state
 */
#define GPIOB_IDR (*(volatile uint32_t *)(GPIOB_BASE + 0x10))

/* Writing register for changing state from HIGH or LOW */
#define GPIOB_ODR (*(volatile uint32_t *)(GPIOB_BASE + 0x14))

void gpio_init();

void read_write_buttons(int *matrix_buttons);

#endif
