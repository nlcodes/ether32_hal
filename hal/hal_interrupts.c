#include "hal_interrupts.h"
#include "../drivers/interrupts.h"

void hal_timer_interrupt_init(uint32_t delay_ns) {
  timer_interrupt_init(delay_ns);
}

uint8_t hal_timer_interrupt_check() {
  return timer_interrupt_check();
}

void hal_timer_interrupt_reset() {
  timer_interrupt_reset();
}

void hal_timer_interrupt_change_delay(uint32_t delay_ns) {
  timer_interrupt_change_delay(delay_ns);
}
