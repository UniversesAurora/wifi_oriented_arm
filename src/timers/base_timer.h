#ifndef __BASE_TIMER_H
#define __BASE_TIMER_H

#include <stm32f10x.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_rcc.h>

#define            BASIC_TIM1                   TIM6
#define            BASIC_TIM1_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            BASIC_TIM1_CLK               RCC_APB1Periph_TIM6
#define            BASIC_TIM1_Prescaler         71
#define            BASIC_TIM1_IRQ               TIM6_IRQn
#define            BASIC_TIM1_IRQHandler        TIM6_IRQHandler


#define            BASIC_TIM2                   TIM7
#define            BASIC_TIM2_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            BASIC_TIM2_CLK               RCC_APB1Periph_TIM7
#define            BASIC_TIM2_Prescaler         71
#define            BASIC_TIM2_IRQ               TIM7_IRQn
#define            BASIC_TIM2_IRQHandler        TIM7_IRQHandler


void base_timer_1_init(void);
void base_timer_2_init(void);
void delay_base_timer_1_us(uint64_t us);
void delay_base_timer_1_ms(uint64_t ms);
void delay_base_timer_2_us(uint64_t us);
void delay_base_timer_2_ms(uint64_t ms);

#endif

