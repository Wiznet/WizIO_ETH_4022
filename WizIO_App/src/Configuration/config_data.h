#ifndef __CONFIGDATA_H__
#define __CONFIGDATA_H__

#include <stdint.h>
#include "wizchip_conf.h"
#include "common.h"

#define TCP_CLIENT_MODE		0
#define TCP_SERVER_MODE		1
#define UDP_MODE			2
#define MQTT_MODE			3
#define MODBUS_TCP_MODE     4
#define MODBUS_UDP_MODE     5

enum DataFormat
{
    kRaw = 0,
    kJson
};

enum AnalogFilter
{
    kNone = 0,
    kAverage
};

enum NetState
{
    kNetDisconnect = 0,
    kNetConnect,
    kNetUdp
};

enum DigitalOutMode
{
    kDO = 0,
    kDOPulse
};

enum DigitalInMode
{
    kDI = 0,
    kDIHighCounter,
    kDILowCounter,
    kDIFrequency,
};

struct __network_info_common
{
    uint8_t mac[6];
    uint8_t local_ip[4];
    uint8_t gateway[4];
    uint8_t subnet[4];
    uint8_t dns[4];
}__attribute__((packed));

struct __mqtt_info
{
    char user[10];
    char pw[10];
    char publish_topic[25];
    char subscribe_topic[25];
}__attribute__((packed));

struct __working_info
{
    uint8_t remote_ip[4];			// Must Be 4byte Alignment

    uint16_t local_port;
    uint16_t remote_port;

    uint8_t mode;
    uint8_t state;
}__attribute__((packed));

struct __analog_in_common
{
    uint8_t filter;
    uint16_t modbus_address;
}__attribute__((packed));

struct __analog_in
{
    uint8_t use;
    uint16_t value;
}__attribute__((packed));

struct __digital_in
{
    uint8_t use;
    uint16_t value;

    uint8_t mode;
    uint16_t modbus_address;
}__attribute__((packed));

struct __digital_out
{
    uint8_t use;
    uint16_t value;

    uint8_t mode;
    uint16_t modbus_address;

    uint16_t high_width;
    uint16_t low_width;
}__attribute__((packed));

struct __options
{
    char module_name[20];
    char pw_setting[10];

    uint8_t dhcp_use;
    uint8_t dns_use;
    char dns_domain_name[30];

    uint16_t reconnection;
    uint16_t transfer_interval;

    char separator;
    uint8_t form;
}__attribute__((packed));

typedef struct __WIZIOPacket
{
    uint16_t packet_size;
    uint8_t module_type[3];
    uint8_t fw_ver[3];

    struct __network_info_common network_info_common;
    struct __mqtt_info mqtt_info;
    struct __working_info working_info;
    struct __analog_in_common analog_in_common;
    struct __analog_in analog_in[ANALOG_IN_CHANNEL_NUM];
    struct __digital_in digital_in[DIGITAL_IN_CHANNEL_NUM];
    struct __digital_out digital_out[DIGITAL_OUT_CHANNEL_NUM];
    struct __options options;
}__attribute__((packed)) WIZIOPacket;

WIZIOPacket* GetWIZIOPacketPointer(void);
void SetWIZIOPacketToFactoryValue(void);
void LoadWIZIOPacketFromStorage(void);
void SaveWIZIOPacketToStorage(void);
void GetWIZIOPacketValue(void *dest, const void *src, uint16_t size);
void SetWIZIOPacketValue(void *dest, const void *value, const uint16_t size);
void SetWIZIOPacket(wiz_NetInfo *net);
void GetWIZIOPacket(wiz_NetInfo *net);

void DisplayNetInfo(void);
void ConfigurationMac(void);
void ConfigurationNet(void);
void SetDhcpMode(void);
void SetStaticMode(void);
void SetMac(uint8_t *mac);

#endif /* __CONFIGDATA_H__ */
