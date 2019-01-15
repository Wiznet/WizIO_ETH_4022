#ifndef __TIMERHANDLER_H__
#define __TIMERHANDLER_H__

#include <stdint.h>

extern volatile uint8_t g_interval_flag;
extern uint8_t g_reconn_flag;
extern uint32_t g_reconn_time;
extern uint8_t g_link_status_flag;
extern uint32_t g_link_status_time;

void Timer0IRQHandler(void);
void Timer1IRQHandler(void);
void ConfigurationTimer0(void);
void ConfigurationTimer1(void);
void delay_cnt(uint32_t count);
void delay_ms(uint32_t ms);

#endif
