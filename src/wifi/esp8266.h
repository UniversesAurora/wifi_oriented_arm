#ifndef __ESP8266_H
#define __ESP8266_H

#include "bsp_uart.h"

#define      WIFI_1_UART                                  UART2
#define      WIFI_2_UART                                  UART3
#define      WIFI_3_UART                                  UART4
#define      WIFI_4_UART                                  UART5

#define      WIFI_1_UART_INIT                             uart2_init
#define      WIFI_2_UART_INIT                             uart3_init
#define      WIFI_3_UART_INIT                             uart4_init
#define      WIFI_4_UART_INIT                             uart5_init


#define      WIFI_1_CH_PD_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define      WIFI_1_CH_PD_CLK                             RCC_APB2Periph_GPIOE
#define      WIFI_1_CH_PD_PORT                            GPIOE
#define      WIFI_1_CH_PD_PIN                             GPIO_Pin_9

#define      WIFI_1_RST_APBxClock_FUN                     RCC_APB2PeriphClockCmd
#define      WIFI_1_RST_CLK                               RCC_APB2Periph_GPIOE
#define      WIFI_1_RST_PORT                              GPIOE
#define      WIFI_1_RST_PIN                               GPIO_Pin_10


/*=========================================================================================*/


#define      WIFI_2_CH_PD_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define      WIFI_2_CH_PD_CLK                             RCC_APB2Periph_GPIOE
#define      WIFI_2_CH_PD_PORT                            GPIOE
#define      WIFI_2_CH_PD_PIN                             GPIO_Pin_13

#define      WIFI_2_RST_APBxClock_FUN                     RCC_APB2PeriphClockCmd
#define      WIFI_2_RST_CLK                               RCC_APB2Periph_GPIOE
#define      WIFI_2_RST_PORT                              GPIOE
#define      WIFI_2_RST_PIN                               GPIO_Pin_14


/*=========================================================================================*/


#define      WIFI_3_CH_PD_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define      WIFI_3_CH_PD_CLK                             RCC_APB2Periph_GPIOF
#define      WIFI_3_CH_PD_PORT                            GPIOF
#define      WIFI_3_CH_PD_PIN                             GPIO_Pin_0

#define      WIFI_3_RST_APBxClock_FUN                     RCC_APB2PeriphClockCmd
#define      WIFI_3_RST_CLK                               RCC_APB2Periph_GPIOF
#define      WIFI_3_RST_PORT                              GPIOF
#define      WIFI_3_RST_PIN                               GPIO_Pin_1


/*=========================================================================================*/


#define      WIFI_4_CH_PD_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define      WIFI_4_CH_PD_CLK                             RCC_APB2Periph_GPIOF
#define      WIFI_4_CH_PD_PORT                            GPIOF
#define      WIFI_4_CH_PD_PIN                             GPIO_Pin_2

#define      WIFI_4_RST_APBxClock_FUN                     RCC_APB2PeriphClockCmd
#define      WIFI_4_RST_CLK                               RCC_APB2Periph_GPIOF
#define      WIFI_4_RST_PORT                              GPIOF
#define      WIFI_4_RST_PIN                               GPIO_Pin_3

//#define INIT_WIFI_EN_RST(num) init_wifi_##num##_en_rst

#define     WIFI_1_EN_ENABLE()                 GPIO_SetBits (WIFI_1_CH_PD_PORT, WIFI_1_CH_PD_PIN)
#define     WIFI_1_EN_DISABLE()                GPIO_ResetBits (WIFI_1_CH_PD_PORT, WIFI_1_CH_PD_PIN)

#define     WIFI_1_RST_HIGH_LEVEL()            GPIO_SetBits (WIFI_1_RST_PORT, WIFI_1_RST_PIN)
#define     WIFI_1_RST_LOW_LEVEL()             GPIO_ResetBits (WIFI_1_RST_PORT, WIFI_1_RST_PIN)

#define     WIFI_2_EN_ENABLE()                 GPIO_SetBits (WIFI_2_CH_PD_PORT, WIFI_2_CH_PD_PIN)
#define     WIFI_2_EN_DISABLE()                GPIO_ResetBits (WIFI_2_CH_PD_PORT, WIFI_2_CH_PD_PIN)

#define     WIFI_2_RST_HIGH_LEVEL()            GPIO_SetBits (WIFI_2_RST_PORT, WIFI_2_RST_PIN)
#define     WIFI_2_RST_LOW_LEVEL()             GPIO_ResetBits (WIFI_2_RST_PORT, WIFI_2_RST_PIN)

#define     WIFI_3_EN_ENABLE()                 GPIO_SetBits (WIFI_3_CH_PD_PORT, WIFI_3_CH_PD_PIN)
#define     WIFI_3_EN_DISABLE()                GPIO_ResetBits (WIFI_3_CH_PD_PORT, WIFI_3_CH_PD_PIN)

#define     WIFI_3_RST_HIGH_LEVEL()            GPIO_SetBits (WIFI_3_RST_PORT, WIFI_3_RST_PIN)
#define     WIFI_3_RST_LOW_LEVEL()             GPIO_ResetBits (WIFI_3_RST_PORT, WIFI_3_RST_PIN)

#define     WIFI_4_EN_ENABLE()                 GPIO_SetBits (WIFI_4_CH_PD_PORT, WIFI_4_CH_PD_PIN)
#define     WIFI_4_EN_DISABLE()                GPIO_ResetBits (WIFI_4_CH_PD_PORT, WIFI_4_CH_PD_PIN)

#define     WIFI_4_RST_HIGH_LEVEL()            GPIO_SetBits (WIFI_4_RST_PORT, WIFI_4_RST_PIN)
#define     WIFI_4_RST_LOW_LEVEL()             GPIO_ResetBits (WIFI_4_RST_PORT, WIFI_4_RST_PIN)

#define     RX_BUF_MAX_LEN                     2048


typedef enum
{
    WIFI_1,
    WIFI_2,
    WIFI_3,
    WIFI_4,
}
wifi_t;

typedef struct
{
    char Data_RX_BUF [RX_BUF_MAX_LEN];

    union
    {
        __IO u16 InfAll;
        struct
        {
            __IO u16 FramLength       : 15;
            __IO u16 FramFinishFlag   : 1;
        } InfBit;
    };
}
wifi_frame_record;

extern wifi_frame_record  wifi1_frame_record, wifi2_frame_record, wifi3_frame_record, wifi4_frame_record;


#endif

