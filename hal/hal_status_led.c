#include "hal_status_led.h"
#include "../drivers/led/led_on_off/led_on_off.h"
#include "../drivers/led/led_blink/led_blink.h"

/* State is 1 or 0 (on or off) */
void hal_led_on_off(volatile uint8_t running) {
  led_on_off(running);
}

void hal_led_blink() {
  led_blink();
}
