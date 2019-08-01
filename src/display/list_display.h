#ifndef __LIST_DISPLAY_H
#define __LIST_DISPLAY_H

#include <stm32f10x.h>
#include "lcd_display.h"
#include "../timers/bsp_systick.h"
#include "../key/bsp_key.h"


#define LIST_MAX_ROW 100

#define out_of_memory \
    lcd_clear_screen(); \
    lcd_print("NO MEMORY!", 0, 0)

typedef enum
{
    UPDATE,
    NORMAL,
}
list_update_mode;

typedef struct
{
    char* line_name;
    char* line_icon;
    void* message;
}
list_row;

typedef struct
{
    uint8_t icon_num;
    uint64_t row_num;
    char indicator;
    list_row rows[LIST_MAX_ROW];
}
display_list;


void list_set_list(display_list* list);
void list_set_update_time(uint64_t time);
void list_set_update_func(void (* update_func)(
                              display_list*));
void list_set_callon_func(void (* callon_func)(void*));
uint8_t test_cancel(void);
int list_start_display(void);
void list_stop_display(void);

#endif

