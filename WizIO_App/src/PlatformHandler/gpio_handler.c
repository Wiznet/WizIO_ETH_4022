#include "w7500x_gpio.h"
#include "config_data.h"
#include "gpio_handler.h"
#include "timer_handler.h"

GPIO_TypeDef* gk_LedGpioPort[LED_NUM] = { LED1_PORT, LED2_PORT, LED3_PORT };
const uint16_t gk_LedGpioPin[LED_NUM] = { LED1_PIN, LED2_PIN, LED3_PIN };

void InitLed(LedNum num)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = gk_LedGpioPin[num];
    GPIO_InitStructure.GPIO_Direction = GPIO_Direction_OUT;
    GPIO_InitStructure.GPIO_Pad = GPIO_OpenDrainEnable | GPIO_HighDrivingStrength | GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_AF = PAD_AF1;

    GPIO_Init(gk_LedGpioPort[num], &GPIO_InitStructure);

    delay_cnt(10000);
}

void OnLed(LedNum num)
{
    GPIO_ResetBits(gk_LedGpioPort[num], gk_LedGpioPin[num]);
}

void OffLed(LedNum num)
{
    GPIO_SetBits(gk_LedGpioPort[num], gk_LedGpioPin[num]);
}

void ToggleLed(LedNum num)
{
    gk_LedGpioPort[num]->DATAOUT ^= gk_LedGpioPin[num];
}

uint32_t GetLEDStatus(LedNum num)
{
    return GPIO_ReadOutputDataBit(gk_LedGpioPort[num], gk_LedGpioPin[num]);
}

void InitBootPin(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = BOOT_PIN;
    GPIO_InitStructure.GPIO_Direction = GPIO_Direction_IN;
    GPIO_InitStructure.GPIO_AF = BOOT_AF;

    GPIO_Init(BOOT_PORT, &GPIO_InitStructure);
}

BitAction GetBootPinStatus(void)
{
    return GPIO_ReadInputDataBit(BOOT_PORT, BOOT_PIN);
}

void InitBuzzerPin(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
    GPIO_InitStructure.GPIO_Direction = GPIO_Direction_OUT;
    GPIO_InitStructure.GPIO_Pad = GPIO_OpenDrainDisable | GPIO_HighDrivingStrength | GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_AF = BUZZER_AF;

    GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);
}

void OnBuzzer(void)
{
    GPIO_SetBits(BUZZER_PORT, BUZZER_PIN);
}

void OffBuzzer(void)
{
    GPIO_ResetBits(BUZZER_PORT, BUZZER_PIN);
}

void ToggleBuzzer(void)
{
    BUZZER_PORT->DATAOUT ^= BUZZER_PIN;
}

#if 0
void InitFactoryResetPin(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_ITInitTypeDef GPIO_ITInitStructure;

    //Configure the Boot trigger pin
    GPIO_InitStructure.GPIO_Pin = FACT_PIN;
    GPIO_InitStructure.GPIO_Direction = GPIO_Direction_IN;
    GPIO_InitStructure.GPIO_Pad = GPIO_InputBufferDisable;
    GPIO_InitStructure.GPIO_AF = FACT_GPIO_AF;
    GPIO_Init(FACT_GPIO_PORT, &GPIO_InitStructure);

    GPIO_ITInitStructure.GPIO_IT_Pin = FACT_PIN;
    GPIO_ITInitStructure.GPIO_IT_Polarity = GPIO_IT_HighRising;
    GPIO_ITInitStructure.GPIO_IT_Type = GPIO_IT_Edge;
    GPIO_IT_Init(FACT_GPIO_PORT, &GPIO_ITInitStructure);
    GPIO_ITConfig(FACT_GPIO_PORT, FACT_PIN, ENABLE);
}
uint8_t GetFactoryResetPinStatus(void)
{
    return GPIO_ReadInputDataBit(FACT_GPIO_PORT, FACT_PIN);
}
#endif
