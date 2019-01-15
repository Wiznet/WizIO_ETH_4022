#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "w7500x.h"
#include "uart_handler.h"

#if BOARD == WIZWIKI_W7500
extern void UartPuts(UART_TypeDef* UARTx, uint8_t *str);
#else
extern void S_UartPuts(uint8_t *str);
#endif

void myprintf(char *fmt, ...)
{
    va_list arg_ptr;
    char etxt[128];  // buffer size

    va_start(arg_ptr, fmt);
    vsprintf(etxt, fmt, arg_ptr);
    va_end(arg_ptr);

#if BOARD == WIZWIKI_W7500
    UartPuts(UART1, etxt);
#else
    S_UartPuts(etxt);
#endif
}

#if BOARD == WIZWIKI_W7500
void ConfigurationDebugUart1(void)
{
    UART_InitTypeDef UART_InitStructure;

    UART_StructInit(&UART_InitStructure);
    UART_Init(UART1, &UART_InitStructure);
    UART_Cmd(UART1, ENABLE);
}
#endif
