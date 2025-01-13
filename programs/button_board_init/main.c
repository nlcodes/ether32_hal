#include "stm32_drivers/led/led_on_off.h"
#include <stdint.h>

#define RCC_BASE 0x40023800
#define GPIOB_BASE 0x40020400

#define RCC_AHB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define GPIOB_MODER (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_PUPDR (*(volatile uint32_t *)(GPIOB_BASE + 0x0C))
#define GPIOB_IDR (*(volatile uint32_t *)(GPIOB_BASE + 0x10))

int main() {
  
  /* Enable GPIOB clock */
  RCC_AHB1ENR |= (1 << 1);

  /* Set PB4 and PB5 input with pull up */
  GPIOB_MODER &= ~(3 << 8);
  GPIOB_PUPDR |= (1 << 8);
  GPIOB_MODER &= ~(3 << 10);
  GPIOB_PUPDR |= (1 << 10);

  while(1) {
    if(!(GPIOB_IDR & (1 << 4))) {
      led_on_off(1);
    } else if(!(GPIOB_IDR & (1 << 5))) {
      led_on_off(1);
    } else {
      led_on_off(0);
    }
  }
}
