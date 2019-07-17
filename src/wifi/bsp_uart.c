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

static void uart_init(
    USART_TypeDef* uart,
    void (*gpio_clk_fun)(uint32_t, FunctionalState),
    void (*uart_clk_fun)(uint32_t, FunctionalState),
    uint32_t gpio_clk, uint32_t uart_clk, GPIO_TypeDef* tx_port,
    uint16_t tx_pin, GPIO_TypeDef* rx_port, uint16_t rx_pin,
    uint8_t IRQChannel, uint8_t PreemptionPriority,
    uint8_t SubPriority,
    uint32_t baudrate, uint16_t word_length,
    uint16_t stopbits, uint16_t parity, uint16_t mode,
    uint16_t flow)
{
    GPIO_InitTypeDef gpio_init_type;
    USART_InitTypeDef uart_init_type;

    gpio_clk_fun(gpio_clk, ENABLE);

    gpio_init_type.GPIO_Pin = tx_pin;
    gpio_init_type.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_init_type.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(tx_port, &gpio_init_type);

    gpio_init_type.GPIO_Pin = rx_pin;
    gpio_init_type.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(rx_port, &gpio_init_type);

    uart_clk_fun(uart_clk, ENABLE);

    uart_init_type.USART_BaudRate = baudrate;
    uart_init_type.USART_WordLength = word_length;
    uart_init_type.USART_StopBits = stopbits;
    uart_init_type.USART_Parity = parity;
    uart_init_type.USART_HardwareFlowControl = flow;
    uart_init_type.USART_Mode = mode;

    USART_Init(uart, &uart_init_type);

    init_nvic(IRQChannel, PreemptionPriority, SubPriority);

    USART_ITConfig(uart, USART_IT_RXNE, ENABLE);

    USART_Cmd(uart, ENABLE);
}

void uart1_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow)
{
    uart_init(
        UART1,
        UART1_GPIO_APBxClkCmd,
        UART1_APBxClkCmd,
        UART1_GPIO_CLK, UART1_CLK,
        UART1_TX_GPIO_PORT, UART1_TX_GPIO_PIN,
        UART1_RX_GPIO_PORT, UART1_RX_GPIO_PIN,
        UART1_IRQ, 1, 1,
        baudrate, word_length,
        stopbits, parity, mode, flow);
}

void uart2_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow)
{
    uart_init(
        UART2,
        UART2_GPIO_APBxClkCmd,
        UART2_APBxClkCmd,
        UART2_GPIO_CLK, UART2_CLK,
        UART2_TX_GPIO_PORT, UART2_TX_GPIO_PIN,
        UART2_RX_GPIO_PORT, UART2_RX_GPIO_PIN,
        UART2_IRQ, 1, 2,
        baudrate, word_length,
        stopbits, parity, mode, flow);
}


void uart3_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow)
{
    uart_init(
        UART3,
        UART3_GPIO_APBxClkCmd,
        UART3_APBxClkCmd,
        UART3_GPIO_CLK, UART3_CLK,
        UART3_TX_GPIO_PORT, UART3_TX_GPIO_PIN,
        UART3_RX_GPIO_PORT, UART3_RX_GPIO_PIN,
        UART3_IRQ, 1, 3,
        baudrate, word_length,
        stopbits, parity, mode, flow);
}


void uart4_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow)
{
    uart_init(
        UART4,
        UART4_GPIO_APBxClkCmd,
        UART4_APBxClkCmd,
        UART4_GPIO_CLK, UART4_CLK,
        UART4_TX_GPIO_PORT, UART4_TX_GPIO_PIN,
        UART4_RX_GPIO_PORT, UART4_RX_GPIO_PIN,
        UART4_IRQ, 1, 4,
        baudrate, word_length,
        stopbits, parity, mode, flow);
}


void uart5_init(uint32_t baudrate, uint16_t word_length,
                uint16_t stopbits, uint16_t parity, uint16_t mode,
                uint16_t flow)
{
    UART5_GPIO_APBxClkCmd(UART5_GPIO_CLK1, ENABLE);
    uart_init(
        UART5,
        UART5_GPIO_APBxClkCmd,
        UART5_APBxClkCmd,
        UART5_GPIO_CLK2, UART5_CLK,
        UART5_TX_GPIO_PORT, UART5_TX_GPIO_PIN,
        UART5_RX_GPIO_PORT, UART5_RX_GPIO_PIN,
        UART5_IRQ, 1, 5,
        baudrate, word_length,
        stopbits, parity, mode, flow);
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
    while (str[k - 1] != '\0');

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


