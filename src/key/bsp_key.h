#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_exti.h>
#include <misc.h>

/*============S1=============*/

#define KEY_ENTER_RCC RCC_APB2Periph_GPIOE
#define KEY_ENTER_Pin GPIO_Pin_4
#define KEY_ENTER_PORT GPIOE
#define KEY_ENTER_PORTS GPIO_PortSourceGPIOE
#define KEY_ENTER_PinS GPIO_PinSource4
#define KEY_ENTER_LINE EXTI_Line4
#define KEY_ENTER_TRIG EXTI_Trigger_Rising
#define KEY_ENTER_IRQC EXTI4_IRQn
#define KEY_ENTER_IRQHAND EXTI4_IRQHandler

/*============S2=============*/

#define KEY_CANCEL_RCC RCC_APB2Periph_GPIOE
#define KEY_CANCEL_Pin GPIO_Pin_3
#define KEY_CANCEL_PORT GPIOE
#define KEY_CANCEL_PORTS GPIO_PortSourceGPIOE
#define KEY_CANCEL_PinS GPIO_PinSource3
#define KEY_CANCEL_LINE EXTI_Line3
#define KEY_CANCEL_TRIG EXTI_Trigger_Rising
#define KEY_CANCEL_IRQC EXTI3_IRQn
#define KEY_CANCEL_IRQHAND EXTI3_IRQHandler

/*============S3=============*/

#define KEY_UP_RCC RCC_APB2Periph_GPIOE
#define KEY_UP_Pin GPIO_Pin_2
#define KEY_UP_PORT GPIOE
#define KEY_UP_PORTS GPIO_PortSourceGPIOE
#define KEY_UP_PinS GPIO_PinSource2
#define KEY_UP_LINE EXTI_Line2
#define KEY_UP_TRIG EXTI_Trigger_Rising
#define KEY_UP_IRQC EXTI2_IRQn
#define KEY_UP_IRQHAND EXTI2_IRQHandler

/*============S4=============*/

#define KEY_DOWN_RCC RCC_APB2Periph_GPIOA
#define KEY_DOWN_Pin GPIO_Pin_0
#define KEY_DOWN_PORT GPIOA
#define KEY_DOWN_PORTS GPIO_PortSourceGPIOA
#define KEY_DOWN_PinS GPIO_PinSource0
#define KEY_DOWN_LINE EXTI_Line0
#define KEY_DOWN_TRIG EXTI_Trigger_Falling
#define KEY_DOWN_IRQC EXTI0_IRQn
#define KEY_DOWN_IRQHAND EXTI0_IRQHandler

#define KEY_WAIT_TIME 0x220000

#define key_enter_open exti_config(KEY_ENTER_LINE, EXTI_Mode_Interrupt, KEY_ENTER_TRIG, ENABLE)
#define key_enter_close exti_config(KEY_ENTER_LINE, EXTI_Mode_Interrupt, KEY_ENTER_TRIG, DISABLE)

#define key_cancel_open exti_config(KEY_CANCEL_LINE, EXTI_Mode_Interrupt, KEY_CANCEL_TRIG, ENABLE)
#define key_cancel_close exti_config(KEY_CANCEL_LINE, EXTI_Mode_Interrupt, KEY_CANCEL_TRIG, DISABLE)

#define key_up_open exti_config(KEY_UP_LINE, EXTI_Mode_Interrupt, KEY_UP_TRIG, ENABLE)
#define key_up_close exti_config(KEY_UP_LINE, EXTI_Mode_Interrupt, KEY_UP_TRIG, DISABLE)

#define key_down_open exti_config(KEY_DOWN_LINE, EXTI_Mode_Interrupt, KEY_DOWN_TRIG, ENABLE)
#define key_down_close exti_config(KEY_DOWN_LINE, EXTI_Mode_Interrupt, KEY_DOWN_TRIG, DISABLE)



void exti_config(uint32_t line, EXTIMode_TypeDef mode,
                 EXTITrigger_TypeDef trigger, FunctionalState cmd);
void key_init(void);


#endif
