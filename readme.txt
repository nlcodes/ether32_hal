stm32_hal

About:
  A hal/drivers firmware library written in c 
  Designed and tested using stm32f411ce_8mflash blackpill microcontroller
  Drivers are written with modularity for
  programs using supported peripherals

  Peripherals supported/tested include adafruit stemma qt 128x64 oled, 
  4x4 gpio button matrix, and stm32 blackpill test led

  This hal is designed to allow the programmer easy initialization and
  usage of these peripherals and mcu
  While only tested with the peripherals listed above, this hal is likely
  to work with similar mcu/peripherals possibly with 
  some minor adjustments required

Instructions:
  Place stm32_hal directory in master directory of 
  stm32 firmware project using the hal

  Include the path of the main hal file (hal.h) in 
  program to access all hal functions
  Path should be "stm32_hal/hal/hal.h"

  For documentation regarding specific hal functions, their purpose, 
  and how to implement them in an stm32: Read hal.txt 
  Reading of this documentation is essential to understand
  how to use the hal, and goes into great detail on the specifics 
  of how to go about using the hal in your programs 
  This document covers essential initialization steps as well as 
  how to use the hal functions to manipulate your mcu and peripherals 
  from a higher level of abstraction, and is
  located at "stm32_hal/hal.txt"

  If you would like help building your project using the hal,
  move the contents of make_utils directory into project master directory
  The contents of make_utils are build tools for 
  stm32_hal c code compilation on linux
  For more documentation on the contents of make_utils read make.txt
  located at "stm32_hal/make.txt"
