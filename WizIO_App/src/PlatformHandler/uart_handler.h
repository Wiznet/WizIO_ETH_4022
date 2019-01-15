#ifndef __UARTHANDLER_H__
#define __UARTHANDLER_H__

#include "w7500x.h"
#include "common.h"

void myprintf(char *fmt, ...);

#if BOARD == WIZWIKI_W7500
void ConfigurationDebugUart1(void);
#endif

#endif

