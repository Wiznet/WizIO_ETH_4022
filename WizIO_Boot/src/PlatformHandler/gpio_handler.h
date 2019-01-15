#ifndef __GPIOHANDLER_H__
#define __GPIOHANDLER_H__

#include <stdint.h>
#include "w7500x.h"
#include "common.h"

#define LED_NUM     3

#define LED1_PORT   GPIOC
#define LED1_PIN    GPIO_Pin_12
#define LED1_AF     PAD_AF1

#define LED2_PORT   GPIOC
#define LED2_PIN    GPIO_Pin_13
#define LED2_AF     PAD_AF1

#define LED3_PORT   GPIOC
#define LED3_PIN    GPIO_Pin_14
#define LED3_AF     PAD_AF1

#define BOOT_PORT   GPIOA
#define BOOT_PIN    GPIO_Pin_1
#define BOOT_AF     PAD_AF1

#define BUZZER_PORT GPIOC
#define BUZZER_PIN  GPIO_Pin_15
#define BUZZER_AF   PAD_AF1

typedef enum
{
    kLED1 = 0,
    kLED2,
    kLED3
} LedNum;

void InitLed(LedNum led);
void OnLed(LedNum led);
void OffLed(LedNum led);
void ToggleLed(LedNum led);
uint32_t GetLEDStatus(LedNum led);

void InitBootPin(void);
BitAction GetBootPinStatus(void);

void InitBuzzerPin(void);
void OnBuzzer(void);
void OffBuzzer(void);
void ToggleBuzzer(void);

#if 0
void InitFactoryResetPin(void);
uint8_t GetFactoryResetPinStatus(void);
#endif

#endif
