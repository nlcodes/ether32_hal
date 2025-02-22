#ifndef LED_ON_OFF_H 
#define LED_ON_OFF_H

#include "../../globals.h"

/* Output data register */
#define GPIOC_ODR (*(volatile uint32_t *)(GPIOC_BASE + 0x14))

void led_on_off(volatile uint8_t running);

#endif
