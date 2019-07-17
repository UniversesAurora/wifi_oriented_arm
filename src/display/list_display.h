#ifndef __LIST_DISPLAY_H
#define __LIST_DISPLAY_H

#include <stm32f10x.h>
#include "lcd_display.h"


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
    list_row* rows;
}
display_list;

void update(display_list* list);


#endif

