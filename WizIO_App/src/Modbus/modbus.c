#include "modbus.h"
#include "digital_handler.h"

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

static void SetFuctionType(int fc);
static uint16_t ConvertByteToWord(uint8_t h, uint8_t l);

static void SetFuctionType(int fc)
{
    if (fc == 1) g_modbus_function_type = MB_FC_READ_COILS;
    if (fc == 4) g_modbus_function_type = MB_FC_READ_INPUT_REGISTERS;
    if (fc == 5) g_modbus_function_type = MB_FC_WRITE_COILS;
    if (fc == 6) g_modbus_function_type = MB_FC_WRITE_REGISTERS;
    if (fc == 15) g_modbus_function_type = MB_FC_WRITE_MULTIPLE_COILS;
    if (fc == 16) g_modbus_function_type = MB_FC_WRITE_MULTIPLE_REGISTERS;
}

static uint16_t ConvertByteToWord(uint8_t h, uint8_t l)
{
    return (h << 8) | l;
}

static int ReadCoilFunction(int start, uint8_t * buf)
{
    WIZIOPacket *value = GetWIZIOPacketPointer();
    int byte_data_length, coil_data_length, message_length;
    uint8_t i, j, coil_read_count = 0, illegal_count = 0;

    coil_data_length = ConvertByteToWord(buf[10], buf[11]);
    byte_data_length = coil_data_length / 8;

    if (byte_data_length * 8 < coil_data_length) byte_data_length++;

    /* Check request function */
    for (i = 0; i < MB_N_DIC; i++) {
        if (value->digital_in[i].use == ENABLE && value->digital_in[i].mode == kDI) {
            illegal_count++;
        }
    }
    if (illegal_count == 0) {
        buf[MB_TCP_FUNC] |= MB_FC_READ_COILS + 0x80;
        buf[MB_TCP_FUNC + 1] = MB_ERROR_ILLEGAL_FUNCTION_CODE;  //Illegal Function
        message_length = 10;
        return message_length;
    }

    /* Check request address */
    for (i = 0; i < MB_N_DIC; i++) {
        if ((value->digital_in[i].modbus_address >= start) && (value->digital_in[i].modbus_address <= (start + byte_data_length))) {
            illegal_count++;
        }
    }
    if (illegal_count == 0) {
        buf[MB_TCP_FUNC] |= MB_FC_READ_COILS + 0x80;
        buf[MB_TCP_FUNC + 1] = MB_ERROR_ILLEGAL_DATA_ADDRESS;  //Illegal Address
        message_length = 10;
        return message_length;
    } else {
        illegal_count = 0;
    }

    coil_data_length = byte_data_length * 8;
    buf[5] = byte_data_length + 3;  //Number of bytes after this one.
    buf[8] = byte_data_length;  //Number of bytes after this one (or number of bytes of data).

    for (i = 0; i < byte_data_length; i++) {
        for (j = 0; j < 8; j++) {
            if (value->digital_in[0].use == ENABLE && value->digital_in[0].modbus_address == start + coil_read_count && value->digital_in[0].mode == kDI) {
                bitWrite(buf[9 + i], j, g_digital_in_coils[0]);
            } else if (value->digital_in[1].use == ENABLE && value->digital_in[1].modbus_address == start + coil_read_count && value->digital_in[1].mode == kDI) {
                bitWrite(buf[9 + i], j, g_digital_in_coils[1]);
            } else {
                bitWrite(buf[9 + i], j, 0);
            }
            coil_read_count++;
        }
    }
    message_length = byte_data_length + 9;
    g_modbus_function_type = MB_FC_NONE;
    return message_length;
}

