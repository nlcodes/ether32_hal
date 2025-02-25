#include "hal_buttons.h"
#include "../drivers/4x4_button_matrix/buttons.h"

/* Inits gpio for 4x4 button board
 * Call before hal_read_write
 */
void hal_gpio_init() {
  gpio_init();
}

/* Reads and writes button matrix
 * Stores button state in passed array as being pressed(1) or released(0)
 */
void hal_read_write_buttons(volatile uint8_t *matrix_buttons) {
  read_write_buttons(matrix_buttons);
}
