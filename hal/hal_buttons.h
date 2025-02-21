#ifndef HAL_BUTTONS_H
#define HAL_BUTTONS_H

#include <stdint.h>

void hal_gpio_init();
void hal_read_write_buttons(int *matrix_buttons);

#endif
