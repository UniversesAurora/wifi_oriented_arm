#include "stm32f10x.h"
#include "wifi/esp8266.h"

int main(void)
{
    uart1_init(115200, USART_WordLength_8b,
               USART_StopBits_1, USART_Parity_No,
               USART_Mode_Rx | USART_Mode_Tx,
               USART_HardwareFlowControl_None);
    wifi_init(WIFI_4);
    
    printf("hello\n");
    wifi_reset(WIFI_4);
    wait_at(WIFI_4);
    while (1)
    {
        printf("hello\n");
        char* ret = exec_wifi_cmd(WIFI_4, "AT+CWLAP", 2);
        printf("%s\n", ret);
        delay_hard_ms(1000);
    }
}
