#ifndef LED_BLINK_H
#define LED_BLINK_H

#include "../../globals.h"

/* Bit set/reset register */
#define GPIOC_BSRR (*(volatile uint32_t *)(GPIOC_BASE + 0x18))

void led_blink();

#endif