static int ReadInputRegisterFunction(int start, uint8_t * buf)
{
    WIZIOPacket *value = GetWIZIOPacketPointer();
    int word_data_length, byte_data_length, message_length;
    uint8_t hn, ln;
    uint8_t i, illegal_count = 0;
    uint16_t analog_address_temp[MB_N_AIR];

    for (i = 0; i < MB_N_AIR; i++) {
        analog_address_temp[i] = value->analog_in_common.modbus_address + i;
    }

    word_data_length = ConvertByteToWord(buf[10], buf[11]);

    /* Check request function */
    for (i = 0; i < MB_N_AIR; i++) {
        if (value->analog_in[i].use == ENABLE) {
            illegal_count++;
        }
    }
    for (i = 0; i < MB_N_DIR; i++) {
        if (value->digital_in[i].use == ENABLE && value->digital_in[i].mode != kDI) {
            illegal_count++;
        }
    }
    if (illegal_count == 0) {
        buf[MB_TCP_FUNC] |= MB_FC_READ_INPUT_REGISTERS + 0x80;
        buf[MB_TCP_FUNC + 1] = MB_ERROR_ILLEGAL_FUNCTION_CODE;  //Illegal Function
        message_length = 10;
        return message_length;
    }

    /* Check request address */
    for (i = 0; i < MB_N_AIR; i++) {
        if ((analog_address_temp[i] >= start) && (analog_address_temp[i] <= (start + word_data_length))) {
            illegal_count++;
        }
    }
    for (i = 0; i < MB_N_DIR; i++) {
        if ((value->digital_in[i].modbus_address >= start) && (value->digital_in[i].modbus_address <= (start + word_data_length))) {
            illegal_count++;
        }
    }
    if (illegal_count == 0) {
        buf[MB_TCP_FUNC] |= MB_FC_READ_INPUT_REGISTERS + 0x80;
        buf[MB_TCP_FUNC + 1] = MB_ERROR_ILLEGAL_DATA_ADDRESS;  //Illegal Address
        message_length = 10;
        return message_length;
    } else {
        illegal_count = 0;
    }

    byte_data_length = word_data_length * 2;

    buf[5] = byte_data_length + 3;  //Number of bytes after this one.
    buf[8] = byte_data_length;  //Number of bytes after this one (or number of bytes of data).

    for (int i = 0; i < word_data_length; i++) {
        if (value->analog_in[0].use == ENABLE && analog_address_temp[0] == start + i) {
            hn = g_analog_in_register[0] >> 8;
            ln = g_analog_in_register[0];
            buf[9 + i * 2] = hn;
            buf[10 + i * 2] = ln;
        } else if (value->analog_in[1].use == ENABLE && analog_address_temp[1] == start + i) {
            hn = g_analog_in_register[1] >> 8;
            ln = g_analog_in_register[1];
            buf[9 + i * 2] = hn;
            buf[10 + i * 2] = ln;
        } else if (value->analog_in[2].use == ENABLE && analog_address_temp[2] == start + i) {
            hn = g_analog_in_register[2] >> 8;
            ln = g_analog_in_register[2];
            buf[9 + i * 2] = hn;
            buf[10 + i * 2] = ln;
        } else if (value->analog_in[3].use == ENABLE && analog_address_temp[3] == start + i) {
            hn = g_analog_in_register[3] >> 8;
            ln = g_analog_in_register[3];
            buf[9 + i * 2] = hn;
            buf[10 + i * 2] = ln;
        } else if (value->digital_in[0].use == ENABLE && value->digital_in[0].modbus_address == start + i && value->digital_in[0].mode != kDI) {
            hn = g_digital_in_register[0] >> 8;
            ln = g_digital_in_register[0];
            buf[9 + i * 2] = hn;
            buf[10 + i * 2] = ln;
        } else if (value->digital_in[1].use == ENABLE && value->digital_in[1].modbus_address == start + i && value->digital_in[1].mode != kDI) {
            hn = g_digital_in_register[1] >> 8;
            ln = g_digital_in_register[1];
            buf[9 + i * 2] = hn;
            buf[10 + i * 2] = ln;
        } else {
            buf[9 + i * 2] = 0;
            buf[10 + i * 2] = 0;
        }
    }
    message_length = byte_data_length + 9;
    g_modbus_function_type = MB_FC_NONE;
    return message_length;
}

