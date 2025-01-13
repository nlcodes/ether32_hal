CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
CFLAGS = -mcpu=cortex-m4 -mthumb -Os
LDFLAGS = -Tlink.ld -nostartfiles

test: startup.o main.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o test.elf $^

startup.o: startup.s 
	$(AS) -mcpu=cortex-m4 -mthumb -o startup.o startup.s 

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c 

clean:
	rm -f *.o *.elf *.bin
