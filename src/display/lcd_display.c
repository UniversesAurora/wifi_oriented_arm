#include "lcd_display.h"

static void delay_s(uint64_t time)
{
    for (; time > 0; time--);
}

void init_lcd_display(void)
{
    GPIO_InitTypeDef gpio_init_type;
    RCC_APB2PeriphClockCmd(LCD_DIS_RCC, ENABLE);
    gpio_init_type.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_init_type.GPIO_Speed = GPIO_Speed_10MHz;
    gpio_init_type.GPIO_Pin =  RS_PIN;
    GPIO_Init(LCD_DIS_PORT, &gpio_init_type);
    gpio_init_type.GPIO_Pin =  RW_PIN;
    GPIO_Init(LCD_DIS_PORT, &gpio_init_type);
    gpio_init_type.GPIO_Pin =  E_PIN;
    GPIO_Init(LCD_DIS_PORT, &gpio_init_type);
    write_cmd_byte_no_wait(0x38);
    delay_s(0x2FF);
    write_cmd_byte_no_wait(0x38);
    delay_s(0x2FF);
    write_cmd_byte_no_wait(0x38);
    delay_s(0x2FF);
    write_cmd_byte(0x38);
    write_cmd_byte(0x08);
    write_cmd_byte(0x01);
    write_cmd_byte(0x06);
    write_cmd_byte(0x0c);
}

static void set_data_pin_gpio(GPIO_InitTypeDef*
                              gpio_init_type)
{
    gpio_init_type->GPIO_Pin =  D0_PIN;
    GPIO_Init(LCD_DIS_PORT, gpio_init_type);
    gpio_init_type->GPIO_Pin =  D1_PIN;
    GPIO_Init(LCD_DIS_PORT, gpio_init_type);
    gpio_init_type->GPIO_Pin =  D2_PIN;
    GPIO_Init(LCD_DIS_PORT, gpio_init_type);
    gpio_init_type->GPIO_Pin =  D3_PIN;
    GPIO_Init(LCD_DIS_PORT, gpio_init_type);
    gpio_init_type->GPIO_Pin =  D4_PIN;
    GPIO_Init(LCD_DIS_PORT, gpio_init_type);
    gpio_init_type->GPIO_Pin =  D5_PIN;
    GPIO_Init(LCD_DIS_PORT, gpio_init_type);
    gpio_init_type->GPIO_Pin =  D6_PIN;
    GPIO_Init(LCD_DIS_PORT, gpio_init_type);
    gpio_init_type->GPIO_Pin =  D7_PIN;
    GPIO_Init(LCD_DIS_PORT, gpio_init_type);
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
    uint8_t data = (0xFF & GPIO_ReadInputData(LCD_DIS_PORT));
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
            GPIO_WriteBit(LCD_DIS_PORT, 1 << time, Bit_RESET);
            break;

        case 1:
            GPIO_WriteBit(LCD_DIS_PORT, 1 << time, Bit_SET);
            break;
        }

        data >>= 1;
    }
}

static void rs_set(void)
{
    GPIO_SetBits(LCD_DIS_PORT, RS_PIN);
}

static void rs_reset(void)
{
    GPIO_ResetBits(LCD_DIS_PORT, RS_PIN);
}

static void rw_set(void)
{
    GPIO_SetBits(LCD_DIS_PORT, RW_PIN);
}

static void rw_reset(void)
{
    GPIO_ResetBits(LCD_DIS_PORT, RW_PIN);
}

static void e_set(void)
{
    GPIO_SetBits(LCD_DIS_PORT, E_PIN);
}

static void e_reset(void)
{
    GPIO_ResetBits(LCD_DIS_PORT, E_PIN);
}

static void wait_bf(void)
{
    while (read_status_byte() & BF_BIT);
}


uint8_t read_status_byte(void)
{
    uint8_t data;
    rs_reset();
    rw_set();
    delay_s(0x10);
    e_set();
    delay_s(0x40);
    data = read_data();
    delay_s(0x10);
    e_reset();
    return data;
}

uint8_t read_data_byte(void)
{
    uint8_t data;
    wait_bf();
    rs_set();
    rw_set();
    delay_s(0x10);
    e_set();
    delay_s(0x40);
    data = read_data();
    delay_s(0x10);
    e_reset();
    return data;
}