static int WriteCoilFunction(int start, uint8_t * buf)
{
    WIZIOPacket *value = GetWIZIOPacketPointer();
    int message_length;
    uint8_t i, illegal_count = 0;

    /* Check request function */
    for (i = 0; i < MB_N_DOC; i++) {
        if (value->digital_out[i].use == ENABLE && value->digital_out[i].mode == kDO) {
            illegal_count++;
        }
    }
    if (illegal_count == 0) {
        buf[MB_TCP_FUNC] |= MB_FC_WRITE_COILS + 0x80;
        buf[MB_TCP_FUNC + 1] = MB_ERROR_ILLEGAL_FUNCTION_CODE;  //Illegal Function
        message_length = 10;
        return message_length;
    }

    /* Check request address */
    for (i = 0; i < MB_N_DOC; i++) {
        if (value->digital_out[i].modbus_address == start) {
            illegal_count++;
        }
    }
    if (illegal_count == 0) {
        buf[MB_TCP_FUNC] |= MB_FC_WRITE_COILS + 0x80;
        buf[MB_TCP_FUNC + 1] = MB_ERROR_ILLEGAL_DATA_ADDRESS;  //Illegal Address
        message_length = 10;
        return message_length;
    } else {
        illegal_count = 0;
    }

    for (i = 0; i < MB_N_DOC; i++) {
        if (value->digital_out[i].use == ENABLE && value->digital_out[i].modbus_address == start && value->digital_out[i].mode == kDO) {
            if (ConvertByteToWord(buf[10], buf[11])) {
                SetDigitalOutHigh(i);
            } else {
                SetDigitalOutLow(i);
            }
        }
    }

    buf[5] = 6;  //Number of bytes after this one.
    message_length = 12;
    g_modbus_function_type = MB_FC_NONE;
    return message_length;
}

static int WriteRegisterFunction(int start, uint8_t * buf)
{
    WIZIOPacket *value = GetWIZIOPacketPointer();
    int message_length;
    uint8_t i, j, illegal_count = 0;
    uint16_t digital_address_temp[MB_N_DOR][2];
    uint8_t pwm_update_flag = 0;
    uint16_t write_reg_temp;

    for (i = 0; i < MB_N_DOR; i++) {
        for (j = 0; j < 2; j++) {
            digital_address_temp[i][j] = value->digital_out[i].modbus_address + j;
        }
    }

    /* Check request function */
    for (i = 0; i < MB_N_DOR; i++) {
        if (value->digital_out[i].use == ENABLE && value->digital_out[i].mode == kDOPulse) {
            illegal_count++;
        }
    }
    if (illegal_count == 0) {
        buf[MB_TCP_FUNC] |= MB_FC_WRITE_REGISTERS + 0x80;
        buf[MB_TCP_FUNC + 1] = MB_ERROR_ILLEGAL_FUNCTION_CODE;  //Illegal Function
        message_length = 10;
        return message_length;
    }

    /* Check request address */
    for (i = 0; i < MB_N_DOR; i++) {
        for (j = 0; j < 2; j++) {
            if (digital_address_temp[i][j] == start) {
                illegal_count++;
            }
        }
    }
    if (illegal_count == 0) {
        buf[MB_TCP_FUNC] |= MB_FC_WRITE_REGISTERS + 0x80;
        buf[MB_TCP_FUNC + 1] = MB_ERROR_ILLEGAL_DATA_ADDRESS;  //Illegal Address
        message_length = 10;
        return message_length;
    } else {
        illegal_count = 0;
    }

    for (i = 0; i < MB_N_DOR; i++) {
        for (j = 0; j < 2; j++) {
            if (value->digital_out[i].use == ENABLE && digital_address_temp[i][j] == start && value->digital_out[i].mode == kDOPulse) {
                write_reg_temp = ConvertByteToWord(buf[10], buf[11]);
                if (j == 0) {
                    if (value->digital_out[i].high_width != write_reg_temp) {
                        value->digital_out[i].high_width = write_reg_temp;
                        pwm_update_flag = 1;
                    }
                } else {
                    if (value->digital_out[i].low_width != write_reg_temp) {
                        value->digital_out[i].low_width = write_reg_temp;
                        pwm_update_flag = 1;
                    }
                }
            }
        }
        if (pwm_update_flag == 1) {
            pwm_update_flag = 0;
            PWM_Cmd(gk_DigitalOutPwmChannel[i], DISABLE);
            InitDigitalOutWithPwm(i, value->digital_out[i].high_width, value->digital_out[i].low_width);
        }
    }

    buf[5] = 6;  //Number of bytes after this one.
    message_length = 12;
    g_modbus_function_type = MB_FC_NONE;
    return message_length;
}

