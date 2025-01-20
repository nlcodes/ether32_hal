#include "stm32_drivers/led/led_on_off.h"
#include <stdint.h>

/* Key register */
#define I2C1_BASE 0x40005400
#define RCC_BASE 0x40023800
#define GPIOB_BASE 0x40020400

/* RCC registers for enabling peripherals */

/* GPIO */
#define RCC_AHB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x30))

/* I2C */
#define RCC_APB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x40)) 

/* I2C1 peripheral registers */
#define I2C1_CR1 (*(volatile uint32_t *)(I2C1_BASE + 0x00))
#define I2C1_CR2 (*(volatile uint32_t *)(I2C1_BASE + 0x04))
#define I2C1_DR (*(volatile uint32_t *)(I2C1_BASE + 0x10))
#define I2C1_SR1 (*(volatile uint32_t *)(I2C1_BASE + 0x14))
#define I2C1_SR2 (*(volatile uint32_t *)(I2C1_BASE + 0x18))
#define I2C1_CCR (*(volatile uint32_t *)(I2C1_BASE + 0x1C))
#define I2C1_TRISE (*(volatile uint32_t *)(I2C1_BASE + 0x20))

/* Delay function */
void delay_loop(volatile uint32_t cycles) {
  for (volatile uint32_t i = 0; i < cycles; i++);
}

/* Init I2C */
void i2c_init() {

  /* Turn on clocks for peripherals */

  /* Enable GPIOB */ 
  RCC_AHB1ENR |= (1 << 1); 
  
  /* Enable I2C1 */
  RCC_APB1ENR |= (1 << 21); 

  delay_loop(1000); 

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
  for (uint8_t i = 0; i < len; i++) {

    /* Wait for TxE (Transmit Buffer Empty) */
    while(!(I2C1_SR1 & (1 << 7)));  
    I2C1_DR = data[i];
    delay_loop(10);
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
  delay_loop(100);
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
  ssd1306_command(0x00);

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

/* Write data to screen */
void oled_write_data(uint8_t data) {

  /* Control byte followed by data byte */
  uint8_t data_packet[2] = {0x40, data};  
  i2c_write(0x3D, data_packet, 2);
  delay_loop(10);
}

/* Fill the entire screen with a specific pattern */
void fill_screen(uint8_t pattern) {

  /* Loop through each page (8 pages total) */
  for (uint8_t page = 0; page < 8; page++) {

    /* Set the current page address */
    ssd1306_command(0xB0 + page);

    /* Set the lower column address (0x00) */
    ssd1306_command(0x00);

    /* Set the higher column address (0x10) */
    ssd1306_command(0x10);

    /* Loop through each column (128 columns total) */
    for (uint16_t col = 0; col < 128; col++) {

      /* Write the pattern to the current column */
      oled_write_data(pattern);
    }
  }
}

int main() {

  /* Delay to allow reliable startup */
  delay_loop(1000000);

  i2c_init();

  oled_init();
 
  /* Clear the display; turn off while clearing to avoid pixel flashing */
  ssd1306_command(0xAE);
  fill_screen(0x00);
  ssd1306_command(0xAF);

  /* Draw data */
  oled_write_data(0xFF);

  /* Program finish */
  led_on_off(1);

  while(1) {
    
    /* Add conditions */
  }

  return 0;
}
