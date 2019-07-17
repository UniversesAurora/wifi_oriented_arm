#ifndef __LCD_DISPLAY_H
#define __LCD_DISPLAY_H

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

#define LCD_DIS_RCC RCC_APB2Periph_GPIOE
#define LCD_DIS_PORT GPIOE

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



void init_lcd_display(void);
uint8_t read_status_byte(void);
uint8_t read_data_byte(void);
void write_cmd_byte(uint8_t data);
void write_cmd_byte_no_wait(uint8_t data);
void write_data_byte(uint8_t data);
void lcd_print_line(char* string, int row, int col);


#endif

