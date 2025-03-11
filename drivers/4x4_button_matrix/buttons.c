#include "buttons.h"
#include "../interrupts.h"

void gpio_init() {

  /* Enable GPIOB clock */
  RCC_AHB1ENR |= (1 << 1);

  /* Set interrupt delay*/
  timer_interrupt_change_delay(6250);

  /* Interrupt handles timing */
  timer_interrupt_reset();  
  while(!timer_interrupt_check());

  /* Set PB12-15 as inputs with pull-up (rows) */
  /* Clear mode bits */
  GPIOB_MODER &= ~(0xFF << 24);

  /* Clear pullup bits first */
  GPIOB_PUPDR &= ~(0xFF << 24);  
  
  /* Set pullup for PB12-15 */
  GPIOB_PUPDR |= (0x55 << 24);   
  
  /* Set PB0-3 as outputs (columns) */
  /* Clear bits 0-7 */
  GPIOB_MODER &= ~(0xFF);

  /* Set to output mode */
  GPIOB_MODER |= 0x55;
}

void read_write_buttons(volatile uint8_t *matrix_buttons) {

  /* Columns */
  for(int i = 0; i < 4; i++) {
    GPIOB_ODR = ~(1 << i);  

    /* Wait for timer interrupt signal after setting ODR */
    timer_interrupt_change_delay(6250);
    timer_interrupt_reset();
    while(!timer_interrupt_check());

    uint32_t rows = GPIOB_IDR;

    /* Rows
     * Map all 4x4 button matrix to array
     * Each button is represented as 0 or 1
     * State changes to 1 while button is held
     */
    for(int j = 0; j < 4; j++) {
      if(!(rows & (1 << (j + 12)))) {
        matrix_buttons[(j * 4) + i] = 1;
      } else {
        matrix_buttons[(j * 4) + i] = 0;
      }
    }
  } 
}
