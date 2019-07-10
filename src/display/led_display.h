#ifndef __LED_DISPLAY_H
#define __LED_DISPLAY_H

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

#define LED_DIS_RCC RCC_APB2Periph_GPIOE
#define LED_DIS_PORT GPIOE

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

typedef enum
{
    A = 01000001,
    B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    a = 01000001,
    b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
}
charset;

void init_led_display(void);
uint8_t read_status_byte(void);
uint8_t read_data_byte(void);
void write_cmd_byte(uint8_t data);
void write_cmd_byte_no_wait(uint8_t data);
void write_data_byte(uint8_t data);


#endif

