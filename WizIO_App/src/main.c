/**
 ******************************************************************************
 * @file    main.c
 * @author  WIZnet
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2018 WIZnet</center></h2>
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "dhcp.h"
#include "dns.h"
#include "tftp.h"
#include "dhcp_cb.h"
#include "config_data.h"
#include "config_message.h"
#include "modbus.h"
#include "analog_handler.h"
#include "digital_handler.h"
#include "flash_handler.h"
#include "gpio_handler.h"
#include "storage_handler.h"
#include "timer_handler.h"
#include "remote_io.h"
#include "main.h"
#include "common.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define _MAIN_DEBUG_

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t g_send_buf[WORK_BUF_SIZE];
uint8_t g_recv_buf[WORK_BUF_SIZE];
uint8_t g_run_dns = ENABLE;
uint8_t g_buzzer_on_flag = 0;
uint8_t g_buzzer_locate_flag = 0;
static __IO uint32_t TimingDelay;

/* Private function prototypes -----------------------------------------------*/
void delay(__IO uint32_t milliseconds);
void TimingDelay_Decrement(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
    int ret;
    WIZIOPacket *value = GetWIZIOPacketPointer();
    uint8_t dns_server_ip[4];
    uint8_t analog_in_count = 0;
    uint8_t digital_in_count = 0;
    uint8_t digital_out_count = 0;

    /* Set System init */
    SystemInit();

    /* Set SysTick init */
    SysTick_Config((GetSystemClock() / 1000));

    /* Set WZ_100US Register */
    setTIC100US((GetSystemClock() / 10000));

#if BOARD == WIZWIKI_W7500
    ConfigurationDebugUart1();
#else
    /* Configure UART2 */
    S_UART_Init(115200);
    S_UART_Cmd(ENABLE);
#endif

    InitLed(kLED1);  //12
    InitLed(kLED2);  //13
    InitLed(kLED3);  //14

    OffLed(kLED1);
    OffLed(kLED2);
    OffLed(kLED3);

    InitBuzzerPin();
    OnBuzzer();
    g_buzzer_on_flag = 1;

    /* Load Configure Information */
    LoadWIZIOPacketFromStorage();

    ConfigurationTimer0();
    ConfigurationTimer1();

#ifdef _MAIN_DEBUG_
    uint8_t tmpstr[6] = { 0, };

    ctlwizchip(CW_GET_ID, (void*) tmpstr);
    printf("\r\n============================================\r\n");
    printf(" WizIO %s App\r\n", tmpstr);
    printf("============================================\r\n");
    printf("[APP] SourceClock : %d\r\n", GetSourceClock());
    printf("[APP] SystemClock : %d\r\n", GetSystemClock());
    printf("[APP] Module Configuration Size : %d\r\n", sizeof(WIZIOPacket));
#endif

    /* Initialize PHY */
#ifdef W7500
    ret = PHY_Init(GPIOB, GPIO_Pin_15, GPIO_Pin_14);
#elif defined (W7500P)
    ret = PHY_Init(GPIOB, GPIO_Pin_14, GPIO_Pin_15);
#endif
#ifdef _MAIN_DEBUG_
    printf("[APP] PHY_Init : %s\r\n", ret == SET ? "Success" : "Fail");
#endif
    /* Check Link */
    ret = PHY_GetLinkStatus();
#ifdef _MAIN_DEBUG_
    printf("[APP] Link : %s\r\n", ret == PHY_LINK_ON ? "On" : "Off");
#endif
    ConfigurationMac();

    DHCP_init(SOCK_DHCP, g_send_buf);
    reg_dhcp_cbfunc(dhcp_assign, dhcp_assign, dhcp_conflict);
    /* Initialize Network Information */
    if (value->options.dhcp_use) {       // DHCP
        uint32_t ret;
        uint8_t dhcp_retry = 0;
#ifdef _MAIN_DEBUG_
        printf("[APP] Start DHCP\r\n");
#endif
        while (1) {
            ret = DHCP_run();

            if (ret == DHCP_IP_LEASED) break;
            else if (ret == DHCP_FAILED) dhcp_retry++;

            if (dhcp_retry > 3) {
                ConfigurationNet();
                break;
            }
            RunUdpConfig(SOCK_CONFIG);
        }
    } else {
        ConfigurationNet();       //Static
    }

    DisplayNetInfo();

    DNS_init(SOCK_DNS, g_send_buf);
    if (value->options.dns_use) {
        uint8_t dns_retry = 0;

        memcpy(dns_server_ip, value->network_info_common.dns, sizeof(dns_server_ip));

        while (1) {
            if (DNS_run(dns_server_ip, (uint8_t *) value->options.dns_domain_name, value->working_info.remote_ip) == 1) break;
            else dns_retry++;

            if (dns_retry > 3) {
                break;
            }

            RunUdpConfig(SOCK_CONFIG);

            if (value->options.dhcp_use) DHCP_run();
        }
    }

    /* Analog Input initial */
    InitMCP320xSpiInterface();
    InitMCP320xType(SINGLE, MCP3204);

    if (value->analog_in_common.filter == kAverage) {
        InitAnalogInFilterValue();
    }

    /* Digital Input initial */
    InitDigitalIn();
    /* Digital Output initial */
    InitDigitalOut();

    while (1) {
        /* Update Analog in value */
        UpdateAnalogInValue(analog_in_count);
        analog_in_count++;
        if (analog_in_count >= AI_NUM) {
            analog_in_count = 0;
        }

        /* Update Digital in value */
        UpdateDigitalInValue(digital_in_count);
        digital_in_count++;
        if (digital_in_count >= DI_NUM) {
            digital_in_count = 0;
        }

        /* Update Digital out value */
        UpdateDigitalOutValue(digital_out_count);
        digital_out_count++;
        if (digital_out_count >= DO_NUM) {
            digital_out_count = 0;
        }

        RunRemoteIO(SOCK_DATA);
        RunUdpConfig(SOCK_CONFIG);

        if (value->options.dhcp_use == ENABLE) DHCP_run();

        if (value->options.dns_use == ENABLE && g_run_dns == ENABLE) {
            memcpy(dns_server_ip, value->network_info_common.dns, sizeof(dns_server_ip));
            if (DNS_run(dns_server_ip, (uint8_t *) value->options.dns_domain_name, value->working_info.remote_ip) == 1) {
                g_run_dns = DISABLE;
            }
        }
    }

    return 0;
}

/**
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in milliseconds.
 * @retval None
 */
void delay(__IO uint32_t milliseconds)
{
    TimingDelay = milliseconds;
    while (TimingDelay != 0)
        ;
}

/**
 * @brief  Decrements the TimingDelay variable.
 * @param  None
 * @retval None
 */
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00) {
        TimingDelay--;
    }
}

#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    printf("Wrong parameters value: file %s on line %d\r\n", file, line);
    /* Infinite loop */
    while (1) {
    }
}
#endif

/******************** (C) COPYRIGHT WIZnet *****END OF FILE********************/
