#ifndef HAL_OLED_H
#define HAL_OLED_H

#include <stdint.h>
#include <stddef.h>

/* Writing functions */

/* Width is how many horizontal px to write to; height is how many pages */
void hal_display_write(uint8_t *data, uint8_t col, uint8_t page, uint8_t width, uint8_t height);
void hal_display_fill(uint8_t data);
void hal_display_write_bitmap(uint8_t *bitmap_data);

/* Buffer functions */
void hal_buffer_init();
void hal_buffer_set_pixel(uint8_t x, uint8_t y, uint8_t state);
void hal_buffer_write();

/* Write binary data using buffer */
void hal_draw_binary_data(const uint8_t *data, uint8_t width, uint8_t height, uint8_t x, uint8_t y);
void hal_clear_binary_data(const uint8_t *data, uint8_t width, uint8_t height, uint8_t x, uint8_t y);

#endif
