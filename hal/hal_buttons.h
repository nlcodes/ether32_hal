#ifndef HAL_BUTTONS_H
#define HAL_BUTTONS_H

#include <stdint.h>

void hal_gpio_init();
void hal_read_write_buttons(volatile uint8_t *matrix_buttons);

#endif
