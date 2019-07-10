#include "stm32f10x_it.h"

extern volatile uint64_t systick_int_times;

void SysTick_Handler(void)
{
    systick_int_times--;
}

extern volatile uint64_t basic_tim1_int_times;

void BASIC_TIM1_IRQHandler(void)
{
    if (TIM_GetITStatus(BASIC_TIM1, TIM_IT_Update) != RESET)
    {
        basic_tim1_int_times--;
        TIM_ClearITPendingBit(BASIC_TIM1, TIM_FLAG_Update);
    }
}


extern volatile uint64_t basic_tim2_int_times;

void BASIC_TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(BASIC_TIM2, TIM_IT_Update) != RESET)
    {
        basic_tim2_int_times--;
        TIM_ClearITPendingBit(BASIC_TIM2, TIM_FLAG_Update);
    }
}

