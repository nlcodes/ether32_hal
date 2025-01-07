#include <stdint.h>

/* Reset and Clock Control base address */
#define RCC_BASE 0x40023800

/* Clock enable register */
#define RCC_AHB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x30))

/* GPIO Port C base address */
#define GPIOC_BASE 0x40020800

/* Mode register */
#define GPIOC_MODER (*(volatile uint32_t *)(GPIOC_BASE + 0x00))

/* Bit set/reset register */
#define GPIOC_BSRR (*(volatile uint32_t *)(GPIOC_BASE + 0x18))

int main() {

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
