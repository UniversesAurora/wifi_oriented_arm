#include "led_display.h"

static void delay_s(uint64_t time)
{
    for (; time > 0; time--);
}

void init_led_display(void)
{
    GPIO_InitTypeDef gpio_init_type;

    RCC_APB2PeriphClockCmd(LED_DIS_RCC, ENABLE);

    gpio_init_type.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_init_type.GPIO_Speed = GPIO_Speed_10MHz;

    gpio_init_type.GPIO_Pin =  RS_PIN;
    GPIO_Init(LED_DIS_PORT, &gpio_init_type);
    gpio_init_type.GPIO_Pin =  RW_PIN;
    GPIO_Init(LED_DIS_PORT, &gpio_init_type);
    gpio_init_type.GPIO_Pin =  E_PIN;
    GPIO_Init(LED_DIS_PORT, &gpio_init_type);

    write_cmd_byte_no_wait(0x38);
    delay_s(0x2FF);
    write_cmd_byte_no_wait(0x38);
    delay_s(0x2FF);
    write_cmd_byte_no_wait(0x38);
    delay_s(0x2FF);
}

static void set_data_pin_gpio(GPIO_InitTypeDef*
                              gpio_init_type)
{
    gpio_init_type->GPIO_Pin =  D0_PIN;
    GPIO_Init(LED_DIS_PORT, gpio_init_type);
    gpio_init_type->GPIO_Pin =  D1_PIN;
    GPIO_Init(LED_DIS_PORT, gpio_init_type);
    gpio_init_type->GPIO_Pin =  D2_PIN;
    GPIO_Init(LED_DIS_PORT, gpio_init_type);
    gpio_init_type->GPIO_Pin =  D3_PIN;
    GPIO_Init(LED_DIS_PORT, gpio_init_type);
    gpio_init_type->GPIO_Pin =  D4_PIN;
    GPIO_Init(LED_DIS_PORT, gpio_init_type);
    gpio_init_type->GPIO_Pin =  D5_PIN;
    GPIO_Init(LED_DIS_PORT, gpio_init_type);
    gpio_init_type->GPIO_Pin =  D6_PIN;
    GPIO_Init(LED_DIS_PORT, gpio_init_type);
    gpio_init_type->GPIO_Pin =  D7_PIN;
    GPIO_Init(LED_DIS_PORT, gpio_init_type);
}

static void start_read_data(void)
{
    GPIO_InitTypeDef gpio_init_type;
    gpio_init_type.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    set_data_pin_gpio(&gpio_init_type);
}

static void start_write_data(void)
{
    GPIO_InitTypeDef gpio_init_type;
    gpio_init_type.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_init_type.GPIO_Speed = GPIO_Speed_10MHz;
    set_data_pin_gpio(&gpio_init_type);
}

static uint8_t read_data(void)
{
    start_read_data();
    uint8_t data = (0xFF & GPIO_ReadInputData(LED_DIS_PORT));
    return data;
}

static void write_data(uint8_t data)
{
    start_write_data();
    int time = 0;

    for (; time < 8; time++)
    {
        switch (data & 1)
        {
        case 0:
            GPIO_WriteBit(LED_DIS_PORT, 1 << time, Bit_RESET);
            break;

        case 1:
            GPIO_WriteBit(LED_DIS_PORT, 1 << time, Bit_SET);
            break;
        }

        data >>= 1;
    }
}

static void rs_set(void)
{
    GPIO_SetBits(LED_DIS_PORT, RS_PIN);
}

static void rs_reset(void)
{
    GPIO_ResetBits(LED_DIS_PORT, RS_PIN);
}

static void rw_set(void)
{
    GPIO_SetBits(LED_DIS_PORT, RW_PIN);
}

static void rw_reset(void)
{
    GPIO_ResetBits(LED_DIS_PORT, RW_PIN);
}

static void e_set(void)
{
    GPIO_SetBits(LED_DIS_PORT, E_PIN);
}

static void e_reset(void)
{
    GPIO_ResetBits(LED_DIS_PORT, E_PIN);
}

void wait_bf(void)
{
    while (read_status_byte() & BF_BIT);
}


uint8_t read_status_byte(void)
{
    uint8_t data;

    rs_reset();
    rw_set();
    delay_s(0x1F);
    e_set();
    delay_s(0x5F);
    data = read_data();
    delay_s(0x1F);
    e_reset();

    return data;
}

uint8_t read_data_byte(void)
{
    uint8_t data;

    wait_bf();

    rs_set();
    rw_set();
    delay_s(0x1F);
    e_set();
    delay_s(0x5F);
    data = read_data();
    delay_s(0x1F);
    e_reset();

    return data;
}

void write_cmd_byte(uint8_t data)
{
    wait_bf();
    rs_reset();
    rw_reset();
    write_data(data);
    delay_s(0x3F);
    e_set();
    delay_s(0x5F);
    e_reset();
    delay_s(0x1F);
}

void write_cmd_byte_no_wait(uint8_t data)
{
    rs_reset();
    rw_reset();
    write_data(data);
    delay_s(0x3F);
    e_set();
    delay_s(0x5F);
    e_reset();
    delay_s(0x1F);
}

void write_data_byte(uint8_t data)
{
    wait_bf();
    rs_set();
    rw_reset();
    write_data(data);
    delay_s(0x3F);
    e_set();
    delay_s(0x5F);
    e_reset();
    delay_s(0x1F);
}

