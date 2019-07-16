#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H

#include <stm32f10x.h>
#include <core_cm3.h>
#include <string.h>


#define MAX_TICK_WAIT_QUEUE_LEN 100
#define MAX_DELAY_QUEUE_LEN     50

typedef struct
{
    uint8_t exist;
    uint64_t time;
    uint64_t next_remain_time;
    void (* reg_func)(uint64_t reg_identifier, void* message);
    void* message;
}
tick_wait_unit;

typedef struct
{
    uint64_t reg_num;
    tick_wait_unit queue[MAX_TICK_WAIT_QUEUE_LEN];
}
tick_wait_queue;

typedef struct
{
    uint8_t exist;
    uint64_t reg_identifier;
    uint8_t finnish;
}
delay_unit;

typedef struct
{
    uint64_t delay_queue_num;
    delay_unit queue[MAX_DELAY_QUEUE_LEN];
}
delay_queue;


uint64_t tick_reg(uint64_t time,
                  void (* reg_func)(uint64_t reg_identifier, void* message),
                  void* message);
int tick_unreg(uint64_t reg_identifier);
int systick_delay(uint64_t time);
void timeout_handler(uint64_t reg_identifier, void* flag);

/* Better not to use these functions */
void delay_hard_us(uint64_t us);
void delay_hard_ms(uint64_t ms);

#endif

