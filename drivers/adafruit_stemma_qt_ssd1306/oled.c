#include "oled.h"
#include "../interrupts.h"
#include <string.h>

/* Minimum reliable timer delay on tested mcu is 4250ns 
 * Lower values may be not be effective
 */

/* Display buffer for 128x64 oled */
uint8_t display_buffer[1024] = {0};

/* Init I2C */
void i2c_init() {

  /* Turn on clocks for peripherals */

  /* Enable GPIOB */ 
  RCC_AHB1ENR |= (1 << 1); 
  
  /* Enable I2C1 */
  RCC_APB1ENR |= (1 << 21); 
  
  timer_interrupt_change_delay(6250000);
  timer_interrupt_reset();
  while(!timer_interrupt_check());

  /* GPIO config; set pins to alternate function mode */
  *(volatile uint32_t *)(GPIOB_BASE + 0x00) |= (2 << 12) | (2 << 14);
  *(volatile uint32_t *)(GPIOB_BASE + 0x20) |= (4 << 24) | (4 << 28);

  /* Enable pull ups on PB6/PB7 */
  *(volatile uint32_t *)(GPIOB_BASE + 0x0C) |= (1 << 12) | (1 << 14);

  /* Set to open-drain mode */
  *(volatile uint32_t *)(GPIOB_BASE + 0x04) |= (1 << 6) | (1 << 7);

  /* Config I2C */

  /* APB1 clock frequency */
  I2C1_CR2 = 16;  

  /* Clock control register */
  I2C1_CCR = 80; 

  /* Rise time register */
  I2C1_TRISE = 17;   

  /* Enable I2C */
  I2C1_CR1 |= 1;                
}

/* I2C write function for STM32 */
void i2c_write(uint8_t address, uint8_t *data, uint8_t len) {

  /* Wait for bus free */
  while (I2C1_SR2 & (1 << 1));  

  /* Generate START condition */
  I2C1_CR1 |= (1 << 8);

  /* Wait for SB (Start Bit) */
  while(!(I2C1_SR1 & (1 << 0)));

  /* Send address + Write bit (0) */

  /* Ensure write bit is 0 */
  I2C1_DR = (address << 1) & 0xFE;  
  
  /* Wait for ADDR (EV6) */
  while(!(I2C1_SR1 & (1 << 1)));    
  
  /* Clear ADDR flag */
  (void)I2C1_SR1;                  
  (void)I2C1_SR2;

  /* Send data bytes */
  for(uint8_t i = 0; i < len; i++) {

    /* Wait for TxE (Transmit Buffer Empty) */
    while(!(I2C1_SR1 & (1 << 7)));  
    I2C1_DR = data[i];

    timer_interrupt_change_delay(4250);
    timer_interrupt_reset();
    while(!timer_interrupt_check());
  }

  /* Wait for BTF (Byte Transfer Finished) */
  while(!(I2C1_SR1 & (1 << 2)));

  /* Generate STOP condition */
  I2C1_CR1 |= (1 << 9);

  /* Wait for STOP to clear */
  while(I2C1_CR1 & (1 << 9));  
}

/* Send command function for SSD1306 screen */
void ssd1306_command(uint8_t command) {

  /* Control byte followed by command byte */
  uint8_t data[2] = {0x00, command};  
  i2c_write(0x3D, data, 2);

  timer_interrupt_change_delay(6250);
  timer_interrupt_reset();
  while(!timer_interrupt_check());
}

void oled_init() {

  /*
   * Initialize the SSD1306 OLED display by sending a sequence of commands.
   * Each command configures a specific aspect of the display.
   */

  /* Display off */
  ssd1306_command(0xAE);

  /* Set display clock divide */
  ssd1306_command(0xD5);

  /* Divide value */
  ssd1306_command(0x80);

  /* Set multiplex ratio */
  ssd1306_command(0xA8);

  /* Multiplex ratio for 128x64 screen */
  ssd1306_command(0x3F);

  /* Set display offset */
  ssd1306_command(0xD3);

  /* No offset */
  ssd1306_command(0x00);

  /* Set start line */
  ssd1306_command(0x40);

  /* Charge pump command */
  ssd1306_command(0x8D);

  /* Enable charge pump */
  ssd1306_command(0x14);

  /* Memory mode */
  ssd1306_command(0x20);

  /* Horizontal addressing mode */
  ssd1306_command(0x02);

  /* Segment remap */
  ssd1306_command(0xA1);

  /* Set COM output scan direction */
  ssd1306_command(0xC8);

  /* Set COM pins hardware config */
  ssd1306_command(0xDA);

  /* 128x64 display config */
  ssd1306_command(0x12);

  /* Set contrast control */
  ssd1306_command(0x81);

  /* Set contrast value */
  ssd1306_command(0xCF);

  /* Set precharge period */
  ssd1306_command(0xD9);

  /* Precharge period value */
  ssd1306_command(0xF1);

  /* Set VCOMH deselect level */
  ssd1306_command(0xDB);

  /* VCOMH deselect level value */
  ssd1306_command(0x40);

  /* Resume from RAM content */
  ssd1306_command(0xA4);

  /* Normal display */
  ssd1306_command(0xA6);

  /* Display ON */
  ssd1306_command(0xAF);
}

