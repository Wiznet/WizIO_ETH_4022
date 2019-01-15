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
#include "w7500x_flash.h"
#include "config_data.h"
#include "config_message.h"
#include "flash_handler.h"
#include "gpio_handler.h"
#include "storage_handler.h"
#include "timer_handler.h"
#include "main.h"
#include "common.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BOOT_VEC_BACK_ADDR      (DEVICE_APP_MAIN_ADDR - SECT_SIZE)
#define _MAIN_DEBUG_

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t g_send_buf[WORK_BUF_SIZE];
uint8_t g_recv_buf[WORK_BUF_SIZE];
uint8_t g_socket_rcv_buf[MAX_MTU_SIZE];
uint8_t g_op_mode = NORMAL_MODE;
static __IO uint32_t TimingDelay;

/* Private function prototypes -----------------------------------------------*/
void delay(__IO uint32_t milliseconds);
void TimingDelay_Decrement(void);
static int application_update(void);
static void application_jump(void);
static void Copy_Interrupt_VectorTable(uint32_t start_addr);
static void Backup_Boot_Interrupt_VectorTable(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
    int ret;

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

    if (*(uint32_t*) BOOT_VEC_BACK_ADDR == 0xFFFFFFFF) {
        Backup_Boot_Interrupt_VectorTable();
    } else {
        Copy_Interrupt_VectorTable(BOOT_VEC_BACK_ADDR);
    }

    InitLed(kLED1);
    InitLed(kLED2);
    InitLed(kLED3);

    OffLed(kLED1);
    OffLed(kLED2);
    OffLed(kLED3);

    InitBuzzerPin();
    OffBuzzer();

    InitBootPin();

    /* Load Configure Information */
    LoadWIZIOPacketFromStorage();

    ConfigurationTimer0();

    /* Check MAC Address */
    CheckMacAddress();
    OnBuzzer();
#ifdef _MAIN_DEBUG_
    uint8_t tmpstr[6] = { 0, };

    ctlwizchip(CW_GET_ID, (void*) tmpstr);
    printf("\r\n============================================\r\n");
    printf(" WizIO %s Boot\r\n", tmpstr);
    printf("============================================\r\n");
    printf("[BOOT] SourceClock : %d\r\n", GetSourceClock());
    printf("[BOOT] SystemClock : %d\r\n", GetSystemClock());
#endif

    /* Initialize PHY */
#ifdef W7500
    ret = PHY_Init(GPIOB, GPIO_Pin_15, GPIO_Pin_14);
#elif defined (W7500P)
    ret = PHY_Init(GPIOB, GPIO_Pin_14, GPIO_Pin_15);
#endif
#ifdef _MAIN_DEBUG_
    printf("[BOOT] PHY_Init : %s\r\n", ret == SET ? "Success" : "Fail");
#endif
    /* Check Link */
    ret = PHY_GetLinkStatus();
#ifdef _MAIN_DEBUG_
    printf("[BOOT] Link : %s\r\n", ret == PHY_LINK_ON ? "On" : "Off");
#endif
    ConfigurationNet();

    TFTP_init(SOCK_TFTP, g_socket_rcv_buf);

    ret = application_update();

#ifdef _MAIN_DEBUG_
    printf("[BOOT] check trigger:%d ret:%d\r\n", GetBootPinStatus(), ret);
#endif
    if ((GetBootPinStatus() == Bit_SET) && (ret != TFTP_FAIL)) {
        uint32_t tmp;

        tmp = *(volatile uint32_t *) APP_BASE;

        if ((tmp & 0xffffffff) != 0xffffffff) {
            Copy_Interrupt_VectorTable(DEVICE_APP_MAIN_ADDR);
#ifdef _MAIN_DEBUG_
            printf("[BOOT] jump to application\r\n");
#endif
            OffBuzzer();
            application_jump();
        }
    }
    OffBuzzer();
    while (1) {
        if (g_op_mode == NORMAL_MODE) {
            RunUdpConfig(SOCK_CONFIG);
        } else {
            if (TFTP_run() != TFTP_PROGRESS) g_op_mode = NORMAL_MODE;
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

static void application_jump(void)
{
    /* Set Stack Pointer */
    asm volatile("ldr r0, =0x00008000");
    asm volatile("ldr r0, [r0]");
    asm volatile("mov sp, r0");

    /* Jump to Application ResetISR */
    asm volatile("ldr r0, =0x00008004");
    asm volatile("ldr r0, [r0]");
    asm volatile("mov pc, r0");
}

static int application_update(void)
{
    Firmware_Upload_Info firmware_upload_info;
    uint8_t firmup_flag = 0;

    read_storage(0, &firmware_upload_info, sizeof(Firmware_Upload_Info));
    if (firmware_upload_info.wiznet_header.stx == STX) {
        firmup_flag = 1;
    }

    if (firmup_flag) {
        uint32_t tftp_server;
        uint8_t *filename;
        int ret;

        //DBG_PRINT(INFO_DBG, "### Application Update... ###\r\n");
        tftp_server = (firmware_upload_info.tftp_info.ip[0] << 24) | (firmware_upload_info.tftp_info.ip[1] << 16) | (firmware_upload_info.tftp_info.ip[2] << 8) | (firmware_upload_info.tftp_info.ip[3]);
        filename = firmware_upload_info.filename;

        TFTP_read_request(tftp_server, filename);

        while (1) {
            ret = TFTP_run();
            if (ret != TFTP_PROGRESS) break;
        }

        if (ret == TFTP_SUCCESS) {
            ReplyFirmwareUploadDone(SOCK_CONFIG);

            memset(&firmware_upload_info, 0, sizeof(Firmware_Upload_Info));
            write_storage(0, &firmware_upload_info, sizeof(Firmware_Upload_Info));
        }

        return ret;
    }

    return 0;
}

void Copy_Interrupt_VectorTable(uint32_t start_addr)
{
    uint32_t i;
    uint8_t flash_vector_area[SECT_SIZE];

    for (i = 0x00; i < 0x08; i++)
        flash_vector_area[i] = *(volatile uint8_t *) (0x00000000 + i);
    for (i = 0x08; i < 0xA8; i++)
        flash_vector_area[i] = *(volatile uint8_t *) (start_addr + i);  // Actual address range; Interrupt vector table is located here
    for (i = 0xA8; i < SECT_SIZE; i++)
        flash_vector_area[i] = *(volatile uint8_t *) (0x00000000 + i);
    __disable_irq();
    FLASH_IAP(IAP_ERAS_SECT, 0x00000000, 0, 0);  // Erase the interrupt vector table area : Sector 0
    FLASH_IAP(IAP_PROG, 0x00000000, flash_vector_area, SECT_SIZE);  // Write the application vector table to 0x00000000
    __enable_irq();
}

void Backup_Boot_Interrupt_VectorTable(void)
{
    uint32_t i;
    uint8_t flash_vector_area[SECT_SIZE];

    for (i = 0; i < SECT_SIZE; i++) {
        flash_vector_area[i] = *(volatile uint8_t *) (0x00000000 + i);
    }
    __disable_irq();
    FLASH_IAP(IAP_PROG, BOOT_VEC_BACK_ADDR, flash_vector_area, SECT_SIZE);
    __enable_irq();
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
