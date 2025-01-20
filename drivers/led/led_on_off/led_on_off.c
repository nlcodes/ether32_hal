#include "led_on_off.h"

void led_on_off(volatile uint8_t running) {

  /* GPIOC clock */
  RCC_AHB1ENR |= (1 << 2); 

  /* PC13 output */
  GPIOC_MODER |= (1 << 26);

  if (running) {

    /* LED ON (low) */
    GPIOC_ODR &= ~(1 << 13);
  } else if (!running) {

    /* LED OFF (high) */
    GPIOC_ODR |= (1 << 13);
  }
}
