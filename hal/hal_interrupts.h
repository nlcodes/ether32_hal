#ifndef HAL_INTERRUPTS_H
#define HAL_INTERRUPTS_H

#include <stdint.h>

/* Init function for timer interrupt
 * Called once per program when using stm32_hal
 * This initializes the timer interrupt for re use 
 * You can then use other hal functions below to
 * check if the delay is done,
 * reset the timer, and change the delay timing
 * Timer interrupts must be initialized before any
 * peripherals are initialized
 */
void hal_timer_interrupt_init(uint32_t delay_ns);

/* Checks to see if delay is done */
uint8_t hal_timer_interrupt_check();

/* Resets the interrupt timer */
void hal_timer_interrupt_reset();

/* Change delay timing initially set with hal_timer_interrupt_init() */
void hal_timer_interrupt_change_delay(uint32_t delay_ns);

#endif
