#ifndef HAL_OLED_H
#define HAL_OLED_H

#include <stdint.h>
#include <stddef.h>

/* Writing functions */

/* Width is how many horizontal px to write to; height is how many pages */
void hal_display_write(uint8_t *data, uint8_t page, uint8_t col, uint8_t width, uint8_t height);
void hal_display_fill(uint8_t data);
void hal_display_write_bitmap(uint8_t *bitmap_data);

#endif
