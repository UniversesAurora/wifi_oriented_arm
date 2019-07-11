#include "bsp_uart.h"

static void init_nvic(uint8_t IRQChannel,
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

void uart1_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow)
{
    GPIO_InitTypeDef gpio_init_type;
    USART_InitTypeDef uart_init_type;

    UART1_GPIO_APBxClkCmd(UART1_GPIO_CLK, ENABLE);

    gpio_init_type.GPIO_Pin = UART1_TX_GPIO_PIN;
    gpio_init_type.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_init_type.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART1_TX_GPIO_PORT, &gpio_init_type);

    gpio_init_type.GPIO_Pin = UART1_RX_GPIO_PIN;
    gpio_init_type.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART1_RX_GPIO_PORT, &gpio_init_type);

    UART1_APBxClkCmd(UART1_CLK, ENABLE);

    uart_init_type.USART_BaudRate = baudrate;

    uart_init_type.USART_WordLength = word_length;

    uart_init_type.USART_StopBits = stopbits;

    uart_init_type.USART_Parity = parity;

    uart_init_type.USART_HardwareFlowControl = flow;

    uart_init_type.USART_Mode = mode;

    USART_Init(UART1, &uart_init_type);

    init_nvic(UART1_IRQ, 1, 1);

    USART_ITConfig(UART1, USART_IT_RXNE, ENABLE);

    USART_Cmd(UART1, ENABLE);
}

void uart2_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow)
{
    GPIO_InitTypeDef gpio_init_type;
    USART_InitTypeDef uart_init_type;

    UART2_GPIO_APBxClkCmd(UART2_GPIO_CLK, ENABLE);

    gpio_init_type.GPIO_Pin = UART2_TX_GPIO_PIN;
    gpio_init_type.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_init_type.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART2_TX_GPIO_PORT, &gpio_init_type);

    gpio_init_type.GPIO_Pin = UART2_RX_GPIO_PIN;
    gpio_init_type.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART2_RX_GPIO_PORT, &gpio_init_type);

    UART2_APBxClkCmd(UART2_CLK, ENABLE);

    uart_init_type.USART_BaudRate = baudrate;

    uart_init_type.USART_WordLength = word_length;

    uart_init_type.USART_StopBits = stopbits;

    uart_init_type.USART_Parity = parity;

    uart_init_type.USART_HardwareFlowControl = flow;

    uart_init_type.USART_Mode = mode;

    USART_Init(UART2, &uart_init_type);

    init_nvic(UART2_IRQ, 1, 2);

    USART_ITConfig(UART2, USART_IT_RXNE, ENABLE);

    USART_Cmd(UART2, ENABLE);
}


void uart3_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow)
{
    GPIO_InitTypeDef gpio_init_type;
    USART_InitTypeDef uart_init_type;

    UART3_GPIO_APBxClkCmd(UART3_GPIO_CLK, ENABLE);

    gpio_init_type.GPIO_Pin = UART3_TX_GPIO_PIN;
    gpio_init_type.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_init_type.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART3_TX_GPIO_PORT, &gpio_init_type);

    gpio_init_type.GPIO_Pin = UART3_RX_GPIO_PIN;
    gpio_init_type.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART3_RX_GPIO_PORT, &gpio_init_type);

    UART3_APBxClkCmd(UART3_CLK, ENABLE);

    uart_init_type.USART_BaudRate = baudrate;

    uart_init_type.USART_WordLength = word_length;

    uart_init_type.USART_StopBits = stopbits;

    uart_init_type.USART_Parity = parity;

    uart_init_type.USART_HardwareFlowControl = flow;

    uart_init_type.USART_Mode = mode;

    USART_Init(UART3, &uart_init_type);

    init_nvic(UART3_IRQ, 1, 3);

    USART_ITConfig(UART3, USART_IT_RXNE, ENABLE);

    USART_Cmd(UART3, ENABLE);
}


void uart4_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow)
{
    GPIO_InitTypeDef gpio_init_type;
    USART_InitTypeDef uart_init_type;

    UART4_GPIO_APBxClkCmd(UART4_GPIO_CLK, ENABLE);

    gpio_init_type.GPIO_Pin = UART4_TX_GPIO_PIN;
    gpio_init_type.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_init_type.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART4_TX_GPIO_PORT, &gpio_init_type);

    gpio_init_type.GPIO_Pin = UART4_RX_GPIO_PIN;
    gpio_init_type.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART4_RX_GPIO_PORT, &gpio_init_type);

    UART4_APBxClkCmd(UART4_CLK, ENABLE);

    uart_init_type.USART_BaudRate = baudrate;

    uart_init_type.USART_WordLength = word_length;

    uart_init_type.USART_StopBits = stopbits;

    uart_init_type.USART_Parity = parity;

    uart_init_type.USART_HardwareFlowControl = flow;

    uart_init_type.USART_Mode = mode;

    USART_Init(UART4, &uart_init_type);

    init_nvic(UART4_IRQ, 1, 4);

    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

    USART_Cmd(UART4, ENABLE);
}


void uart5_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow)
{
    GPIO_InitTypeDef gpio_init_type;
    USART_InitTypeDef uart_init_type;

    UART5_GPIO_APBxClkCmd(UART5_GPIO_CLK1, ENABLE);
    UART5_GPIO_APBxClkCmd(UART5_GPIO_CLK2, ENABLE);

    gpio_init_type.GPIO_Pin = UART5_TX_GPIO_PIN;
    gpio_init_type.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_init_type.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART5_TX_GPIO_PORT, &gpio_init_type);

    gpio_init_type.GPIO_Pin = UART5_RX_GPIO_PIN;
    gpio_init_type.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART5_RX_GPIO_PORT, &gpio_init_type);

    UART5_APBxClkCmd(UART5_CLK, ENABLE);

    uart_init_type.USART_BaudRate = baudrate;

    uart_init_type.USART_WordLength = word_length;

    uart_init_type.USART_StopBits = stopbits;

    uart_init_type.USART_Parity = parity;

    uart_init_type.USART_HardwareFlowControl = flow;

    uart_init_type.USART_Mode = mode;

    USART_Init(UART5, &uart_init_type);

    init_nvic(UART5_IRQ, 1, 5);

    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);

    USART_Cmd(UART5, ENABLE);
}






void uart_send_byte(USART_TypeDef* pUSARTx, uint8_t ch)
{
    USART_SendData(pUSARTx, ch);

    while (USART_GetFlagStatus(pUSARTx,
                               USART_FLAG_TXE) == RESET);
}


void uart_send_string(USART_TypeDef* pUSARTx, char* str)
{
    uint64_t k = 0;

    do
    {
        uart_send_byte(pUSARTx, str[k]);
        k++;
    }
    while (str[k] != '\0');

    while (USART_GetFlagStatus(pUSARTx,
                               USART_FLAG_TC) == RESET);
}

int fputc(int ch, FILE* f)
{
    USART_SendData(DEBUG_UART, (uint8_t) ch);

    while (USART_GetFlagStatus(DEBUG_UART,
                               USART_FLAG_TXE) == RESET);

    return (ch);
}

int fgetc(FILE* f)
{
    while (USART_GetFlagStatus(DEBUG_UART,
                               USART_FLAG_RXNE) == RESET);

    return (int)USART_ReceiveData(DEBUG_UART);
}


