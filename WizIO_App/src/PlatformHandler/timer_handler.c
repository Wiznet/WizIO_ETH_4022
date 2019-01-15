#include <stdio.h>
#include "tftp.h"
#include "socket.h"
#include "dhcp.h"
#include "dns.h"
#include "mqtt_interface.h"
#include "w7500x_dualtimer.h"
#include "config_data.h"
#include "digital_handler.h"
#include "gpio_handler.h"
#include "timer_handler.h"
#include "common.h"

volatile uint8_t g_interval_flag = 0;
volatile uint32_t g_interval_time = 0;

uint8_t g_reconn_flag = 0; /* 0 : connect / 1 : NONE */
uint32_t g_reconn_time = 0;

static uint32_t g_timer0_mill_cnt = 0;
static uint32_t g_timer0_sec_cnt = 0;

static uint32_t g_timer1_mill_cnt = 0;

extern uint8_t g_buzzer_on_flag;
static uint32_t g_buzzer_on_cnt = 0;
extern uint8_t g_buzzer_locate_flag;
static uint32_t g_buzzer_locate_cnt = 0;

static uint32_t g_frequency_case_1_run_count[DI_NUM] = { 0, };
static uint32_t g_frequency_case_2_run_count[DI_NUM] = { 0, };

uint8_t g_link_status_flag = 0;
uint32_t g_link_status_time = 0;

extern uint8_t g_run_dns;

void Timer0IRQHandler(void)
{
    struct __options *option = (struct __options *) &(GetWIZIOPacketPointer()->options);

    if (DUALTIMER_GetITStatus(DUALTIMER0_0)) {
        DUALTIMER_ClearIT(DUALTIMER0_0);

        g_timer0_mill_cnt++;
        MilliTimer_Handler();

        /* Sensors data Transfer Interval Process */
        if (!g_interval_flag && option->transfer_interval) {

            g_interval_time++;
            if (g_interval_time >= option->transfer_interval) {
                g_interval_flag = 1;
                g_interval_time = 0;
            }
        }

        /* Reconnection Process */
        if (g_reconn_flag) g_reconn_time++;

        if (option->reconnection <= g_reconn_time) {
            g_reconn_flag = 0;
            g_reconn_time = 0;
        }

        /* Second Process */
        if ((g_timer0_mill_cnt % (1000 - 1)) == 0) {
            ToggleLed(kLED1);
            g_timer0_mill_cnt = 0;
            g_timer0_sec_cnt++;

            /* DHCP Process */
            if (option->dhcp_use) DHCP_time_handler();

            /* DNS Process */
#if 1
            if (option->dns_use) {
                DNS_time_handler();
            }
#endif
            /* Minute Process */
            if ((g_timer0_sec_cnt % (60 - 1)) == 0) {
                g_timer0_sec_cnt = 0;
#if 1
                /* DNS Process */
                if (option->dns_use) {
                    g_run_dns = 1;
                }
#endif
            }
            /* Link Status Time Process */
            if (g_link_status_flag == 1) {
                g_link_status_time++;
                if ((g_link_status_time % 5) == 0) {
                    g_link_status_time = 0;
                    g_link_status_flag = 2;
                }
            }
        }
    }
}

void Timer1IRQHandler(void)
{
    uint8_t i;
    if (DUALTIMER_GetITStatus(DUALTIMER1_0)) {
        DUALTIMER_ClearIT(DUALTIMER1_0);

        if (g_buzzer_on_flag) {
            g_timer1_mill_cnt++;
            if ((g_timer1_mill_cnt % (500 - 1)) == 0) {
                ToggleBuzzer();
                g_timer1_mill_cnt = 0;
                g_buzzer_on_cnt++;
                if (g_buzzer_on_cnt >= 6) {
                    OffBuzzer();
                    g_buzzer_on_cnt = 0;
                    g_buzzer_on_flag = 0;
                    g_timer1_mill_cnt = 0;
                }
            }
        }

        if (g_buzzer_locate_flag) {
            g_timer1_mill_cnt++;
            if ((g_timer1_mill_cnt % (200 - 1)) == 0) {
                ToggleBuzzer();
                g_timer1_mill_cnt = 0;
                g_buzzer_locate_cnt++;
                if (g_buzzer_locate_cnt >= 15) {
                    OffBuzzer();
                    g_buzzer_locate_cnt = 0;
                    g_buzzer_locate_flag = 0;
                    g_timer1_mill_cnt = 0;
                }
            }
        }

        for (i = 0; i < DI_NUM; i++) {
            if (g_frequency_calculation[i].start == ENABLE) {
                g_frequency_case_1_run_count[i]++;
            } else {
                g_frequency_case_1_run_count[i] = 1;
            }

            if (g_frequency_calculation[i].start == DISABLE) {
                g_frequency_case_2_run_count[i]++;
            } else {
                g_frequency_case_2_run_count[i] = 1;
            }
        }

        for (i = 0; i < DI_NUM; i++) {
            if ((g_frequency_case_1_run_count[i] % 1500) == 0) {
                g_frequency_case_1_run_count[i] = 1;
                g_frequency_calculation[i].count_capture = 0;
            }
            if ((g_frequency_case_2_run_count[i] % 1500) == 0) {
                g_frequency_case_2_run_count[i] = 1;
                g_frequency_calculation[i].count_capture = 0;
            }
        }

    }
}

void ConfigurationTimer0(void)
{
    DUALTIMER_InitTypDef DUALTIMER_InitStructure;

    DUALTIMER_InitStructure.Timer_Load = 48000 - 1;  //1ms
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

    DUALTIMER_InitStructure.Timer_Load = 48000 - 1;  //1ms
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

