#include "hal.h"
#include "hal_oled.h"
#include "../drivers/adafruit_stemma_qt_ssd1306/oled.h"

/* Write data directly to screen */
void hal_display_init() {
  display_init();
}

void hal_display_write(uint8_t *data, uint8_t col, uint8_t page, uint8_t width, uint8_t height) {
  display_write(data, col, page, width, height);
}

void hal_display_fill(uint8_t data) {
  display_fill(data);
}

void hal_display_write_bitmap(uint8_t *bitmap_data) {
  display_write_bitmap(bitmap_data);
}


/* Buffer manipulation and writing functions */
void hal_buffer_init() {
  buffer_init();
}

void hal_buffer_write() {
  buffer_write();
}

void hal_buffer_set_pixel(uint8_t x, uint8_t y, uint8_t state) {
  buffer_set_pixel(x, y, state);
}

void hal_draw_binary_data(const uint8_t *data, uint8_t width, uint8_t height, uint8_t x, uint8_t y) {
  draw_binary_data(data, width, height, x, y);
}

void hal_clear_binary_data(const uint8_t *data, uint8_t width, uint8_t height, uint8_t x, uint8_t y) {
  clear_binary_data(data, width, height, x, y);
}
