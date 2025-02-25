#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "globals.h"

/* Base memory addresses for interrupt control registers */

/* System config controller */
#define SYSCFG_BASE 0x40013800

/* External interrupt controller */
#define EXTI_BASE 0x40013C00


/* Timer 2 registers */

#define TIM2_BASE 0x40000000

/* Control register 1 */
#define TIM2_CR1 (*(volatile uint32_t *)(TIM2_BASE + 0x00))

/* Prescaler register; divides clock frequency */
#define TIM2_PSC (*(volatile uint32_t *)(TIM2_BASE + 0x28))

/* Auto reload register; sets frequency */
#define TIM2_ARR (*(volatile uint32_t *)(TIM2_BASE + 0x2C))

/* Status register; shows interrupt flags */
#define TIM2_SR (*(volatile uint32_t *)(TIM2_BASE + 0x10))

/* DMA interrupt enable register */
#define TIM2_DIER (*(volatile uint32_t *)(TIM2_BASE + 0x0C))

/* Event Generation Register*/
#define TIM2_EGR (*(volatile uint32_t *)(TIM2_BASE + 0x14))


/* Timer control bits */

/* Counter enable; starts and stops timer */
#define TIM_CR1_CEN 0x0001

/* Update interrupt enable; lets timer trigger interrupts */
#define TIM_DIER_UIE 0x0001

/* Update interrupt flag; shows when timer triggered */
#define TIM_SR_UIF 0x0001


/* NVIC registers
 * Enables interrupts in cpu
 */

#define NVIC_BASE 0xE000E100
#define NVIC_IPR_BASE 0xE000E400
#define NVIC_SetPriority(IRQn, priority) \
  (*(volatile uint8_t *)(NVIC_IPR_BASE + IRQn) = (priority << 4))
#define NVIC_ISER0 (*(volatile uint32_t *)(NVIC_BASE + 0x00))
#define NVIC_ISER1 (*(volatile uint32_t *)(NVIC_BASE + 0x04))


/* Interrupt number; tells NVIC which interrupt is which */

/* Timer two number */
#define TIM2_IRQn 28


/* Function for timer interrupt for button matrix */
void buttons_timer_init();

/* General delay interrupt function
 * TIM2_IRQHandler() defined in interrupts.c
 * Automatically called by hardware 
 * Does not need header file declaration
 */

/* Delay done signal for timer interrupt */
extern volatile uint8_t ir_delay_done;

#define PRIMASK (*((volatile uint32_t *)0xE000ED10))

static inline void __disable_irq() {
  PRIMASK = 1;
}

static inline void __enable_irq() {
  PRIMASK = 0;
}

#endif
