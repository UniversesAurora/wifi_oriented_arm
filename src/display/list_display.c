#include "list_display.h"

static display_list* current_list;
static uint64_t update_time = 3000;
static void (* ufunc)(display_list*);
static void (* cfunc)(void*);
static uint8_t exit_flag = 0;

static struct
{
    int indicator;
    int upper_space;
}
cur_sts;

uint8_t penter = 0, pcancel = 0, pup = 0, pdown = 0;

void list_set_list(display_list* list)
{
    current_list = list;
}

void list_set_update_time(uint64_t time)
{
    update_time = time;
}

void list_set_update_func(void (* update_func)(
                              display_list*))
{
    ufunc = update_func;
}

void list_set_callon_func(void (* callon_func)(void*))
{
    cfunc = callon_func;
}


static void show(list_update_mode mode)
{
    if (current_list->row_num < 1)
    {
        lcd_clear_screen();
        return;
    }

    static int old_indicator = -1;
    static int old_upper_space = -1;
    int dis_start = cur_sts.indicator - cur_sts.upper_space;
    int item_str_len = hcol_num - 1 - current_list->icon_num;
    int row_iter;
    char* indi_spa = malloc(3);

    if (!indi_spa)
    {
        out_of_memory;
        return;
    }

    sprintf(indi_spa, "%c", current_list->indicator);

    if (dis_start < 0)
    {
        cur_sts.indicator = 0;
        cur_sts.upper_space = 0;
        dis_start = 0;
    }

    if (dis_start + 1 > current_list->row_num)
    {
        cur_sts.indicator = current_list->row_num - 1;
        cur_sts.upper_space = 0;
        dis_start = current_list->row_num - 1;
    }
    else if (cur_sts.indicator > current_list->row_num - 1)
    {
        cur_sts.upper_space -= cur_sts.indicator -
                               current_list->row_num + 1;
        cur_sts.indicator = current_list->row_num - 1;
    }

    if (item_str_len < 0)
        item_str_len = 0;

    if (old_indicator - old_upper_space != cur_sts.indicator -
            cur_sts.upper_space || mode)
        for (row_iter = 0; row_iter < hrow_num; row_iter++)
        {
            if (dis_start + row_iter >= current_list->row_num)
                lcd_print_line_with_num("", row_iter, 1, hcol_num - 1);
            else
            {
                lcd_print_line_with_num(current_list->rows[dis_start +
                                                  row_iter].line_name, row_iter, 1, item_str_len);
                lcd_print_line_with_num(current_list->rows[dis_start +
                                                  row_iter].line_icon, row_iter, item_str_len + 1,
                                        current_list->icon_num);
            }
        }

    for (row_iter = 0; row_iter < hrow_num; row_iter++)
    {
        if (row_iter == cur_sts.upper_space)
            lcd_print_line_with_num(indi_spa, row_iter, 0, 1);
        else
            lcd_print_line_with_num(" ", row_iter, 0, 1);
    }

    old_indicator = cur_sts.indicator;
    old_upper_space = cur_sts.upper_space;
    free(indi_spa);
}


static void infi_check(void)
{
    uint8_t time_to_ref = 0;
    ufunc(current_list);
    show(NORMAL);
    tick_reg(update_time, timeout_handler, &time_to_ref);
    key_enter_open;
    key_up_open;
    key_down_open;

    while (1)
    {
        if (exit_flag)
            return;
        
        if (time_to_ref)
        {
            ufunc(current_list);
            show(NORMAL);
            time_to_ref = 0;
            tick_reg(update_time, timeout_handler, &time_to_ref);
        }
        
        if (exit_flag)
            return;

        if (penter)
        {
            key_enter_close;
            key_up_close;
            key_down_close;
            key_cancel_open;
            cfunc(current_list->rows[cur_sts.indicator].message);
            penter = 0;
            key_enter_open;
            key_up_open;
            key_down_open;
            key_cancel_close;
            pcancel = 0;
            ufunc(current_list);
            show(NORMAL);
        }
        
        if (exit_flag)
            return;

        if (pup)
        {
            if (cur_sts.indicator > 0
                    && cur_sts.indicator < current_list->row_num)
            {
                if (cur_sts.upper_space < 1)
                {
                    cur_sts.indicator--;
                    show(NORMAL);
                }
                else
                {
                    cur_sts.upper_space--;
                    cur_sts.indicator--;
                    show(UPDATE);
                }
            }
            else
            {
                lcd_print_line_with_num("AT TOP!", 0, 0, hcol_num);
                systick_delay(1000);
                show(NORMAL);
            }

            pup = 0;
        }
        
        if (exit_flag)
            return;

        if (pdown)
        {
            if (cur_sts.indicator >= 0
                    && cur_sts.indicator < current_list->row_num - 1)
            {
                if (hrow_num - cur_sts.upper_space < 2)
                {
                    cur_sts.indicator++;
                    show(NORMAL);
                }
                else
                {
                    cur_sts.upper_space++;
                    cur_sts.indicator++;
                    show(UPDATE);
                }
            }
            else
            {
                lcd_print_line_with_num("AT BOTTOM!", hrow_num - 1, 0,
                                        hcol_num);
                systick_delay(1000);
                show(NORMAL);
            }

            pdown = 0;
        }
        
        if (exit_flag)
            return;
    }
}

uint8_t test_cancel(void)
{
    return pcancel;
}


int list_start_display(void)
{
    if (!current_list || !ufunc || !cfunc)
        return -1;

    init_lcd_display();
    key_init();
    infi_check();
    return 0;
}

void list_stop_display(void)
{
    exit_flag = 1;
}



