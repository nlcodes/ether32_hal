#include "hal.h"
#include "hal_oled.h"
#include "../drivers/adafruit_stemma_qt_ssd1306/oled.h"

void hal_display_init() {
  display_init();
}

void hal_display_write(uint8_t *data, uint8_t page, uint8_t col, uint8_t width, uint8_t height) {
  display_write(data, page, col, width, height);
}

void hal_display_fill(uint8_t data) {
  display_fill(data);
}

void hal_display_write_bitmap(uint8_t *bitmap_data) {
  display_write_bitmap(bitmap_data);
}
