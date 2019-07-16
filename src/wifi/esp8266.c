#include "esp8266.h"

wifi_frame_record  wifi1_frame_record, wifi2_frame_record,
                   wifi3_frame_record, wifi4_frame_record;


void init_wifi_power(void)
{
    GPIO_InitTypeDef gpio_init_type;

    WIFI_POWER_RST_APBxClock_FUN(WIFI_POWER_RST_CLK, ENABLE);
    gpio_init_type.GPIO_Pin = WIFI_POWER_RST_PIN;
    gpio_init_type.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_init_type.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(WIFI_POWER_RST_PORT, &gpio_init_type);
    wifi_power_cut();
    wifi_power_on();
}

void wifi_power_cut(void)
{
    GPIO_ResetBits(WIFI_POWER_RST_PORT, WIFI_POWER_RST_PIN);
}

void wifi_power_on(void)
{
    GPIO_SetBits(WIFI_POWER_RST_PORT, WIFI_POWER_RST_PIN);
}



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

static void init_wifi_1_en_rst(void)
{
    init_wifi_en_rst(WIFI_1_CH_PD_APBxClock_FUN,
                     WIFI_1_RST_APBxClock_FUN, WIFI_1_CH_PD_CLK, WIFI_1_RST_CLK,
                     WIFI_1_CH_PD_PORT, WIFI_1_RST_PORT, WIFI_1_CH_PD_PIN,
                     WIFI_1_RST_PIN);
}

static void init_wifi_2_en_rst(void)
{
    init_wifi_en_rst(WIFI_2_CH_PD_APBxClock_FUN,
                     WIFI_2_RST_APBxClock_FUN, WIFI_2_CH_PD_CLK, WIFI_2_RST_CLK,
                     WIFI_2_CH_PD_PORT, WIFI_2_RST_PORT, WIFI_2_CH_PD_PIN,
                     WIFI_2_RST_PIN);
}

static void init_wifi_3_en_rst(void)
{
    init_wifi_en_rst(WIFI_3_CH_PD_APBxClock_FUN,
                     WIFI_3_RST_APBxClock_FUN, WIFI_3_CH_PD_CLK, WIFI_3_RST_CLK,
                     WIFI_3_CH_PD_PORT, WIFI_3_RST_PORT, WIFI_3_CH_PD_PIN,
                     WIFI_3_RST_PIN);
}

static void init_wifi_4_en_rst(void)
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
        WIFI_1_RST_HIGH_LEVEL();
        WIFI_1_EN_ENABLE();
        break;

    case WIFI_2:
        init_wifi_2_en_rst();
        WIFI_2_UART_INIT(115200, USART_WordLength_8b,
                         USART_StopBits_1, USART_Parity_No,
                         USART_Mode_Rx | USART_Mode_Tx,
                         USART_HardwareFlowControl_None);
        WIFI_2_RST_HIGH_LEVEL();
        WIFI_2_EN_ENABLE();
        break;

    case WIFI_3:
        init_wifi_3_en_rst();
        WIFI_3_UART_INIT(115200, USART_WordLength_8b,
                         USART_StopBits_1, USART_Parity_No,
                         USART_Mode_Rx | USART_Mode_Tx,
                         USART_HardwareFlowControl_None);
        WIFI_3_RST_HIGH_LEVEL();
        WIFI_3_EN_ENABLE();
        break;

    case WIFI_4:
        init_wifi_4_en_rst();
        WIFI_4_UART_INIT(115200, USART_WordLength_8b,
                         USART_StopBits_1, USART_Parity_No,
                         USART_Mode_Rx | USART_Mode_Tx,
                         USART_HardwareFlowControl_None);
        WIFI_4_RST_HIGH_LEVEL();
        WIFI_4_EN_ENABLE();
        break;
    }
}

void wifi_reset(wifi_t wifi)
{
    switch (wifi)
    {
    case WIFI_1:
        WIFI_1_RST_LOW_LEVEL();
        systick_delay(500);
        WIFI_1_RST_HIGH_LEVEL();
        break;

    case WIFI_2:
        WIFI_2_RST_LOW_LEVEL();
        systick_delay(500);
        WIFI_2_RST_HIGH_LEVEL();
        break;

    case WIFI_3:
        WIFI_3_RST_LOW_LEVEL();
        systick_delay(500);
        WIFI_3_RST_HIGH_LEVEL();
        break;

    case WIFI_4:
        WIFI_4_RST_LOW_LEVEL();
        systick_delay(500);
        WIFI_4_RST_HIGH_LEVEL();
        break;
    }
}


