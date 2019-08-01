#include "stm32f10x_it.h"

static void delay_s(uint64_t time)
{
    for (; time > 0; time--);
}



extern tick_wait_queue tick_wait_record;

void SysTick_Handler(void)
{
    uint64_t i;
    uint64_t counted = 0;

    for (i = 0; i < MAX_TICK_WAIT_QUEUE_LEN; i++)
    {
        if (tick_wait_record.queue[i].exist)
        {
            tick_wait_record.queue[i].next_remain_time--;
            counted++;

            if (tick_wait_record.queue[i].next_remain_time == 0)
            {
                tick_wait_record.queue[i].next_remain_time =
                    tick_wait_record.queue[i].time;
                tick_wait_record.queue[i].reg_func(i,
                                                   tick_wait_record.queue[i].message);
            }
        }

        if (counted == tick_wait_record.reg_num)
            break;
    }
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

void UART1_IRQHandler(void)
{
}

void UART2_IRQHandler(void)
{
    if (USART_GetITStatus(UART2, USART_IT_RXNE) != RESET)
        wifi_interrupt_handler(UART2, &wifi1_frame_record);
}

void UART3_IRQHandler(void)
{
    if (USART_GetITStatus(UART3, USART_IT_RXNE) != RESET)
        wifi_interrupt_handler(UART3, &wifi2_frame_record);
}

void UART4_IRQHandler(void)
{
    if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
        wifi_interrupt_handler(UART4, &wifi3_frame_record);
}


void UART5_IRQHandler(void)
{
    if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
        wifi_interrupt_handler(UART5, &wifi4_frame_record);
}

extern uint8_t penter, pcancel, pup, pdown;

void KEY_ENTER_IRQHAND(void)
{
    delay_s(KEY_WAIT_TIME);

    if (EXTI_GetITStatus(KEY_ENTER_LINE) != RESET)
        penter = 1;

    EXTI_ClearITPendingBit(KEY_ENTER_LINE);
}

void KEY_CANCEL_IRQHAND(void)
{
    delay_s(KEY_WAIT_TIME);

    if (EXTI_GetITStatus(KEY_CANCEL_LINE) != RESET)
        pcancel = 1;

    EXTI_ClearITPendingBit(KEY_CANCEL_LINE);
}

void KEY_UP_IRQHAND(void)
{
    delay_s(KEY_WAIT_TIME);

    if (EXTI_GetITStatus(KEY_UP_LINE) != RESET)
        pup = 1;

    EXTI_ClearITPendingBit(KEY_UP_LINE);
}

void KEY_DOWN_IRQHAND(void)
{
    delay_s(KEY_WAIT_TIME);

    if (EXTI_GetITStatus(KEY_DOWN_LINE) != RESET)
        pdown = 1;

    EXTI_ClearITPendingBit(KEY_DOWN_LINE);
}



