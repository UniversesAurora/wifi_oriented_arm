#include "esp8266.h"

wifi_frame_record  wifi1_frame_record, wifi2_frame_record, wifi3_frame_record, wifi4_frame_record;

static void init_wifi_en_rst(void (*en_fun)(uint32_t,
                             FunctionalState), void (*rst_fun)(uint32_t,
                                     FunctionalState), uint32_t en_clk, uint32_t rst_clk,
                             GPIO_TypeDef* en_port, GPIO_TypeDef* rst_port,
                             uint16_t en_pin, uint16_t rst_pin)
{
    GPIO_InitTypeDef gpio_init_type;

    en_fun(en_clk, ENABLE);
    gpio_init_type.GPIO_Pin = en_pin;
    gpio_init_type.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_init_type.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(en_port, &gpio_init_type);

    rst_fun(rst_clk, ENABLE);
    gpio_init_type.GPIO_Pin = rst_pin;
    GPIO_Init(rst_port, &gpio_init_type);
}

static void init_wifi_1_en_rst()
{
    init_wifi_en_rst(WIFI_1_CH_PD_APBxClock_FUN,
                     WIFI_1_RST_APBxClock_FUN, WIFI_1_CH_PD_CLK, WIFI_1_RST_CLK,
                     WIFI_1_CH_PD_PORT, WIFI_1_RST_PORT, WIFI_1_CH_PD_PIN,
                     WIFI_1_RST_PIN);
}

static void init_wifi_2_en_rst()
{
    init_wifi_en_rst(WIFI_2_CH_PD_APBxClock_FUN,
                     WIFI_2_RST_APBxClock_FUN, WIFI_2_CH_PD_CLK, WIFI_2_RST_CLK,
                     WIFI_2_CH_PD_PORT, WIFI_2_RST_PORT, WIFI_2_CH_PD_PIN,
                     WIFI_2_RST_PIN);
}

static void init_wifi_3_en_rst()
{
    init_wifi_en_rst(WIFI_3_CH_PD_APBxClock_FUN,
                     WIFI_3_RST_APBxClock_FUN, WIFI_3_CH_PD_CLK, WIFI_3_RST_CLK,
                     WIFI_3_CH_PD_PORT, WIFI_3_RST_PORT, WIFI_3_CH_PD_PIN,
                     WIFI_3_RST_PIN);
}

static void init_wifi_4_en_rst()
{
    init_wifi_en_rst(WIFI_4_CH_PD_APBxClock_FUN,
                     WIFI_4_RST_APBxClock_FUN, WIFI_4_CH_PD_CLK, WIFI_4_RST_CLK,
                     WIFI_4_CH_PD_PORT, WIFI_4_RST_PORT, WIFI_4_CH_PD_PIN,
                     WIFI_4_RST_PIN);
}


void wifi_init(wifi_t wifi)
{
    switch (wifi)
    {
    case WIFI_1:
        init_wifi_1_en_rst();
        WIFI_1_UART_INIT(115200, USART_WordLength_8b,
                         USART_StopBits_1, USART_Parity_No,
                         USART_Mode_Rx | USART_Mode_Tx,
                         USART_HardwareFlowControl_None);
        USART_ITConfig(WIFI_1_UART, USART_IT_IDLE, ENABLE);
        WIFI_1_RST_HIGH_LEVEL();
        WIFI_1_EN_DISABLE();
        break;

    case WIFI_2:
        init_wifi_2_en_rst();
        WIFI_2_UART_INIT(115200, USART_WordLength_8b,
                         USART_StopBits_1, USART_Parity_No,
                         USART_Mode_Rx | USART_Mode_Tx,
                         USART_HardwareFlowControl_None);
        USART_ITConfig(WIFI_2_UART, USART_IT_IDLE, ENABLE);
        WIFI_2_RST_HIGH_LEVEL();
        WIFI_2_EN_DISABLE();
        break;

    case WIFI_3:
        init_wifi_3_en_rst();
        WIFI_3_UART_INIT(115200, USART_WordLength_8b,
                         USART_StopBits_1, USART_Parity_No,
                         USART_Mode_Rx | USART_Mode_Tx,
                         USART_HardwareFlowControl_None);
        USART_ITConfig(WIFI_3_UART, USART_IT_IDLE, ENABLE);
        WIFI_3_RST_HIGH_LEVEL();
        WIFI_3_EN_DISABLE();
        break;

    case WIFI_4:
        init_wifi_4_en_rst();
        WIFI_4_UART_INIT(115200, USART_WordLength_8b,
                         USART_StopBits_1, USART_Parity_No,
                         USART_Mode_Rx | USART_Mode_Tx,
                         USART_HardwareFlowControl_None);
        USART_ITConfig(WIFI_4_UART, USART_IT_IDLE, ENABLE);
        WIFI_4_RST_HIGH_LEVEL();
        WIFI_4_EN_DISABLE();
        break;
    }
}
