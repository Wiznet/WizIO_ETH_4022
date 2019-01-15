#ifndef __DIGITALHANDLER_H__
#define __DIGITALHANDLER_H__

#include <stdint.h>
#include "w7500x.h"
#include "common.h"

#define DI_NUM          DIGITAL_IN_CHANNEL_NUM

#define DI1_PORT        GPIOC
#define DI1_PIN         GPIO_Pin_2
#define DI1_PIN_SOURCE  GPIO_PinSource2
#define DI1_AF          PAD_AF1
#define DI1_PWM_AF      PAD_AF2
#define DI1_PWM_CH      PWM2
#define DI1_IRQ         PWM2_IRQn

#define DI2_PORT        GPIOC
#define DI2_PIN         GPIO_Pin_3
#define DI2_PIN_SOURCE  GPIO_PinSource3
#define DI2_AF          PAD_AF1
#define DI2_PWM_AF      PAD_AF2
#define DI2_PWM_CH      PWM3
#define DI2_IRQ         PWM3_IRQn

#define DO_NUM          DIGITAL_OUT_CHANNEL_NUM

#define DO1_PORT        GPIOC
#define DO1_PIN         GPIO_Pin_0
#define DO1_PIN_SOURCE  GPIO_PinSource0
#define DO1_AF          PAD_AF1
#define DO1_PWM_AF      PAD_AF2
#define DO1_PWM_CH      PWM0

#define DO2_PORT        GPIOC
#define DO2_PIN         GPIO_Pin_1
#define DO2_PIN_SOURCE  GPIO_PinSource1
#define DO2_AF          PAD_AF1
#define DO2_PWM_AF      PAD_AF2
#define DO2_PWM_CH      PWM1

extern PWM_TypeDef* gk_DigitalOutPwmChannel[DO_NUM];
extern PWM_TypeDef* gk_DigitalInPwmChannel[DI_NUM];

struct FrequencyCalculation
{
    uint8_t start;
    uint8_t end;
    uint32_t old_capture;
    uint32_t new_capture;
    uint32_t count_capture;
}__attribute__((packed));

typedef enum
{
    kDigitalIn1 = 0,
    kDigitalIn2,
    kDigitalIn3,
    kDigitalIn4,
    kDigitalIn5,
    kDigitalIn6,
    kDigitalIn7,
    kDigitalIn8
} DigitalInNum;

typedef enum
{
    kDigitalOut1 = 0,
    kDigitalOut2,
    kDigitalOut3,
    kDigitalOut4,
    kDigitalOut5,
    kDigitalOut6,
    kDigitalOut7,
    kDigitalOut8
} DigitalOutNum;

struct FrequencyCalculation g_frequency_calculation[DI_NUM];

void InitDigitalIn(void);
void InitDigitalInWithGpio(DigitalInNum num);
void InitDigitalInWithPwm(DigitalInNum num, uint8_t mode);
uint32_t GetDigitalInCounter(DigitalInNum num);
uint32_t GetDigitalInFrequency(DigitalInNum num);
uint32_t GetDigitalInStatus(DigitalInNum num);
void UpdateDigitalInValue(DigitalInNum num);

void InitDigitalOut(void);
void InitDigitalOutWithGpio(DigitalOutNum num);
void InitDigitalOutWithPwm(DigitalOutNum num, uint16_t high_width, uint16_t low_width);
void SetDigitalOutHigh(DigitalOutNum num);
void SetDigitalOutLow(DigitalOutNum num);
uint32_t GetDigitalOutStatus(DigitalOutNum num);
void UpdateDigitalOutValue(DigitalOutNum num);

void PwmIRQHandler(DigitalInNum num);

#endif /* __DIGITALHANDLER_H__ */
