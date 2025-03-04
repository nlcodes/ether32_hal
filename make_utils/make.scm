; Build script for stm32_hal 
 
(shell-command 
  "make clean && make && \
   arm-none-eabi-objcopy -O binary test.elf test.bin && \
   st-flash write test.bin 0x8000000")
