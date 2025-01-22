#ifndef HAL_OLED_H
#define HAL_OLED_H

#include <stdint.h>
#include <stddef.h>

/* Writing functions */
void hal_display_write(uint8_t *data, uint8_t page, uint8_t col, uint8_t width, uint8_t height);
void hal_display_fill(uint8_t data);

#endif
