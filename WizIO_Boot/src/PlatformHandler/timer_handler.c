#include <stdio.h>
#include "tftp.h"
#include "socket.h"
#include "dhcp.h"
#include "dns.h"
#include "w7500x_dualtimer.h"
#include "config_data.h"
#include "gpio_handler.h"
#include "timer_handler.h"

static uint32_t g_mill_cnt = 0;
static uint8_t g_led_index = 0;
static uint8_t g_led_direction = 0;
static uint32_t g_mic_cnt = 0;

void Timer0IRQHandler(void)
{
    if (DUALTIMER_GetITStatus(DUALTIMER0_0)) {
        DUALTIMER_ClearIT(DUALTIMER0_0);

        g_mill_cnt++;

        if ((g_mill_cnt % (100 - 1)) == 0) {

            if (g_led_direction == 0) {
                g_led_index++;
            } else {
                g_led_index--;
            }

            if (g_led_index == 2) {
                g_led_direction = 1;
            } else if (g_led_index == 0) {
                g_led_direction = 0;
            }
            ToggleLed(g_led_index);
        }

        if ((g_mill_cnt % (1000 - 1)) == 0) {
            g_mill_cnt = 0;
            tftp_timeout_handler();
        }
    }
}

void Timer1IRQHandler(void)
{
    if (DUALTIMER_GetITStatus(DUALTIMER1_0)) {
        DUALTIMER_ClearIT(DUALTIMER1_0);
        g_mic_cnt++;
        //ToggleBuzzer();
        if ((g_mic_cnt % (10 - 1)) == 0) {

        }
    }
}

void ConfigurationTimer0(void)
{
    DUALTIMER_InitTypDef DUALTIMER_InitStructure;

    DUALTIMER_InitStructure.Timer_Load = 8000 - 1;  //1ms
    DUALTIMER_InitStructure.Timer_Prescaler = DUALTIMER_Prescaler_1;
    DUALTIMER_InitStructure.Timer_Wrapping = DUALTIMER_Periodic;
    DUALTIMER_InitStructure.Timer_Repetition = DUALTIMER_Wrapping;
    DUALTIMER_InitStructure.Timer_Size = DUALTIMER_Size_32;
    DUALTIMER_Init(DUALTIMER0_0, &DUALTIMER_InitStructure);

    DUALTIMER_ITConfig(DUALTIMER0_0, ENABLE);

    NVIC_EnableIRQ(DUALTIMER0_IRQn);

    DUALTIMER_Cmd(DUALTIMER0_0, ENABLE);
}

void ConfigurationTimer1(void)
{
    DUALTIMER_InitTypDef DUALTIMER_InitStructure;

    DUALTIMER_InitStructure.Timer_Load = 800 - 1;  //100us
    DUALTIMER_InitStructure.Timer_Prescaler = DUALTIMER_Prescaler_1;
    DUALTIMER_InitStructure.Timer_Wrapping = DUALTIMER_Periodic;
    DUALTIMER_InitStructure.Timer_Repetition = DUALTIMER_Wrapping;
    DUALTIMER_InitStructure.Timer_Size = DUALTIMER_Size_32;
    DUALTIMER_Init(DUALTIMER1_0, &DUALTIMER_InitStructure);

    DUALTIMER_ITConfig(DUALTIMER1_0, ENABLE);

    NVIC_EnableIRQ(DUALTIMER1_IRQn);

    DUALTIMER_Cmd(DUALTIMER1_0, ENABLE);
}

void delay_cnt(uint32_t count)
{
    volatile uint32_t tmp = count;

    while (tmp--)
        ;
}

void delay_ms(uint32_t ms)
{
    volatile uint32_t nCount;

    nCount = (GetSystemClock() / 10000) * ms;
    for (; nCount != 0; nCount--)
        ;
}

