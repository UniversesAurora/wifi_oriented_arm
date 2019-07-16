#include "bsp_systick.h"

delay_queue delay_record;
tick_wait_queue tick_wait_record;


// return MAX_TICK_WAIT_QUEUE_LEN when no space
uint64_t tick_reg(uint64_t time,
                  void (* reg_func)(uint64_t reg_identifier, void* message),
                  void* message)
{
    tick_wait_unit* new_unit;
    uint64_t count;

    for (count = 0; count < MAX_TICK_WAIT_QUEUE_LEN; count++)
    {
        if (!tick_wait_record.queue[count].exist)
            break;
    }

    if (count >= MAX_TICK_WAIT_QUEUE_LEN)
        return MAX_TICK_WAIT_QUEUE_LEN;

    new_unit = &tick_wait_record.queue[count];

    new_unit->time = time;
    new_unit->next_remain_time = time;
    new_unit->reg_func = reg_func;
    new_unit->message = message;
    tick_wait_record.reg_num++;
    new_unit->exist = 1;

    if (tick_wait_record.reg_num == 1)
        SysTick_Config(72000);

    return count;
}

int tick_unreg(uint64_t reg_identifier)
{
    if (reg_identifier >= MAX_TICK_WAIT_QUEUE_LEN)
        return -1;

    if (!tick_wait_record.queue[reg_identifier].exist)
        return 0;

    memset(&tick_wait_record.queue[reg_identifier], 0,
           sizeof(tick_wait_unit));
    tick_wait_record.reg_num--;

    if (tick_wait_record.reg_num == 0)
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

    return 0;
}


static void delay_timer_handler(uint64_t reg_identifier,
                                void* message)
{
    if (reg_identifier >= MAX_TICK_WAIT_QUEUE_LEN)
        return;

    uint64_t i, counted = 0;

    for (i = 0; i < MAX_DELAY_QUEUE_LEN; i++)
    {
        if (delay_record.queue[i].exist)
        {
            counted++;

            if (delay_record.queue[i].reg_identifier == reg_identifier)
            {
                delay_record.queue[i].finnish = 1;
                tick_unreg(delay_record.queue[i].reg_identifier);
                delay_record.delay_queue_num--;
                return;
            }

            if (counted == delay_record.delay_queue_num)
                return;
        }
    }
}


int systick_delay(uint64_t time)
{
    uint64_t i;

    for (i = 0; i < MAX_DELAY_QUEUE_LEN; i++)
    {
        if (!delay_record.queue[i].exist)
            break;
    }

    if (i >= MAX_DELAY_QUEUE_LEN)
        return -1;

    delay_record.queue[i].finnish = 0;
    uint64_t reg_identifier = tick_reg(time,
                                       delay_timer_handler, NULL);

    if (reg_identifier == MAX_TICK_WAIT_QUEUE_LEN)
        return -1;

    delay_record.delay_queue_num++;
    delay_record.queue[i].reg_identifier = reg_identifier;
    delay_record.queue[i].exist = 1;

    while (!delay_record.queue[i].finnish);

    memset(&delay_record.queue[i], 0, sizeof(delay_unit));

    return 0;
}

void timeout_handler(uint64_t reg_identifier, void* flag)
{
    *(uint8_t*)flag = 1;
    tick_unreg(reg_identifier);
}


/* use these functions will crash the manual workflow of upper functions */

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