static char* wifi_cmd(wifi_frame_record* record,
                      USART_TypeDef* uart, char* cmd, uint64_t timeout)
{
    uint8_t timeouted = 0;
    
    size_t cmd_len = strlen(cmd);
    char* to_send = malloc(cmd_len + 4);
    strcpy(to_send, cmd);
    strcat(to_send, "\r\n");
    record->InfBit.FramFinishFlag = 0;
    record->InfBit.FramLength = 0;

    debug_printf("send!\n");
    uart_send_string(uart, to_send);
    free(to_send);

    uint64_t reg_identifier = tick_reg(timeout, timeout_handler, &timeouted);
    while (!record->InfBit.FramFinishFlag && !timeouted);

    if (timeouted)
        debug_printf("timeout\n");
    else
    {
        tick_unreg(reg_identifier);
        debug_printf("ok\n");
    }

    record->Data_RX_BUF[record->InfBit.FramLength] = '\0';
    return record->Data_RX_BUF;
}

char* exec_wifi_cmd(wifi_t wifi, char* cmd, uint64_t timeout)
{
    switch (wifi)
    {
    case WIFI_1:
        return wifi_cmd(&wifi1_frame_record, WIFI_1_UART, cmd, timeout);

    case WIFI_2:
        return wifi_cmd(&wifi2_frame_record, WIFI_2_UART, cmd, timeout);

    case WIFI_3:
        return wifi_cmd(&wifi3_frame_record, WIFI_3_UART, cmd, timeout);

    case WIFI_4:
        return wifi_cmd(&wifi4_frame_record, WIFI_4_UART, cmd, timeout);
    }

    return NULL;
}


void exec_all_wifi_cmd(char* cmd, uint64_t timeout)
{
    uint8_t timeouted = 0;
    
    size_t cmd_len = strlen(cmd);
    char* to_send = malloc(cmd_len + 4);
    strcpy(to_send, cmd);
    strcat(to_send, "\r\n");
    wifi1_frame_record.InfBit.FramLength = 0;
    wifi2_frame_record.InfBit.FramLength = 0;
    wifi3_frame_record.InfBit.FramLength = 0;
    wifi4_frame_record.InfBit.FramLength = 0;
    wifi1_frame_record.InfBit.FramFinishFlag = 0;
    wifi2_frame_record.InfBit.FramFinishFlag = 0;
    wifi3_frame_record.InfBit.FramFinishFlag = 0;
    wifi4_frame_record.InfBit.FramFinishFlag = 0;

    debug_printf("send!\n");
    uart_send_string(WIFI_1_UART, to_send);
    uart_send_string(WIFI_2_UART, to_send);
    uart_send_string(WIFI_3_UART, to_send);
    uart_send_string(WIFI_4_UART, to_send);
    free(to_send);
    
    uint64_t reg_identifier = tick_reg(timeout, timeout_handler, &timeouted);

    while (!wifi1_frame_record.InfBit.FramFinishFlag && !timeouted);

    while (!wifi2_frame_record.InfBit.FramFinishFlag && !timeouted);

    while (!wifi3_frame_record.InfBit.FramFinishFlag && !timeouted);

    while (!wifi4_frame_record.InfBit.FramFinishFlag && !timeouted);

    if (timeouted)
        debug_printf("timeout\n");
    else
    {
        tick_unreg(reg_identifier);
        debug_printf("ok\n");
    }

    wifi1_frame_record.Data_RX_BUF[wifi1_frame_record.InfBit.FramLength]
        = '\0';
    wifi2_frame_record.Data_RX_BUF[wifi2_frame_record.InfBit.FramLength]
        = '\0';
    wifi3_frame_record.Data_RX_BUF[wifi3_frame_record.InfBit.FramLength]
        = '\0';
    wifi4_frame_record.Data_RX_BUF[wifi4_frame_record.InfBit.FramLength]
        = '\0';
    return;
}

void wait_at(wifi_t wifi)
{
    while (1)
    {
        char* ret = exec_wifi_cmd(wifi, "AT", 500);
        debug_printf("\n\n%s\n\n============\n", ret);

        if (strstr(ret, "OK"))
            return;

        //wifi_reset(wifi);
    }
}

void mode_set(wifi_t wifi)
{
    while (1)
    {
        if (strstr(exec_wifi_cmd(wifi, "AT+CWMODE=1", 500),
                   "OK"))
            return;
    }
}
