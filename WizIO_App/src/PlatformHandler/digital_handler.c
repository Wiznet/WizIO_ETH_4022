#include "modbus.h"
#include "w7500x_gpio.h"
#include "w7500x_pwm.h"
#include "config_data.h"
#include "digital_handler.h"

GPIO_TypeDef* gk_DigitalInPort[DI_NUM] = { DI1_PORT, DI2_PORT };
const uint16_t gk_DigitalInPin[DI_NUM] = { DI1_PIN, DI2_PIN };
const uint16_t gk_DigitalInPinSource[DI_NUM] = { DI1_PIN_SOURCE, DI2_PIN_SOURCE };
GPIOAf_TypeDef gk_DigitalInGpioAf[DI_NUM] = { DI1_AF, DI2_AF };
GPIOAf_TypeDef gk_DigitalInPwmAf[DI_NUM] = { DI1_PWM_AF, DI2_PWM_AF };
PWM_TypeDef* gk_DigitalInPwmChannel[DI_NUM] = { DI1_PWM_CH, DI2_PWM_CH };
const uint16_t gk_DigitalInIrq[DI_NUM] = { DI1_IRQ, DI2_IRQ };

GPIO_TypeDef* gk_DigitalOutPort[DO_NUM] = { DO1_PORT, DO2_PORT };
const uint16_t gk_DigitalOutPin[DO_NUM] = { DO1_PIN, DO2_PIN };
const uint16_t gk_DigitalOutPinSource[DI_NUM] = { DO1_PIN_SOURCE, DO2_PIN_SOURCE };
GPIOAf_TypeDef gk_DigitalOutGpioAf[DO_NUM] = { DO1_AF, DO2_AF };
GPIOAf_TypeDef gk_DigitalOutPwmAf[DO_NUM] = { DO1_PWM_AF, DO2_PWM_AF };
PWM_TypeDef* gk_DigitalOutPwmChannel[DO_NUM] = { DO1_PWM_CH, DO2_PWM_CH };

uint8_t g_frequency_value_count[DI_NUM] = { 0, };

void InitDigitalIn(void)
{
    uint8_t i;

    struct __digital_in *digital = (struct __digital_in *) GetWIZIOPacketPointer()->digital_in;

    for (i = 0; i < DI_NUM; i++) {
        if (digital[i].mode == kDI) {
            InitDigitalInWithGpio(i);
        } else {
            InitDigitalInWithPwm(i, digital[i].mode);
        }
    }
}

void InitDigitalInWithGpio(DigitalInNum num)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = gk_DigitalInPin[num];
    GPIO_InitStructure.GPIO_Direction = GPIO_Direction_IN;
    GPIO_InitStructure.GPIO_Pad = GPIO_SummitTrigger | GPIO_InputBufferEnable;
    GPIO_InitStructure.GPIO_AF = gk_DigitalInGpioAf[num];
    GPIO_Init(gk_DigitalInPort[num], &GPIO_InitStructure);
}

void InitDigitalInWithPwm(DigitalInNum num, uint8_t mode)
{
    PWM_InitTypeDef PWM_InitStructure;

    GPIO_PinAFConfig(gk_DigitalInPort[num], gk_DigitalInPinSource[num], gk_DigitalInPwmAf[num]);

    PWM_StructInit(&PWM_InitStructure);

    if (mode == kDIHighCounter) {
        PWM_InitStructure.PWM_Mode = PWM_Mode_CounterFalling;
        PWM_InitStructure.PWM_Output = PWM_Output_OutDisable_InEnable;
        PWM_InitStructure.PWM_Duty = 10;
        PWM_InitStructure.PWM_Period = 0x0000FFFF;
    } else if (mode == kDILowCounter) {
        PWM_InitStructure.PWM_Mode = PWM_Mode_CounterRising;
        PWM_InitStructure.PWM_Output = PWM_Output_OutDisable_InEnable;
        PWM_InitStructure.PWM_Duty = 10;
        PWM_InitStructure.PWM_Period = 0x0000FFFF;
    } else {
        PWM_InitStructure.PWM_Output = PWM_Output_OutDisable_InEnable;
        PWM_InitStructure.PWM_Prescale_Counter = 48 - 1;
        PWM_InitStructure.PWM_Duty = 5;
        PWM_InitStructure.PWM_Period = 0xFFFFFFFF;
        PWM_ITConfig(gk_DigitalInPwmChannel[num], PWM_IT_ALL, ENABLE);
        NVIC_EnableIRQ(gk_DigitalInIrq[num]);
    }

    PWM_InitStructure.PWM_Output = PWM_Output_OutDisable_InEnable;
    PWM_Init(gk_DigitalInPwmChannel[num], &PWM_InitStructure);

    PWM_Cmd(gk_DigitalInPwmChannel[num], ENABLE);
}

