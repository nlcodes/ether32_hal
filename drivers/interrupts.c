#include "interrupts.h"
#include "../hal/hal.h"

volatile uint8_t ir_delay_done = 0;

void TIM2_IRQHandler(void) {
  if (TIM2_SR & TIM_SR_UIF) {
    ir_delay_done = 1;
    TIM2_SR &= ~TIM_SR_UIF;
  }
}

void timer_interrupt_init(uint16_t delay_ms) {
  __disable_irq();

  /* Enable timer 2 clock */
  RCC_APB1ENR |= (1 << 0);

  /* Config timer */
  TIM2_PSC = 16000-1;
  TIM2_ARR = delay_ms-1;

  /* Set interrupt priority before enabling */
  NVIC_SetPriority(TIM2_IRQn, 2);

  /* Enable timer interrupt */
  TIM2_DIER |= TIM_DIER_UIE;

  /* Enable in nvic */
  NVIC_ISER0 |= (1 << TIM2_IRQn);

  /* Update registers */
  TIM2_EGR |= 0x1;

  /* Start timer */
  TIM2_CR1 |= TIM_CR1_CEN;

  __enable_irq();
}

uint8_t timer_interrupt_check() {
  return ir_delay_done;
}

void timer_interrupt_reset() {
  ir_delay_done = 0;
}

void timer_interrupt_change_delay(uint16_t delay_ms) {
  TIM2_ARR = delay_ms -1;
  TIM2_EGR |= 0x1;
}
