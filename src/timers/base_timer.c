#include "base_timer.h"

static void basic_timer_nvic_config(uint8_t IRQChannel,
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

static void basic_timer_mode_config(TIM_TypeDef* TIMx,
                                    uint16_t period)
{
    TIM_SetCounter(TIMx, 0);

    TIMx->ARR = period;

    TIM_ClearFlag(TIMx, TIM_FLAG_Update);
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIMx, ENABLE);
}

void base_timer_1_init(void)
{
    basic_timer_nvic_config(BASIC_TIM1_IRQ, 0, 3);
    BASIC_TIM1_APBxClock_FUN(BASIC_TIM1_CLK, ENABLE);
    BASIC_TIM1->PSC = BASIC_TIM1_Prescaler;
    BASIC_TIM1->EGR = TIM_PSCReloadMode_Immediate;
    TIM_ARRPreloadConfig(BASIC_TIM1, DISABLE);
}

void base_timer_2_init(void)
{
    basic_timer_nvic_config(BASIC_TIM2_IRQ, 0, 2);
    BASIC_TIM2_APBxClock_FUN(BASIC_TIM2_CLK, ENABLE);
    BASIC_TIM2->PSC = BASIC_TIM2_Prescaler;
    BASIC_TIM2->EGR = TIM_PSCReloadMode_Immediate;
    TIM_ARRPreloadConfig(BASIC_TIM2, DISABLE);
}



volatile uint64_t basic_tim1_int_times;

void delay_base_timer_1(uint64_t time, uint32_t unit)
{
    uint32_t max = (UINT16_MAX + 1) / unit;
    uint32_t max_ticks = unit * max - 1;
    uint64_t times = time / max;
    uint64_t remain = time % max;

    basic_tim1_int_times = times;
    basic_timer_mode_config(BASIC_TIM1, max_ticks);

    while (basic_tim1_int_times);

    TIM_Cmd(BASIC_TIM1, DISABLE);

    basic_tim1_int_times = 1;
    basic_timer_mode_config(BASIC_TIM1, remain * unit - 1);

    while (basic_tim1_int_times);

    TIM_Cmd(BASIC_TIM1, DISABLE);
}

void delay_base_timer_1_us(uint64_t us)
{
    delay_base_timer_1(us, 1);
}

void delay_base_timer_1_ms(uint64_t ms)
{
    delay_base_timer_1(ms, 1000);
}




volatile uint64_t basic_tim2_int_times;

void delay_base_timer_2(uint64_t time, uint32_t unit)
{
    uint32_t max = (UINT16_MAX + 1) / unit;
    uint32_t max_ticks = unit * max - 1;
    uint64_t times = time / max;
    uint64_t remain = time % max;

    basic_tim2_int_times = times;
    basic_timer_mode_config(BASIC_TIM2, max_ticks);

    while (basic_tim2_int_times);

    TIM_Cmd(BASIC_TIM2, DISABLE);

    basic_tim2_int_times = 1;
    basic_timer_mode_config(BASIC_TIM2, remain * unit - 1);

    while (basic_tim2_int_times);

    TIM_Cmd(BASIC_TIM2, DISABLE);
}

void delay_base_timer_2_us(uint64_t us)
{
    delay_base_timer_2(us, 1);
}

void delay_base_timer_2_ms(uint64_t ms)
{
    delay_base_timer_2(ms, 1000);
}

