#ifndef STM32_HAL_H
#define STM32_HAL_H

#include <stdint.h>
#include <stddef.h>

/* SSD1306 OLED */
void hal_display_init();
void hal_display_write(uint8_t *data, size_t len);
void hal_display_fill(uint8_t data);

/* GPIO buttons */

/* Test LED */

#endif
