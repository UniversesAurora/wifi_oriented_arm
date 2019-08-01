#include "bsp_key.h"

static void init_nvic(uint8_t IRQChannel,
                      uint8_t PreemptionPriority, uint8_t SubPriority)
{
    NVIC_InitTypeDef nvic_init_type;
    nvic_init_type.NVIC_IRQChannel = IRQChannel;
    nvic_init_type.NVIC_IRQChannelPreemptionPriority =
        PreemptionPriority;
    nvic_init_type.NVIC_IRQChannelSubPriority = SubPriority;
    nvic_init_type.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init_type);
}

static void init_exti(GPIO_TypeDef* port, uint16_t pin,
                      GPIOMode_TypeDef mode, uint8_t ports, uint8_t pins)
{
    GPIO_InitTypeDef gpio_init_type;
    gpio_init_type.GPIO_Pin =  pin;
    gpio_init_type.GPIO_Mode = mode;
    GPIO_Init(port, &gpio_init_type);
    GPIO_EXTILineConfig(ports, pins);
}

void exti_config(uint32_t line, EXTIMode_TypeDef mode,
                 EXTITrigger_TypeDef trigger, FunctionalState cmd)
{
    EXTI_InitTypeDef exti_init_type;
    exti_init_type.EXTI_Line = line;
    exti_init_type.EXTI_Mode = mode;
    exti_init_type.EXTI_Trigger = trigger;
    exti_init_type.EXTI_LineCmd = cmd;
    EXTI_Init(&exti_init_type);
}


void key_init(void)
{
    init_nvic(KEY_ENTER_IRQC, 0, 0);
    init_nvic(KEY_CANCEL_IRQC, 0, 0);
    init_nvic(KEY_UP_IRQC, 0, 0);
    init_nvic(KEY_DOWN_IRQC, 0, 0);
    RCC_APB2PeriphClockCmd(KEY_ENTER_RCC | KEY_CANCEL_RCC |
                           KEY_UP_RCC | KEY_DOWN_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    init_exti(KEY_ENTER_PORT, KEY_ENTER_Pin, GPIO_Mode_IPU,
              KEY_ENTER_PORTS, KEY_ENTER_PinS);
    init_exti(KEY_CANCEL_PORT, KEY_CANCEL_Pin, GPIO_Mode_IPU,
              KEY_CANCEL_PORTS, KEY_CANCEL_PinS);
    init_exti(KEY_UP_PORT, KEY_UP_Pin, GPIO_Mode_IPU,
              KEY_UP_PORTS, KEY_UP_PinS);
    init_exti(KEY_DOWN_PORT, KEY_DOWN_Pin, GPIO_Mode_IPD,
              KEY_DOWN_PORTS, KEY_DOWN_PinS);
}





