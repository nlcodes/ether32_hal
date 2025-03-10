#include "led_blink.h"
#include "../../interrupts.h"

void led_blink() {

  /* Enable GPIOC clock */
  RCC_AHB1ENR |= (1 << 2);

  /* PC13 as output */
  GPIOC_MODER |= (1 << 26);

  timer_interrupt_change_delay(62500000);

  while(1) {

    /* LED ON */
    GPIOC_BSRR = (1 << 13); 

    timer_interrupt_reset();
    while(!timer_interrupt_check());

    /* LED OFF */
    GPIOC_BSRR = (1 << 29);    

    timer_interrupt_reset();
    while(!timer_interrupt_check());
  }
}
