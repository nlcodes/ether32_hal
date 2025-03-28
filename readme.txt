ether32_hal

About:
  A hal/drivers firmware library written in c 
  Designed and tested using stm32f411ce_8mflash blackpill microcontroller
  Drivers are written with modularity for
  programs using supported peripherals

  Named ether32_hal because the design philosophy of this 
  hardware abstraction layer aims to be like alchemical ether,
  in that the hal underlies and makes up all core aspects of
  the program it is used to build, and is as pure, minimal, 
  and essential as possible
  Only what is directly needed has been included in ether32 
  It aims to be simple, bloat free, and is designed to be 
  extensible and modifiable 
  The supported peripherals are simply the ones which I wanted 
  support for, as this library is primarily designed to be used in 
  my projects
  However, ether32_hal was designed with other users in mind
  You are free to use this hal in 
  non commercial projects (details below)
  While it is an open source project, if you would like to license 
  this library for commercial work please contact me (details below)

  Peripherals supported/tested include adafruit stemma qt 128x64 oled, 
  4x4 gpio button matrix, and stm32 blackpill test led

  This hal is designed to allow the programmer easy initialization and
  usage of these peripherals and mcu
  While only tested with the peripherals listed above, this hal is likely
  to work with similar mcu/peripherals possibly with 
  some minor adjustments required

Instructions:
  Place ether32_hal directory in master directory of 
  stm32 firmware project using the hal

  Include the path of the main hal file (hal.h) in 
  program to access all hal functions
  Path should be "ether32_hal/hal/hal.h"

  For documentation regarding specific hal functions, their purpose, 
  and how to implement them in an stm32: Read hal.txt 
  Reading of this documentation is essential to understand
  how to use the hal, and goes into great detail on the specifics 
  of how to go about using the hal in your programs 
  This document covers essential initialization steps as well as 
  how to use the hal functions to manipulate your mcu and peripherals 
  from a higher level of abstraction, and is
  located at "ether32_hal/hal.txt"

  If you would like help building your project using the hal,
  move the contents of make_utils directory into project master directory
  The contents of make_utils are build tools for 
  ether32_hal c code compilation on linux
  For more documentation on the contents of make_utils read make.txt
  located at "ether32_hal/make.txt"

LICENSE: 
  ether32_hal is open source code and may be used in any non commercial 
  projects, or looked over for education
  If the library is used in something being distrubuted, credits
  are required, and anyone using a modified version of this library in 
  commercial works must obtain a commercial license 
  This includes using the library in a modified form from a project 
  using and distributing the library for free 
  If you would like to use this library for free in non commercial works, 
  credits should include "ether32_hal by Nathan Lusk"
  If you are interested in obtaining a commercial license, send inquiries to 
  nlusk1234@gmail.com
