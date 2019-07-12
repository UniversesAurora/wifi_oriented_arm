#include "bsp_systick.h"

static void delay_hard(uint64_t time, uint32_t unit)
{
    uint32_t max = SysTick_LOAD_RELOAD_Msk / unit;
    uint32_t max_ticks = unit * max;
    uint64_t times = time / max;
    uint64_t remain = time % max;

    SysTick_Config(max_ticks);

    for (; times > 0; times--)
        while (!((SysTick->CTRL) & (1 << 16)));

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

    SysTick_Config(remain * unit);

    while (!((SysTick->CTRL) & (1 << 16)));

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void delay_hard_us(uint64_t us)
{
    delay_hard(us, 72);
}

void delay_hard_ms(uint64_t ms)
{
    delay_hard(ms, 72000);
}



volatile uint64_t systick_int_times;

static void delay_int(uint64_t time, uint32_t unit)
{
    uint32_t max = SysTick_LOAD_RELOAD_Msk / unit;
    uint32_t max_ticks = unit * max;
    uint64_t times = time / max;
    uint64_t remain = time % max;

    systick_int_times = times;
    SysTick_Config(max_ticks);

    while (systick_int_times);

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;


    systick_int_times = 1;
    SysTick_Config(remain * unit);

    while (systick_int_times);

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void delay_int_us(uint64_t us)
{
    delay_int(us, 72);
}

void delay_int_ms(uint64_t ms)
{
    delay_int(ms, 72000);
}

