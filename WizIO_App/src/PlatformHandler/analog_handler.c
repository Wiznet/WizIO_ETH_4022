#include "modbus.h"
#include "w7500x_gpio.h"
#include "w7500x_ssp.h"
#include "analog_handler.h"
#include "config_data.h"

#define START 0x01

#define NBCHANNELMCP3204 4
#define NBCHANNELMCP3208 8

#define SINGLEENDEDVALUE 0x01
#define DIFFERENTIALVALUE 0x000

uint8_t g_mcp_set = 0;
uint8_t g_input_configuration;
uint8_t g_channel_num = 0;
uint16_t g_pre_average[AI_NUM] = { 0, };
float g_alpha = 0;

static void DelaySwitch(uint32_t count);
static void SelectMCP320x(void);
static void DeselectMCP320x(void);
static uint8_t Transfer8(SSP_TypeDef* SSPx, uint8_t byte);

void InitMCP320xSpiInterface(void)
{
    SSP_InitTypeDef SSP0_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    SSP_StructInit(&SSP0_InitStructure);
    SSP0_InitStructure.SSP_ClockRate = 29;
    SSP0_InitStructure.SSP_CPHA = SSP_CPHA_1Edge;
    SSP0_InitStructure.SSP_CPOL = SSP_CPOL_Low;
    SSP0_InitStructure.SSP_FrameFormat = SSP_FrameFormat_MO;
    SSP0_InitStructure.SSP_DataSize = SSP_DataSize_8b;
    SSP0_InitStructure.SSP_Mode = SSP_Mode_Master;
    SSP0_InitStructure.SSP_ClockPrescaler = SSP_ClockPrescaler_16;
    printf("[APP] SPI CLK : %d\r\n", GetSystemClock() / (SSP0_InitStructure.SSP_ClockPrescaler * (1 + SSP0_InitStructure.SSP_ClockRate)));
    SSP_Init(SSP0, &SSP0_InitStructure);
    SSP_Cmd(SSP0, ENABLE);

    GPIO_InitStructure.GPIO_Pin = CS_PIN;
    GPIO_InitStructure.GPIO_Direction = GPIO_Direction_OUT;
    GPIO_InitStructure.GPIO_Pad = GPIO_OpenDrainDisable | GPIO_HighDrivingStrength | GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_AF = CS_AF;
    GPIO_Init(CS_PORT, &GPIO_InitStructure);

    GPIO_SetBits(CS_PORT, CS_PIN);
}

void InitMCP320xType(InputType read_type, Type mcp_type)
{
    g_mcp_set = 1;

    switch (read_type)
    {
        case SINGLE:
            g_input_configuration = SINGLEENDEDVALUE;
            break;
        case DIFFERENTIAL:
            g_input_configuration = DIFFERENTIALVALUE;
            break;
        default:
            g_mcp_set = 0;
            break;
    }

    switch (mcp_type)
    {
        case MCP3204:
            g_channel_num = NBCHANNELMCP3204;
            break;
        case MCP3208:
            g_channel_num = NBCHANNELMCP3208;
            break;
        default:
            g_mcp_set = 0;
            break;
    }
}

static void SelectMCP320x(void)
{
    GPIO_ResetBits(CS_PORT, CS_PIN);
}

static void DeselectMCP320x(void)
{
    GPIO_SetBits(CS_PORT, CS_PIN);
}

uint16_t ReadMCP320x(uint8_t channel)
{
    uint16_t ans = 0;
    uint8_t send_data;
    uint8_t hn = 0, ln = 0;

    if (channel == 3) {
        channel = 0;
    } else {
        channel = channel +1;
    }

    send_data = (START << 4) | (g_input_configuration << 3) | channel;

    if (g_mcp_set) {
        if ((channel <= g_channel_num) && (channel >= 0)) {
            hn = send_data >> 2;
            ln = send_data << 6;
            SelectMCP320x();
            DelaySwitch(1);

            Transfer8(SSP0, hn);
            hn = Transfer8(SSP0, ln);
            ln = Transfer8(SSP0, 0x00);

            DelaySwitch(1);
            DeselectMCP320x();

            ans = ((hn & 0x0F) << 8) | ln;
        }
    }
    return ans;
}

void InitAnalogInFilterValue(void)
{
    uint8_t i, j;
    struct __analog_in *analog = (struct __analog_in *) GetWIZIOPacketPointer()->analog_in;

    for (i = 0; i < AI_NUM; i++) {
        g_pre_average[i] = ReadMCP320x(i);
    }
    for (i = 1; i < 11; i++) {
        g_alpha = (i - 1) / i;
        for (j = 0; j < AI_NUM; j++) {
            analog[j].value = (g_alpha * g_pre_average[j]) + ((1 - g_alpha) * ReadMCP320x(j));
            g_pre_average[j] = analog[j].value;
        }
    }
}

void UpdateAnalogInValue(AnalogInNum num)
{
    g_alpha = 0.7;

    struct __analog_in *analog = (struct __analog_in *) GetWIZIOPacketPointer()->analog_in;
    struct __analog_in_common *common = (struct __analog_in_common *) &GetWIZIOPacketPointer()->analog_in_common;

    if (analog[num].use == ENABLE) {
        if (common->filter == kNone) {
            analog[num].value = ReadMCP320x(num);
            g_analog_in_register[num] = analog[num].value;
        } else {
            analog[num].value = (g_alpha * g_pre_average[num]) + ((1 - g_alpha) * ReadMCP320x(num));
            g_analog_in_register[num] = analog[num].value;
            g_pre_average[num] = analog[num].value;
        }
    } else {
        analog[num].value = 0;
        g_analog_in_register[num] = 0;
    }
}

static uint8_t Transfer8(SSP_TypeDef* SSPx, uint8_t byte)
{
    SSP_SendData(SSPx, byte);

    return SSP_ReceiveData(SSPx);
}

static void DelaySwitch(__IO uint32_t milliseconds)
{
    volatile uint32_t nCount;

    nCount = (GetSystemClock() / 10000) * milliseconds;
    for (; nCount != 0; nCount--)
        ;
}
