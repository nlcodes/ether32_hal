# Compiler and assembler
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as

# Compiler flags
CFLAGS = -mcpu=cortex-m4 -mthumb -Os -Istm32_hal/hal

# Linker flags
LDFLAGS = -Tlink.ld -nostartfiles

# Source files
SRCS = main.c \
       startup.s \
       stm32_hal/hal/hal_oled.c \
       stm32_hal/drivers/adafruit_stemma_qt_ssd1306/oled.c \
       stm32_hal/hal/hal_status_led.c \
       stm32_hal/drivers/led/led_on_off/led_on_off.c \
       stm32_hal/drivers/led/led_blink/led_blink.c \

# Object files (automatically generated from SRCS)
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)

# Output binary
TARGET = test.elf

# Default target
all: $(TARGET)

# Link the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Compile .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble .s files
%.o: %.s
	$(AS) -mcpu=cortex-m4 -mthumb -o $@ $<

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