void write_cmd_byte(uint8_t data)
{
    wait_bf();
    rs_reset();
    rw_reset();
    write_data(data);
    delay_s(0x30);
    e_set();
    delay_s(0x40);
    e_reset();
    delay_s(0x10);
}

void write_cmd_byte_no_wait(uint8_t data)
{
    rs_reset();
    rw_reset();
    write_data(data);
    delay_s(0x30);
    e_set();
    delay_s(0x40);
    e_reset();
    delay_s(0x10);
}

void write_data_byte(uint8_t data)
{
    wait_bf();
    rs_set();
    rw_reset();
    write_data(data);
    delay_s(0x30);
    e_set();
    delay_s(0x40);
    e_reset();
    delay_s(0x10);
}


void lcd_clear_screen(void)
{
    write_cmd_byte(1);
}

void lcd_set_ddram_ptr(uint8_t addr)
{
    if (addr > lcd_ddram_memsize_max - 1)
        return;

    addr |= 0b10000000;
    write_cmd_byte(addr);
}

void lcd_get_new_line(void)
{
    uint8_t addr_cur = read_status_byte();
    addr_cur &= ~BF_BIT;
    int cur_line = addr_cur / one_line_memsize;
    lcd_set_ddram_ptr(cur_line >= hrow_num - 1 ?
                      (hrow_num - 1) * one_line_memsize :
                      (cur_line + 1) * one_line_memsize);
}


char* lcd_get_string(int row, int col, int num)
{
    int read_count, line_count;
    uint8_t read_addr;
    char* str_buf;

    if (row < 0 || row >= hrow_num || col < 0
            || col >= hcol_num)
        return NULL;

    if (num < hrow_num * hcol_num)
        str_buf = malloc(num + 1);
    else
        str_buf = malloc(hrow_num * hcol_num + 1);

    if (!str_buf)
        return NULL;

    read_addr = row * one_line_memsize + col;
    line_count = col;
    lcd_set_ddram_ptr(read_addr);

    for (read_count = 0; read_count < num; read_count++)
    {
        str_buf[read_count] = read_data_byte();
        read_addr++;
        line_count++;

        if (line_count >= hcol_num)
        {
            if (read_addr >= one_line_memsize * (hrow_num - 1) +
                    hcol_num)
                break;

            line_count = 0;
            read_addr += one_line_memsize - hcol_num;
            lcd_set_ddram_ptr(read_addr);
        }
    }

    str_buf[read_count] = '\0';
    return str_buf;
}


void lcd_print_line(char* string, int row, int col)
{
    int display_offset, display_num, i;

    if (!string)
        return;

    if (row < 0 || row >= hrow_num || col < 0
            || col >= hcol_num)
        return;

    display_offset = row * one_line_memsize + col;
    display_num = hcol_num - col;
    lcd_set_ddram_ptr(display_offset);

    for (i = 0; i < display_num; i++)
    {
        if (string[i] == '\0')
            break;

        write_data_byte(string[i]);
    }
}

void lcd_print_line_with_num(char* string, int row, int col,
                             int num)
{
    int need_clear_num = 0, i;
    size_t slen;

    if (!string)
        return;

    slen = strlen(string);

    if (row < 0 || row >= hrow_num || col < 0
            || col >= hcol_num)
        return;

    if (slen > num)
        string[num] = '\0';
    else
        need_clear_num = num - slen;

    lcd_print_line(string, row, col);

    for (i = 0; i < need_clear_num; i++)
        write_data_byte(' ');
}

void lcd_print(char* string, int row, int col)
{
    int row_iter, print_count = 0;
    size_t slen;

    if (!string)
        return;

    if (row < 0 || row >= hrow_num || col < 0
            || col >= hcol_num)
        return;

    slen = strlen(string);

    for (row_iter = row; row_iter < hrow_num; row_iter++)
    {
        if (row_iter == row)
        {
            lcd_print_line(string, row, col);
            print_count += hcol_num - col;
            string += hcol_num - col;
        }
        else
        {
            lcd_print_line(string, row_iter, 0);
            print_count += hcol_num;
            string += hcol_num;
        }

        if (print_count >= slen)
            break;
    }
}




