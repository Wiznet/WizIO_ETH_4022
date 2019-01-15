#ifndef __TIMERHANDLER_H__
#define __TIMERHANDLER_H__

#include <stdint.h>

void Timer0IRQHandler(void);
void Timer1IRQHandler(void);
void ConfigurationTimer0(void);
void ConfigurationTimer1(void);
void delay_cnt(uint32_t count);
void delay_ms(uint32_t ms);

#endif
