.syntax unified
.cpu cortex-m4
.thumb

@ Vector table
.section .vectors 
.word 0x20005000 @ Stack pointer address
.word reset_handler
.word fault_handler
.word fault_handler 

.section .text
.thumb_func 
reset_handler: @ Program start
  bl main @ Branch and link to main 

fault_handler:
  b fault_handler
