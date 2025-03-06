#include "hal_interrupts.h"
#include "../drivers/interrupts.h"

void hal_timer_interrupt_init(uint16_t delay_ms) {
  timer_interrupt_init(delay_ms);
}

uint8_t hal_timer_interrupt_check() {
  return timer_interrupt_check();
}

void hal_timer_interrupt_reset() {
  timer_interrupt_reset();
}

void hal_timer_interrupt_change_delay(uint16_t delay_ms) {
  timer_interrupt_change_delay(delay_ms);
}
