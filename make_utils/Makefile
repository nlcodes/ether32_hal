# Compiler and assembler
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as

# Compiler flags
CFLAGS = -mcpu=cortex-m4 -mthumb -Os -Iether32_hal/hal

# Linker flags
LDFLAGS = -Tlink.ld -nostartfiles

# Source files
SRCS = main.c \
       startup.s \
       ether32_hal/hal/hal_interrupts.c \
       ether32_hal/drivers/interrupts.c \
       ether32_hal/hal/hal_oled.c \
       ether32_hal/drivers/adafruit_stemma_qt_ssd1306/oled.c \
       ether32_hal/hal/hal_buttons.c \
       ether32_hal/drivers/4x4_button_matrix/buttons.c \
       ether32_hal/hal/hal_status_led.c \
       ether32_hal/drivers/led/led_on_off/led_on_off.c \
       ether32_hal/drivers/led/led_blink/led_blink.c \

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
