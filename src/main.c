#include "stm32f10x.h"
#include "wifi/esp8266.h"

int main(void)
{
    uart1_init(115200, USART_WordLength_8b,
               USART_StopBits_1, USART_Parity_No,
               USART_Mode_Rx | USART_Mode_Tx,
               USART_HardwareFlowControl_None);
    init_wifi_power();
    wifi_init(WIFI_1);
    wifi_init(WIFI_2);
    wifi_init(WIFI_3);
    wifi_init(WIFI_4);


    debug_printf("wait1\n");
    wait_at(WIFI_1);
    debug_printf("wait2\n");
    wait_at(WIFI_2);
    debug_printf("wait3\n");
    wait_at(WIFI_3);
    debug_printf("wait4\n");
    wait_at(WIFI_4);
    debug_printf("set1\n");
    mode_set(WIFI_1);
    debug_printf("set2\n");
    mode_set(WIFI_2);
    debug_printf("set3\n");
    mode_set(WIFI_3);
    debug_printf("set4\n");
    mode_set(WIFI_4);

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

    while (1)
    {
        exec_all_wifi_cmd("AT+CWLAP", 2000);
        printf("%s\n", wifi1_frame_record.Data_RX_BUF);
        printf("%s\n", wifi2_frame_record.Data_RX_BUF);
        printf("%s\n", wifi3_frame_record.Data_RX_BUF);
        printf("%s\n", wifi4_frame_record.Data_RX_BUF);
        systick_delay(1000);
    }
}