uint32_t GetDigitalInCounter(DigitalInNum num)
{
    return PWM_GetCounter(gk_DigitalInPwmChannel[num]);
}

uint32_t GetDigitalInFrequency(DigitalInNum num)
{
    return PWM_GetCapture(gk_DigitalInPwmChannel[num]);
}

uint32_t GetDigitalInStatus(DigitalInNum num)
{
    uint8_t bitstatus = 0x00;

    if (GPIO_ReadInputDataBit(gk_DigitalInPort[num], gk_DigitalInPin[num]) != (uint32_t) Bit_RESET) {
        bitstatus = (uint8_t) Bit_SET;
    } else {
        bitstatus = (uint8_t) Bit_RESET;
    }

    return bitstatus;
}

void UpdateDigitalInValue(DigitalInNum num)
{
    struct __digital_in *digital = (struct __digital_in *) GetWIZIOPacketPointer()->digital_in;

    if (digital[num].use == ENABLE) {
        if (digital[num].mode == kDI) {
            digital[num].value = GetDigitalInStatus(num);
            g_digital_in_coils[num] = digital[num].value;
        } else if (digital[num].mode == kDIHighCounter) {
            digital[num].value = GetDigitalInCounter(num);
            g_digital_in_register[num] = digital[num].value;
        } else if (digital[num].mode == kDILowCounter) {
            digital[num].value = GetDigitalInCounter(num);
            g_digital_in_register[num] = digital[num].value;
        } else {
            if (g_frequency_calculation[num].count_capture == 0) {
                g_frequency_value_count[num]++;
                if (g_frequency_value_count[num] >= 3) {
                    g_frequency_value_count[num] = 0;
                    digital[num].value = g_frequency_calculation[num].count_capture;
                    g_digital_in_register[num] = digital[num].value;
                }
            } else {
                g_frequency_value_count[num] = 0;
                digital[num].value = g_frequency_calculation[num].count_capture;
                g_digital_in_register[num] = digital[num].value;
            }
        }
    } else {
        g_digital_in_coils[num] = 0;
        g_digital_in_register[num] = 0;
        digital[num].value = 0;
    }
}

void InitDigitalOut(void)
{
    uint8_t i;

    struct __digital_out *digital = (struct __digital_out *) GetWIZIOPacketPointer()->digital_out;

    for (i = 0; i < DO_NUM; i++) {
        if (digital[i].use == ENABLE) {
            if (digital[i].mode == kDO) {
                InitDigitalOutWithGpio(i);
                if (digital[i].value == 1) {
                    SetDigitalOutHigh(i);
                } else {
                    SetDigitalOutLow(i);
                }
            } else {
                InitDigitalOutWithPwm(i, digital[i].high_width, digital[i].low_width);
            }
        }
    }
}

void InitDigitalOutWithGpio(DigitalOutNum num)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = gk_DigitalOutPin[num];
    GPIO_InitStructure.GPIO_Direction = GPIO_Direction_OUT;
    GPIO_InitStructure.GPIO_Pad = GPIO_OpenDrainDisable | GPIO_HighDrivingStrength | GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_AF = gk_DigitalOutGpioAf[num];

    GPIO_Init(gk_DigitalOutPort[num], &GPIO_InitStructure);

    delay_cnt(10000);
}