/* Main driver functions */

/* Write data to screen */
void display_write(uint8_t *data, uint8_t col, uint8_t page, uint8_t width, uint8_t height) {
  for(uint8_t i = 0; i < height; i++) {

    /* Set page, col low and high */
    ssd1306_command(0xB0 + page + i);
    ssd1306_command(0x00 | (col & 0x0F));
    ssd1306_command(0x10 | ((col >> 4) & 0x0F));

    for(uint8_t j = 0; j < width; j++) {

      /* Control byte followed by data byte */
      uint8_t data_packet[2] = {0x40, (uint8_t)data[i * width + j]};
      i2c_write(0x3D, data_packet, 2);

      timer_interrupt_change_delay(4250);
      timer_interrupt_reset();
      while(!timer_interrupt_check());
    }
  }
}

/* Fill the entire screen with a specific pattern */
void display_fill(uint8_t pattern) {
  uint8_t buffer[128];
  memset(buffer, pattern, sizeof(buffer));

  for(uint8_t page = 0; page < 8; page++) {
    display_write(buffer, 0, page, 128, 1);
  }
}

/* Write any 128x64 bitmap data */
void display_write_bitmap(uint8_t *bitmap_data) {

  /* Call display_write with hardcoded values */
  display_write(bitmap_data, 0, 0, 128, 8);
}


/* Buffer functions */

/* Init buffer */
void buffer_init() {
  memset(display_buffer, 0, sizeof(display_buffer));
}

/* Change a single pixel in the buffer to black or white */
void buffer_set_pixel(uint8_t x, uint8_t y, uint8_t state) {

  /* Find page */
  uint8_t page = y / 8;

  /* Find bit in byte */
  uint8_t bit = y % 8;

  /* Find buffer index */
  uint16_t index = page * 128 + x;
  
  /* Set/clear the bit/pixel */
  if(state) {
    display_buffer[index] |= (1 << bit);
  } else {
    display_buffer[index] &= ~(1 << bit);
  }
}

/* Write entire buffer to screen */
void buffer_write() {
  display_write(display_buffer, 0, 0, 128, 8);
}

/* Clear pixels from drawn data
 * Useful if you want to remove drawn data 
 * For example, during the movement of a sprite 
 * one would clear the data, then draw sprite again 
 * in new position 
 * then draw the buffer
 */
void clear_binary_data(const uint8_t *data, uint8_t width, uint8_t height, uint8_t x, uint8_t y) {
  for(uint8_t row = 0; row < height; row++) {
    for(uint8_t col = 0; col < width; col++) {

      /* Clear pixels that were set in original data */
      if(data[row * width + col]) {
        buffer_set_pixel(x + col, y + row, 0);
      }
    }
  }
}

/* Draws data from a binary bitmap list 0,0,0,1 etc */
void draw_binary_data(const uint8_t *data, uint8_t width, uint8_t height, uint8_t x, uint8_t y) {
  for(uint8_t row = 0; row < height; row++) {
    for(uint8_t col = 0; col < width; col++) {
      
      /* Get pixel from array */
      uint8_t pixel = data[row * width + col];
      
      /* Set white pixels */
      if(pixel) {
        buffer_set_pixel(x + col, y + row, 1);
      }
    }
  }
}

void display_init() {

  /* Delay to allow reliable startup */
  timer_interrupt_change_delay(3000000000);
  timer_interrupt_reset();
  while(!timer_interrupt_check());

  i2c_init();

  timer_interrupt_change_delay(3000000000);
  timer_interrupt_reset();
  while(!timer_interrupt_check());

  oled_init();

  buffer_init();

  /* Clear the display; turn off while clearing to avoid pixel flashing */
  ssd1306_command(0xAE);
  display_fill(0x00);
  ssd1306_command(0xAF);
}
