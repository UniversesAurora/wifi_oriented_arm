#ifndef __LCD_DISPLAY_H
#define __LCD_DISPLAY_H

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LCD_DIS_RCC RCC_APB2Periph_GPIOF
#define LCD_DIS_PORT GPIOF

#define D0_PIN GPIO_Pin_0
#define D1_PIN GPIO_Pin_1
#define D2_PIN GPIO_Pin_2
#define D3_PIN GPIO_Pin_3
#define D4_PIN GPIO_Pin_4
#define D5_PIN GPIO_Pin_5
#define D6_PIN GPIO_Pin_6
#define D7_PIN GPIO_Pin_7
#define RS_PIN GPIO_Pin_8
#define RW_PIN GPIO_Pin_11
#define E_PIN  GPIO_Pin_12

#define BF_BIT 0b10000000

#define hrow_num 2
#define hcol_num 16

#define one_line_memsize 0x40
#define lcd_ddram_memsize_max 0x68

void init_lcd_display(void);
uint8_t read_status_byte(void);
uint8_t read_data_byte(void);
void write_cmd_byte(uint8_t data);
void write_cmd_byte_no_wait(uint8_t data);
void write_data_byte(uint8_t data);
void lcd_clear_screen(void);
void lcd_set_ddram_ptr(uint8_t addr);
void lcd_get_new_line(void);
char* lcd_get_string(int row, int col, int num);
void lcd_print_line(char* string, int row, int col);
void lcd_print_line_with_num(char* string, int row, int col,
                             int num);
void lcd_print(char* string, int row, int col);



#endif