static int WriteMultipleCoilFunction(int start, uint8_t * buf)
{
    WIZIOPacket *value = GetWIZIOPacketPointer();
    int coil_data_length, message_length;
    uint8_t i, illegal_count = 0;
    uint8_t bit_read_temp;

    coil_data_length = ConvertByteToWord(buf[10], buf[11]);

    /* Check request function */
    for (i = 0; i < MB_N_DOC; i++) {
        if (value->digital_out[i].use == ENABLE && value->digital_out[i].mode == kDO) {
            illegal_count++;
        }
    }
    if (illegal_count == 0) {
        buf[MB_TCP_FUNC] |= MB_FC_WRITE_MULTIPLE_COILS + 0x80;
        buf[MB_TCP_FUNC + 1] = MB_ERROR_ILLEGAL_FUNCTION_CODE;  //Illegal Function
        message_length = 10;
        return message_length;
    }

    /* Check request address */
    for (i = 0; i < MB_N_DOC; i++) {
        if (value->digital_out[i].modbus_address == start) {
            illegal_count++;
        }
    }
    if (illegal_count == 0) {
        buf[MB_TCP_FUNC] |= MB_FC_WRITE_MULTIPLE_COILS + 0x80;
        buf[MB_TCP_FUNC + 1] = MB_ERROR_ILLEGAL_DATA_ADDRESS;  //Illegal Address
        message_length = 10;
        return message_length;
    } else {
        illegal_count = 0;
    }

    buf[5] = 6;

    for (i = 0; i < coil_data_length; i++) {
        bit_read_temp = bitRead(buf[13 + (i / 8)], i - ((i / 8) * 8));
        if (value->digital_out[0].use == ENABLE && value->digital_out[0].modbus_address == start + i && value->digital_out[0].mode == kDO) {
            if (bit_read_temp) {
                SetDigitalOutHigh(kDigitalOut1);
            } else {
                SetDigitalOutLow(kDigitalOut1);
            }
        } else if (value->digital_out[1].use == ENABLE && value->digital_out[1].modbus_address == start + i && value->digital_out[1].mode == kDO) {
            if (bit_read_temp) {
                SetDigitalOutHigh(kDigitalOut2);
            } else {
                SetDigitalOutLow(kDigitalOut2);
            }
        } else {

        }
    }
    message_length = 12;
    g_modbus_function_type = MB_FC_NONE;
    return message_length;
}

