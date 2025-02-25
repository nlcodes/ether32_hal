.syntax unified
.cpu cortex-m4
.thumb

@ Vector table
.section .vectors 

@ Stack pointer address
.word 0x20005000 
.word reset_handler
.word fault_handler
.word fault_handler 

.section .text
.thumb_func 

@ Program start
reset_handler:

@ Branch and link to main 
  bl main 

fault_handler:
  b fault_handler