void InitDigitalOutWithPwm(DigitalOutNum num, uint16_t high_width, uint16_t low_width)
{
    PWM_InitTypeDef PWM_InitStructure;

    GPIO_PinAFConfig(gk_DigitalOutPort[num], gk_DigitalOutPinSource[num], gk_DigitalOutPwmAf[num]);

    PWM_StructInit(&PWM_InitStructure);

    PWM_InitStructure.PWM_Output = PWM_Output_OutEnable_InDisable;
    PWM_InitStructure.PWM_Prescale_Counter = 48 - 1;
    PWM_InitStructure.PWM_Duty = (uint32_t) ((high_width * 100) - 1);
    PWM_InitStructure.PWM_Period = PWM_InitStructure.PWM_Duty + (uint32_t) ((low_width * 100) - 1);
    //printf("digital_out[%d], high_width:%d, low_width:%d\r\n", num, high_width, low_width);
    //printf("digital_out[%d], PWM_Duty:%d, PWM_Period:%d\r\n", num, PWM_InitStructure.PWM_Duty, PWM_InitStructure.PWM_Period);
    PWM_Init(gk_DigitalOutPwmChannel[num], &PWM_InitStructure);

    PWM_Cmd(gk_DigitalOutPwmChannel[num], ENABLE);
}

void SetDigitalOutHigh(DigitalOutNum num)
{
    GPIO_SetBits(gk_DigitalOutPort[num], gk_DigitalOutPin[num]);
}

void SetDigitalOutLow(DigitalOutNum num)
{
    GPIO_ResetBits(gk_DigitalOutPort[num], gk_DigitalOutPin[num]);
}

void SetDigitalOutToggle(DigitalOutNum num)
{
    gk_DigitalOutPort[num]->DATAOUT ^= gk_DigitalOutPin[num];
}

uint32_t GetDigitalOutStatus(DigitalOutNum num)
{
    return GPIO_ReadOutputDataBit(gk_DigitalOutPort[num], gk_DigitalOutPin[num]);
}

void UpdateDigitalOutValue(DigitalOutNum num)
{
    struct __digital_out *digital = (struct __digital_out *) GetWIZIOPacketPointer()->digital_out;

    if (digital[num].use == ENABLE) {
        if (digital[num].mode == kDO) {
            digital[num].value = GetDigitalOutStatus(num);
        } else if (digital[num].mode == kDOPulse) {
            digital[num].value = digital[num].high_width + digital[num].low_width;
        }
    }
}

void PwmIRQHandler(DigitalInNum num)
{
    if (PWM_GetITStatus(gk_DigitalInPwmChannel[num], PWM_IT_MI) == SET) {
        PWM_ClearITPendingBit(gk_DigitalInPwmChannel[num], PWM_IT_MI);
        g_frequency_calculation[num].start = ENABLE;
    }
    if (PWM_GetITStatus(gk_DigitalInPwmChannel[num], PWM_IT_OI) == SET) {
        PWM_ClearITPendingBit(gk_DigitalInPwmChannel[num], PWM_IT_OI);
        g_frequency_calculation[num].start = DISABLE;
        g_frequency_calculation[num].end = DISABLE;
        g_frequency_calculation[num].old_capture = 0;
        g_frequency_calculation[num].new_capture = 0;
        g_frequency_calculation[num].count_capture = 0;
    }
    if (PWM_GetITStatus(gk_DigitalInPwmChannel[num], PWM_IT_CI) == SET) {
        PWM_ClearITPendingBit(gk_DigitalInPwmChannel[num], PWM_IT_CI);
        if (g_frequency_calculation[num].start == ENABLE) {
            g_frequency_calculation[num].start = DISABLE;
            g_frequency_calculation[num].end = ENABLE;
            g_frequency_calculation[num].old_capture = GetDigitalInFrequency(num);
            return;
        }
        if (g_frequency_calculation[num].end == ENABLE) {
            g_frequency_calculation[num].end = DISABLE;
            g_frequency_calculation[num].start = ENABLE;
            g_frequency_calculation[num].new_capture = GetDigitalInFrequency(num);
            g_frequency_calculation[num].count_capture = (g_frequency_calculation[num].new_capture - g_frequency_calculation[num].old_capture + 1) / 100;
            return;
        }
    }
}
