#ifndef BUTTONS_H
#define BUTTONS_H

#include "../globals.h"

/* GPIOB */
#define GPIOB_MODER (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_PUPDR (*(volatile uint32_t *)(GPIOB_BASE + 0x0C))

/* Input register for gpiob
 * Read only register which represents HIGH or LOW electrical state
 */
#define GPIOB_IDR (*(volatile uint32_t *)(GPIOB_BASE + 0x10))

/* Writing register for changing state from HIGH or LOW */
#define GPIOB_ODR (*(volatile uint32_t *)(GPIOB_BASE + 0x14))

void gpio_init();

void read_write_buttons(volatile uint8_t *matrix_buttons);

#endif
