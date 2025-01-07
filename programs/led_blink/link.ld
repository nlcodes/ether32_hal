MEMORY {
  FLASH : ORIGIN = 0x08000000, LENGTH = 512k
  RAM : ORIGIN = 0x20000000, LENGTH = 128k
}

SECTIONS {
  .text : { *(.vectors) *(.text*) } > FLASH
  .rodata : { *(.rodata*) } > FLASH
  .data : { *(.data*) } > RAM AT > FLASH
  .bss : { *(.bss*) } > RAM
}
