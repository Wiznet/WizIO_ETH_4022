#ifndef __ANALOGHANDLER_H__
#define __ANALOGHANDLER_H__

#include <stdint.h>
#include "w7500x.h"
#include "common.h"

#define AI_NUM      ANALOG_IN_CHANNEL_NUM

#define CS_PORT     GPIOA
#define CS_PIN      GPIO_Pin_5
#define CS_AF       PAD_AF1

typedef enum
{
    kAnalogIn1 = 0,
    kAnalogIn2,
    kAnalogIn3,
    kAnalogIn4,
    kAnalogIn5,
    kAnalogIn6,
    kAnalogIn7,
    kAnalogIn8
} AnalogInNum;

typedef enum
{
    MCP3204,
    MCP3208
} Type;

typedef enum
{
    SINGLE,
    DIFFERENTIAL
} InputType;

void InitMCP320xSpiInterface(void);
void InitMCP320xType(InputType read_type, Type mcp_type);
uint16_t ReadMCP320x(uint8_t channel);
void InitAnalogInFilterValue(void);
void UpdateAnalogInValue(AnalogInNum num);
#endif /* __ANALOGHANDLER_H__ */
