hal

About:
  This file serves as documentation for stm32_hal
  Specifically, this covers the functions contained in the hal,
  what they accomplish, and how to go about implementing them

Instructions:
  Intrustions regarding how to use the hal are included in the master
  directory of stm32_hal, in the readme.txt file located there

HAL Function Instructions and Explainations:

OLED:
  Functions which cover initialization and writing data to
  128x64 ssd1306 oled using i2c protocol

  Initializes oled using i2c
  Call this function before any write functions
    void hal_display_init();

  Writes pixels to the oled screen
  Takes an array of hex values as first argument
  These hex values represent 8 pixels represented by either 1 or 0
  It then takes column and row as arguments to determine the location
  to begin writing the data 
  Finally it takes width and height of the image as its last argument,
  so it can determine where the data is to stop being written
  Width value is in pixels while height is in oled pages
    void hal_display_write(uint8_t *data, uint8_t page, uint8_t col, uint8_t width, uint8_t height);
    
  Fills the whole screen with either white (0xFF) or black (0x00) pixels
    void hal_display_fill(uint8_t data);

  Writes any 128x64 bitmap data to the oled
  Takes array of the data as an argument expecting hex values
    void hal_display_write_bitmap(uint8_t *bitmap_data);

Button Matrix:
  Functions which cover initialization and reading button inputs
  from 4x4 button matrix using gpio
  
  Call first to initialize gpio for reading and writing button matrix
    void hal_gpio_init();
  
  Takes array as input
  Manages state for button board after passing an array 
  created in program using the hal function
  Stores button state in passed array as being pressed (1) or released (0)
  After figuring where each index is mapped to each button (they are
  sequencially mapped) do some action based on button state as required
  by program
    void hal_read_write_buttons(volatile uint8_t *matrix_buttons);

Test Led:
  Functions which allow blinking or toggling on/off for
  the test led on board the stm32 
  Useful for debugging purposes

  Takes either 1 or 0 as input for on/off toggling
  Called as needed to switch state
    void hal_led_on_off(volatile uint8_t running);

  Indefinitely blinks test led
    void hal_led_blink();

