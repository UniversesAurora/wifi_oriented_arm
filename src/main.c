#include "stm32f10x.h"
#include "wifi/esp8266.h"
#include "display/list_display.h"

void callme(void* ii)
{
    if (!ii)
        list_stop_display();
    else
    {
        lcd_clear_screen();
        lcd_print(ii, 0, 0);

        while (!test_cancel());
    }
}

void update(display_list* dis)
{
    dis->icon_num = 1;
    dis->indicator = '*';
    dis->row_num = 8;
    dis->rows[0].line_icon = "<";
    dis->rows[0].line_name = "Calendar";
    dis->rows[0].message = "2019...Maybe";
    dis->rows[1].line_icon = ">";
    dis->rows[1].line_name = "Clock";
    dis->rows[1].message = "00:00, error less than 24h";
    dis->rows[2].line_icon = "$";
    dis->rows[2].line_name = "Notes";
    dis->rows[2].message = "Write on paper, man";
    dis->rows[3].line_icon = " ";
    dis->rows[3].line_name = "Reminders";
    dis->rows[3].message = "I'll remind you, if I can";
    dis->rows[4].line_icon = "{";
    dis->rows[4].line_name = "Stocks";
    dis->rows[4].message = "If you have money.";
    dis->rows[5].line_icon = "|";
    dis->rows[5].line_name = "Safari";
    dis->rows[5].message = "Welcome! But what's that";
    dis->rows[6].line_icon = " ";
    dis->rows[6].line_name = "Settings";
    dis->rows[6].message = "You thing you need that?";
    dis->rows[7].line_icon = "#";
    dis->rows[7].line_name = "EXIT!!!";
}

display_list list;



int main(void)
{
//    uart1_init(115200, USART_WordLength_8b,
//               USART_StopBits_1, USART_Parity_No,
//               USART_Mode_Rx | USART_Mode_Tx,
//               USART_HardwareFlowControl_None);
//    init_wifi_power();
//    wifi_init(WIFI_1);
//    wifi_init(WIFI_2);
//    wifi_init(WIFI_3);
//    wifi_init(WIFI_4);
//    debug_printf("wait1\n");
//    wait_at(WIFI_1);
//    debug_printf("wait2\n");
//    wait_at(WIFI_2);
//    debug_printf("wait3\n");
//    wait_at(WIFI_3);
//    debug_printf("wait4\n");
//    wait_at(WIFI_4);
//    debug_printf("set1\n");
//    mode_set(WIFI_1);
//    debug_printf("set2\n");
//    mode_set(WIFI_2);
//    debug_printf("set3\n");
//    mode_set(WIFI_3);
//    debug_printf("set4\n");
//    mode_set(WIFI_4);
//while (1)
//
//        printf("hello\n");
//        char* ret = exec_wifi_cmd(WIFI_4, "AT+CWLAP", 2);
//        printf("%s\n", ret);
//
//    printf("hello\n");
//        ret = exec_wifi_cmd(WIFI_1, "AT+CWLAP", 2);
//        printf("%s\n", ret);
//    printf("hello\n");
//        ret = exec_wifi_cmd(WIFI_2, "AT+CWLAP", 2);
//        printf("%s\n", ret);
//    printf("hello\n");
//        ret = exec_wifi_cmd(WIFI_3, "AT+CWLAP", 2);
//        printf("%s\n", ret);
//    while (1)
//    {
//        exec_all_wifi_cmd("AT+CWLAP", 2000);
//        printf("%s\n", wifi1_frame_record.Data_RX_BUF);
//        printf("%s\n", wifi2_frame_record.Data_RX_BUF);
//        printf("%s\n", wifi3_frame_record.Data_RX_BUF);
//        printf("%s\n", wifi4_frame_record.Data_RX_BUF);
//        systick_delay(1000);
//    }
    list_set_list(&list);
    list_set_update_func(update);
    list_set_callon_func(callme);
    list_start_display();
    lcd_clear_screen();
    lcd_print("YOU HAVE LOST!!!!", 0, 0);
}