static int WriteMultipleRegisterFunction(int start, uint8_t * buf)
{
    WIZIOPacket *value = GetWIZIOPacketPointer();
    int word_data_length, message_length;
    uint8_t i, j, illegal_count = 0;
    uint16_t digital_address_temp[MB_N_DOR][2];
    uint16_t write_reg_temp;

    for (i = 0; i < MB_N_DOR; i++) {
        for (j = 0; j < 2; j++) {
            digital_address_temp[i][j] = value->digital_out[i].modbus_address + j;
        }
    }

    word_data_length = ConvertByteToWord(buf[10], buf[11]);

    /* Check request function */
    for (i = 0; i < MB_N_DOR; i++) {
        if (value->digital_out[i].use == ENABLE && value->digital_out[i].mode == kDOPulse) {
            illegal_count++;
        }
    }
    if (illegal_count == 0) {
        buf[MB_TCP_FUNC] |= MB_FC_WRITE_MULTIPLE_REGISTERS + 0x80;
        buf[MB_TCP_FUNC + 1] = MB_ERROR_ILLEGAL_FUNCTION_CODE;  //Illegal Function
        message_length = 10;
        return message_length;
    }

    /* Check request address */
    for (i = 0; i < MB_N_DOR; i++) {
        for (j = 0; j < 2; j++) {
            if (digital_address_temp[i][j] >= start && digital_address_temp[i][j] <= start + word_data_length) {
                illegal_count++;
            }
        }
    }
    if (illegal_count == 0) {
        buf[MB_TCP_FUNC] |= MB_FC_WRITE_MULTIPLE_REGISTERS + 0x80;
        buf[MB_TCP_FUNC + 1] = MB_ERROR_ILLEGAL_DATA_ADDRESS;  //Illegal Address
        message_length = 10;
        return message_length;
    } else {
        illegal_count = 0;
    }

    for (i = 0; i < word_data_length; i++) {
        write_reg_temp = ConvertByteToWord(buf[13 + i * 2], buf[14 + i * 2]);
        if (value->digital_out[0].use == ENABLE && digital_address_temp[0][0] == start + i && value->digital_out[0].mode == kDOPulse) {
            if (value->digital_out[0].high_width != write_reg_temp) {
                value->digital_out[0].high_width = write_reg_temp;
                PWM_Cmd(gk_DigitalOutPwmChannel[0], DISABLE);
                InitDigitalOutWithPwm(0, value->digital_out[0].high_width, value->digital_out[0].low_width);
            }
        } else if (value->digital_out[0].use == ENABLE && digital_address_temp[0][1] == start + i && value->digital_out[0].mode == kDOPulse) {
            if (value->digital_out[0].low_width != write_reg_temp) {
                value->digital_out[0].low_width = write_reg_temp;
                PWM_Cmd(gk_DigitalOutPwmChannel[0], DISABLE);
                InitDigitalOutWithPwm(0, value->digital_out[0].high_width, value->digital_out[0].low_width);
            }
        } else if (value->digital_out[1].use == ENABLE && digital_address_temp[1][0] == start + i && value->digital_out[1].mode == kDOPulse) {
            if (value->digital_out[1].high_width != write_reg_temp) {
                value->digital_out[1].high_width = write_reg_temp;
                PWM_Cmd(gk_DigitalOutPwmChannel[1], DISABLE);
                InitDigitalOutWithPwm(1, value->digital_out[1].high_width, value->digital_out[1].low_width);
            }
        } else if (value->digital_out[1].use == ENABLE && digital_address_temp[1][1] == start + i && value->digital_out[1].mode == kDOPulse) {
            if (value->digital_out[1].low_width != write_reg_temp) {
                value->digital_out[1].low_width = write_reg_temp;
                PWM_Cmd(gk_DigitalOutPwmChannel[1], DISABLE);
                InitDigitalOutWithPwm(1, value->digital_out[1].high_width, value->digital_out[1].low_width);
            }
        }

    }

    buf[5] = 6;  //Number of bytes after this one.
    message_length = 12;
    g_modbus_function_type = MB_FC_NONE;
    return message_length;
}

int ModbusSlave(uint8_t * buf)
{
    int start;
    uint16_t protocol_id;

    protocol_id = ConvertByteToWord(buf[MB_TCP_PID1], buf[MB_TCP_PID2]);

    if (protocol_id != MB_TCP_PROTOCOL_ID) {
        return 0;
    }

    SetFuctionType(buf[MB_TCP_FUNC]);
    start = ConvertByteToWord(buf[8], buf[9]);

    switch (g_modbus_function_type)
    {
        case MB_FC_READ_COILS:
            return ReadCoilFunction(start, buf);
            break;
        case MB_FC_READ_INPUT_REGISTERS:
            return ReadInputRegisterFunction(start, buf);
            break;
        case MB_FC_WRITE_COILS:
            return WriteCoilFunction(start, buf);
            break;
        case MB_FC_WRITE_REGISTERS:
            return WriteRegisterFunction(start, buf);
            break;
        case MB_FC_WRITE_MULTIPLE_COILS:
            return WriteMultipleCoilFunction(start, buf);
            break;
        case MB_FC_WRITE_MULTIPLE_REGISTERS:
            return WriteMultipleRegisterFunction(start, buf);
            break;
        default:
            break;
    }

    return 0;
}
