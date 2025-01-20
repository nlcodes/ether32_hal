#include "led_blink.h"

void led_blink() {

  /* Enable GPIOC clock */
  RCC_AHB1ENR |= (1 << 2);

  /* PC13 as output */
  GPIOC_MODER |= (1 << 26);

  while(1) {

    /* LED ON */
    GPIOC_BSRR = (1 << 13);     
    for(volatile int i = 0; i < 500000; i++);

    /* LED OFF */
    GPIOC_BSRR = (1 << 29);      
    for(volatile int i = 0; i < 500000; i++);
  }
}
