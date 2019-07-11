#include "stm32f10x_it.h"
#include "wifi/bsp_uart.h"
#include "wifi/esp8266.h"

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

void UART1_IRQHandler(void)
{
    
}

void UART2_IRQHandler(void)
{
    uint8_t ucCh;
    if (USART_GetITStatus(UART2, USART_IT_RXNE) != RESET)
    {
        ucCh = USART_ReceiveData(UART2);
        if(wifi1_frame_record.InfBit.FramLength < (RX_BUF_MAX_LEN - 1))
            wifi1_frame_record.Data_RX_BUF[wifi1_frame_record.InfBit.FramLength++] = ucCh;
    }
    
    if (USART_GetITStatus(UART2, USART_IT_IDLE) == SET)
    {
        wifi1_frame_record.InfBit.FramFinishFlag = 1;
        ucCh = USART_ReceiveData(UART2);
    }
}

void UART3_IRQHandler(void)
{
    uint8_t ucCh;
    if (USART_GetITStatus(UART3, USART_IT_RXNE) != RESET)
    {
        ucCh = USART_ReceiveData(UART3);
        if(wifi2_frame_record.InfBit.FramLength < (RX_BUF_MAX_LEN - 1))
            wifi2_frame_record.Data_RX_BUF[wifi2_frame_record.InfBit.FramLength++] = ucCh;
    }
    
    if (USART_GetITStatus(UART3, USART_IT_IDLE) == SET)
    {
        wifi2_frame_record.InfBit.FramFinishFlag = 1;
        ucCh = USART_ReceiveData(UART3);
    }
}

void UART4_IRQHandler(void)
{
    uint8_t ucCh;
    if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {
        ucCh = USART_ReceiveData(UART4);
        if(wifi3_frame_record.InfBit.FramLength < (RX_BUF_MAX_LEN - 1))
            wifi3_frame_record.Data_RX_BUF[wifi3_frame_record.InfBit.FramLength++] = ucCh;
    }
    
    if (USART_GetITStatus(UART4, USART_IT_IDLE) == SET)
    {
        wifi3_frame_record.InfBit.FramFinishFlag = 1;
        ucCh = USART_ReceiveData(UART4);
    }
}


void UART5_IRQHandler(void)
{
    uint8_t ucCh;
    if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
    {
        ucCh = USART_ReceiveData(UART5);
        if(wifi4_frame_record.InfBit.FramLength < (RX_BUF_MAX_LEN - 1))
            wifi4_frame_record.Data_RX_BUF[wifi4_frame_record.InfBit.FramLength++] = ucCh;
    }
    
    if (USART_GetITStatus(UART5, USART_IT_IDLE) == SET)
    {
        printf("\n\n\n\n\nbus idle!\n");
        
        if (++wifi4_frame_record.idle_time == wifi4_frame_record.idle_need)
            wifi4_frame_record.InfBit.FramFinishFlag = 1;
        ucCh = USART_ReceiveData(UART5);
    }
}

