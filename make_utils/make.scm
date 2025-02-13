; Build script for gambit scheme lisp on unix systems
; Works with swd
; Use with other make utils in stm32_hal after moving all make utils to master dir of project
; After installing gambit scheme, run with "gsi make.scm"
 
(shell-command 
  "make clean && make && \
   arm-none-eabi-objcopy -O binary test.elf test.bin && \
   st-flash write test.bin 0x8000000")
