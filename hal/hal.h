#ifndef HAL_H
#define HAL_H

#include "hal_interrupts.h"
#include "hal_oled.h"
#include "hal_status_led.h"
#include "hal_buttons.h"

/* Include defined in hal.h to avoid linter error */
void hal_display_init();

#endif
