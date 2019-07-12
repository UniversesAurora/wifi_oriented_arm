#ifndef __BSP_UART_H
#define __BSP_UART_H

#include <stm32f10x.h>
#include <stm32f10x_usart.h>
#include <stdio.h>


#define  DEBUG_UART               USART1


#define  UART1                    USART1
#define  UART1_CLK                RCC_APB2Periph_USART1
#define  UART1_APBxClkCmd         RCC_APB2PeriphClockCmd

#define  UART1_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  UART1_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd

#define  UART1_TX_GPIO_PORT       GPIOA
#define  UART1_TX_GPIO_PIN        GPIO_Pin_9
#define  UART1_RX_GPIO_PORT       GPIOA
#define  UART1_RX_GPIO_PIN        GPIO_Pin_10

#define  UART1_IRQ                USART1_IRQn
#define  UART1_IRQHandler         USART1_IRQHandler


/*============================================================*/


#define  UART2                    USART2
#define  UART2_CLK                RCC_APB1Periph_USART2
#define  UART2_APBxClkCmd         RCC_APB1PeriphClockCmd

#define  UART2_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  UART2_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd

#define  UART2_TX_GPIO_PORT       GPIOA
#define  UART2_TX_GPIO_PIN        GPIO_Pin_2
#define  UART2_RX_GPIO_PORT       GPIOA
#define  UART2_RX_GPIO_PIN        GPIO_Pin_3

#define  UART2_IRQ                USART2_IRQn
#define  UART2_IRQHandler         USART2_IRQHandler


/*============================================================*/


#define  UART3                    USART3
#define  UART3_CLK                RCC_APB1Periph_USART3
#define  UART3_APBxClkCmd         RCC_APB1PeriphClockCmd

#define  UART3_GPIO_CLK           (RCC_APB2Periph_GPIOB)
#define  UART3_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd

#define  UART3_TX_GPIO_PORT       GPIOB
#define  UART3_TX_GPIO_PIN        GPIO_Pin_10
#define  UART3_RX_GPIO_PORT       GPIOB
#define  UART3_RX_GPIO_PIN        GPIO_Pin_11

#define  UART3_IRQ                USART3_IRQn
#define  UART3_IRQHandler         USART3_IRQHandler


/*============================================================*/


#define  UART4_CLK                RCC_APB1Periph_UART4
#define  UART4_APBxClkCmd         RCC_APB1PeriphClockCmd

#define  UART4_GPIO_CLK           (RCC_APB2Periph_GPIOC)
#define  UART4_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd

#define  UART4_TX_GPIO_PORT       GPIOC
#define  UART4_TX_GPIO_PIN        GPIO_Pin_10
#define  UART4_RX_GPIO_PORT       GPIOC
#define  UART4_RX_GPIO_PIN        GPIO_Pin_11

#define  UART4_IRQ                UART4_IRQn


/*============================================================*/


#define  UART5_CLK                RCC_APB1Periph_UART5
#define  UART5_APBxClkCmd         RCC_APB1PeriphClockCmd

#define  UART5_GPIO_CLK1          (RCC_APB2Periph_GPIOC)
#define  UART5_GPIO_CLK2          (RCC_APB2Periph_GPIOD)
#define  UART5_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd

#define  UART5_TX_GPIO_PORT       GPIOC
#define  UART5_TX_GPIO_PIN        GPIO_Pin_12
#define  UART5_RX_GPIO_PORT       GPIOD
#define  UART5_RX_GPIO_PIN        GPIO_Pin_2

#define  UART5_IRQ                UART5_IRQn


#ifdef DEBUG
#define debug_printf(fmt, ...)   printf(fmt, ##__VA_ARGS__)
#else
#define debug_printf(fmt, ...)
#endif


void uart1_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow);
void uart2_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow);
void uart3_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow);
void uart4_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow);
void uart5_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow);

void uart_send_string(USART_TypeDef* pUSARTx, char* str);



#endif

