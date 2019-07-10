#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H

#include <stm32f10x.h>
#include <core_cm3.h>


void delay_hard_us(uint64_t us);
void delay_hard_ms(uint64_t ms);
void delay_int_us(uint64_t us);
void delay_int_ms(uint64_t ms);

#endif

