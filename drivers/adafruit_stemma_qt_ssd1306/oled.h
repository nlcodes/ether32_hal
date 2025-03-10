#ifndef OLED_H
#define OLED_H

#include "../globals.h"

/* Key register */
#define I2C1_BASE 0x40005400

/* I2C1 peripheral registers */
#define I2C1_CR1 (*(volatile uint32_t *)(I2C1_BASE + 0x00))
#define I2C1_CR2 (*(volatile uint32_t *)(I2C1_BASE + 0x04))
#define I2C1_DR (*(volatile uint32_t *)(I2C1_BASE + 0x10))
#define I2C1_SR1 (*(volatile uint32_t *)(I2C1_BASE + 0x14))
#define I2C1_SR2 (*(volatile uint32_t *)(I2C1_BASE + 0x18))
#define I2C1_CCR (*(volatile uint32_t *)(I2C1_BASE + 0x1C))
#define I2C1_TRISE (*(volatile uint32_t *)(I2C1_BASE + 0x20))

void i2c_init();
void i2c_write(uint8_t address, uint8_t *data, uint8_t len);
void ssd1306_command(uint8_t command);
void oled_init();
void display_write_bitmap(uint8_t *bitmap_data);

/* Main init and write functions */
void display_write(uint8_t *data, uint8_t page, uint8_t col, uint8_t width, uint8_t height);
void display_fill(uint8_t data);
void display_init();

#endif
