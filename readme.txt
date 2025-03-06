stm32_hal

About:
  A hal/drivers firmware library written in c
  Designed and tested  using stm32f411ce_8mflash blackpill microcontroller
  Drivers are written with modularity for different programs using supported peripherals
  Peripherals supported/tested include adafruit stemma qt 128x64 oled, 
  4x4 gpio button matrix, and stm32 blackpill test led
  This hal is designed to allow the programmer easy initialization and
  usage of these peripherals and mcu
  While only tested with the peripherals listed above, this hal is likely
  to work with similar mcu/peripherals possibly with some minor adjustments required

Instructions:
  Place stm32_hal directory in master directory of stm32 firmware project using the hal
  Move the contents of make_utils directory inside stm32_hal into project master directory
  The contents of make_utils are build tools for stm32_hal c code compilation on linux
  For more documentation on the contents of make_utils read readme.txt
  located at "stm32_hal/make_utils/readme.txt"
  Include the path of the main hal file (hal.h) in program to access all hal functions
  Path should be "stm32_hal/hal/hal.h"
  For more documentation regarding specific hal functions, their purpose, and how to 
  implement them in an stm32 firmware project read readme.txt 
  located at "stm32_hal/hal/readme.txt"
