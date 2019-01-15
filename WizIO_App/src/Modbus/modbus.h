#ifndef MODBUS_MODBUSTCP_H_
#define MODBUS_MODBUSTCP_H_

#include <stdint.h>
#include <stdbool.h>
#include "config_data.h"
#include "common.h"

#define MB_TCP_TID1         0
#define MB_TCP_TID2         1
#define MB_TCP_PID1         2
#define MB_TCP_PID2         3
#define MB_TCP_LEN          4
#define MB_TCP_UID          6
#define MB_TCP_FUNC         7

#define MB_UDP_CRC16_SIZE   2

#define MB_TCP_PROTOCOL_ID  0   /* 0 = Modbus Protocol */

#define MB_N_AIR            ANALOG_IN_CHANNEL_NUM
#define MB_N_DIR            DIGITAL_IN_CHANNEL_NUM
#define MB_N_DIC            DIGITAL_IN_CHANNEL_NUM
#define MB_N_DOC            DIGITAL_OUT_CHANNEL_NUM
#define MB_N_DOR            DIGITAL_OUT_CHANNEL_NUM
#define MB_PORT             502

typedef enum
{
    MB_FC_NONE = 0,
    MB_FC_READ_COILS = 1,
    MB_FC_READ_INPUT_REGISTERS = 4,
    MB_FC_WRITE_COILS = 5,
    MB_FC_WRITE_REGISTERS = 6,
    MB_FC_WRITE_MULTIPLE_COILS = 15,
    MB_FC_WRITE_MULTIPLE_REGISTERS = 16
} ModbusFunctionType;

typedef enum
{
    MB_ERROR_ILLEGAL_FUNCTION_CODE = 1,
    MB_ERROR_ILLEGAL_DATA_ADDRESS = 2,
    MB_ERROR_ILLEGAL_DATA_VALUE = 3
} ModbusExceptionType;

uint8_t g_modbus_function_type;
uint16_t g_analog_in_register[MB_N_AIR];
uint16_t g_digital_in_register[MB_N_DIR];
uint8_t g_digital_in_coils[MB_N_DIC];

int ModbusSlave(uint8_t * buf);

#endif /* MODBUS_MODBUSTCP_H_ */
