.syntax unified
.cpu cortex-m4
.thumb

@ Vector table
.section .vectors 

@ Initial stack pointer
.word 0x20005000       

@ Reset handler
.word reset_handler    

@ NMI handler
.word NMI_Handler      

@ Hard fault handler
.word HardFault_Handler 

@ Memory management fault
.word MemManage_Handler 

@ Bus fault
.word BusFault_Handler  

@ Usage fault
.word UsageFault_Handler 

@ Reserved
.word 0                

@ Reserved
.word 0                

@ Reserved
.word 0                

@ Reserved
.word 0                

@ SVCall
.word SVC_Handler      

@ Debug monitor
.word DebugMon_Handler 

@ Reserved
.word 0                

@ PendSV
.word PendSV_Handler   

@ SysTick
.word SysTick_Handler  


@ External interrupts; stm32f411

@ 0: Window Watchdog
.word WWDG_IRQHandler         

@ 1: PVD through EXTI Line detect
.word PVD_IRQHandler          

@ 2: Tamper and TimeStamp
.word TAMP_STAMP_IRQHandler   

@ 3: RTC Wakeup
.word RTC_WKUP_IRQHandler     

@ 4: Flash
.word FLASH_IRQHandler        

@ 5: RCC
.word RCC_IRQHandler          

@ 6: EXTI Line 0
.word EXTI0_IRQHandler        

@ 7: EXTI Line 1
.word EXTI1_IRQHandler        

@ 8: EXTI Line 2
.word EXTI2_IRQHandler        

@ 9: EXTI Line 3
.word EXTI3_IRQHandler        

@ 10: EXTI Line 4
.word EXTI4_IRQHandler        

@ 11: DMA1 Stream 0
.word DMA1_Stream0_IRQHandler 

@ 12: DMA1 Stream 1
.word DMA1_Stream1_IRQHandler 

@ 13: DMA1 Stream 2
.word DMA1_Stream2_IRQHandler 

@ 14: DMA1 Stream 3
.word DMA1_Stream3_IRQHandler 

@ 15: DMA1 Stream 4
.word DMA1_Stream4_IRQHandler 

@ 16: DMA1 Stream 5
.word DMA1_Stream5_IRQHandler 

@ 17: DMA1 Stream 6
.word DMA1_Stream6_IRQHandler 

@ 18: ADC1
.word ADC_IRQHandler          

@ 19: Reserved
.word 0                       

@ 20: Reserved
.word 0                       

@ 21: Reserved
.word 0                       

@ 22: Reserved
.word 0                       

@ 23: EXTI Line 9..5
.word EXTI9_5_IRQHandler      

@ 24: TIM1 Break and TIM9
.word TIM1_BRK_TIM9_IRQHandler 

@ 25: TIM1 Update and TIM10
.word TIM1_UP_TIM10_IRQHandler 

@ 26: TIM1 Trigger and Commutation and TIM11
.word TIM1_TRG_COM_TIM11_IRQHandler 

@ 27: TIM1 Capture Compare
.word TIM1_CC_IRQHandler      

@ 28: TIM2
.word TIM2_IRQHandler         

.section .text

@ Default handlers; all must be defined
.thumb_func
.weak NMI_Handler
NMI_Handler:
    b NMI_Handler

.thumb_func
.weak HardFault_Handler
HardFault_Handler:
    b HardFault_Handler

.thumb_func
.weak MemManage_Handler
MemManage_Handler:
    b MemManage_Handler

.thumb_func
.weak BusFault_Handler
BusFault_Handler:
    b BusFault_Handler

.thumb_func
.weak UsageFault_Handler
UsageFault_Handler:
    b UsageFault_Handler

.thumb_func
.weak SVC_Handler
SVC_Handler:
    bx lr

.thumb_func
.weak DebugMon_Handler
DebugMon_Handler:
    bx lr

.thumb_func
.weak PendSV_Handler
PendSV_Handler:
    bx lr

.thumb_func
.weak SysTick_Handler
SysTick_Handler:
    bx lr

@ Define handler macro
.macro def_irq_handler name
.weak \name
.thumb_set \name, Default_Handler
.endm

.thumb_func
Default_Handler:
    b Default_Handler

@ Generate all peripheral handlers as weak
def_irq_handler WWDG_IRQHandler
def_irq_handler PVD_IRQHandler
def_irq_handler TAMP_STAMP_IRQHandler
def_irq_handler RTC_WKUP_IRQHandler
def_irq_handler FLASH_IRQHandler
def_irq_handler RCC_IRQHandler
def_irq_handler EXTI0_IRQHandler
def_irq_handler EXTI1_IRQHandler
def_irq_handler EXTI2_IRQHandler
def_irq_handler EXTI3_IRQHandler
def_irq_handler EXTI4_IRQHandler
def_irq_handler DMA1_Stream0_IRQHandler
def_irq_handler DMA1_Stream1_IRQHandler
def_irq_handler DMA1_Stream2_IRQHandler
def_irq_handler DMA1_Stream3_IRQHandler
def_irq_handler DMA1_Stream4_IRQHandler
def_irq_handler DMA1_Stream5_IRQHandler
def_irq_handler DMA1_Stream6_IRQHandler
def_irq_handler ADC_IRQHandler
def_irq_handler EXTI9_5_IRQHandler
def_irq_handler TIM1_BRK_TIM9_IRQHandler
def_irq_handler TIM1_UP_TIM10_IRQHandler
def_irq_handler TIM1_TRG_COM_TIM11_IRQHandler
def_irq_handler TIM1_CC_IRQHandler
@ Not defining TIM2_IRQHandler as weak since we use it in c program

@ Program start
.thumb_func 
reset_handler:
  @ Branch and link to main
  bl main
