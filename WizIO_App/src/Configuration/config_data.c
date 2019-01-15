#include <stdio.h>
#include <string.h>
#include "config_data.h"
#include "config_message.h"
#include "uart_handler.h"
#include "storage_handler.h"

static WIZIOPacket g_s2e_packet;

WIZIOPacket* GetWIZIOPacketPointer(void)
{
    return &g_s2e_packet;
}

void SetWIZIOPacketToFactoryValue(void)
{
    uint8_t i;

    g_s2e_packet.packet_size = sizeof(WIZIOPacket);
    g_s2e_packet.module_type[0] = 0x04;
    g_s2e_packet.module_type[1] = 0x00;
    g_s2e_packet.module_type[2] = 0x00;
    g_s2e_packet.fw_ver[0] = MAJOR_VER;
    g_s2e_packet.fw_ver[1] = MINOR_VER;
    g_s2e_packet.fw_ver[2] = MAINTENANCE_VER;

    //network common
    g_s2e_packet.network_info_common.local_ip[0] = 192;
    g_s2e_packet.network_info_common.local_ip[1] = 168;
    g_s2e_packet.network_info_common.local_ip[2] = 0;
    g_s2e_packet.network_info_common.local_ip[3] = 100;
    g_s2e_packet.network_info_common.gateway[0] = 192;
    g_s2e_packet.network_info_common.gateway[1] = 168;
    g_s2e_packet.network_info_common.gateway[2] = 0;
    g_s2e_packet.network_info_common.gateway[3] = 1;
    g_s2e_packet.network_info_common.subnet[0] = 255;
    g_s2e_packet.network_info_common.subnet[1] = 255;
    g_s2e_packet.network_info_common.subnet[2] = 255;
    g_s2e_packet.network_info_common.subnet[3] = 0;
    g_s2e_packet.network_info_common.dns[0] = 8;
    g_s2e_packet.network_info_common.dns[1] = 8;
    g_s2e_packet.network_info_common.dns[2] = 8;
    g_s2e_packet.network_info_common.dns[3] = 8;

    //mqtt
    memcpy(g_s2e_packet.mqtt_info.user, "WIZnet\0\0\0\0", 10);
    memcpy(g_s2e_packet.mqtt_info.pw, "WIZnet\0\0\0\0", 10);
    memcpy(g_s2e_packet.mqtt_info.publish_topic, "WIZnet\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 25);
    memcpy(g_s2e_packet.mqtt_info.subscribe_topic, "WIZnet\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 25);

    //working info
    g_s2e_packet.working_info.remote_ip[0] = 192;
    g_s2e_packet.working_info.remote_ip[1] = 168;
    g_s2e_packet.working_info.remote_ip[2] = 0;
    g_s2e_packet.working_info.remote_ip[3] = 2;
    g_s2e_packet.working_info.local_port = 5000;
    g_s2e_packet.working_info.remote_port = 5000;
    g_s2e_packet.working_info.mode = TCP_SERVER_MODE;
    g_s2e_packet.working_info.state = kNetDisconnect;

    //analog common
    g_s2e_packet.analog_in_common.filter = kNone;
    g_s2e_packet.analog_in_common.modbus_address = 0;

    //analog in
    for (i = 0; i < ANALOG_IN_CHANNEL_NUM; i++) {
        g_s2e_packet.analog_in[i].use = ENABLE;
        g_s2e_packet.analog_in[i].value = 0;
    }

    //digital in
    for (i = 0; i < DIGITAL_IN_CHANNEL_NUM; i++) {
        g_s2e_packet.digital_in[i].use = ENABLE;
        g_s2e_packet.digital_in[i].value = 0;
        g_s2e_packet.digital_in[i].mode = kDI;
        g_s2e_packet.digital_in[i].modbus_address = 10 + i;
    }

    //digital out
    for (i = 0; i < DIGITAL_OUT_CHANNEL_NUM; i++) {
        g_s2e_packet.digital_out[i].use = ENABLE;
        g_s2e_packet.digital_out[i].value = 0;
        g_s2e_packet.digital_out[i].mode = kDO;
        g_s2e_packet.digital_out[i].modbus_address = 20 + (i * 2);
        g_s2e_packet.digital_out[i].high_width = 50;
        g_s2e_packet.digital_out[i].low_width = 100;

    }

    //options
    memcpy(g_s2e_packet.options.module_name, "WizIO ETH-4022\0\0\0\0\0\0", 20);
    memcpy(g_s2e_packet.options.pw_setting, "WIZnet\0\0\0\0", 10);
    g_s2e_packet.options.dhcp_use = DISABLE;
    g_s2e_packet.options.dns_use = DISABLE;
    memcpy(g_s2e_packet.options.dns_domain_name, "wiznet.io\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 30);
    g_s2e_packet.options.reconnection = 1000;
    g_s2e_packet.options.transfer_interval = 1000;
    g_s2e_packet.options.separator = ',';
    g_s2e_packet.options.form = kRaw;
}

void LoadWIZIOPacketFromStorage(void)
{
    read_storage(1, &g_s2e_packet, sizeof(WIZIOPacket));
    if (g_s2e_packet.packet_size == 0x0000 || g_s2e_packet.packet_size == 0xFFFF) {
        SetWIZIOPacketToFactoryValue();
        write_storage(1, &g_s2e_packet, sizeof(WIZIOPacket));
    }

    g_s2e_packet.fw_ver[0] = MAJOR_VER;
    g_s2e_packet.fw_ver[1] = MINOR_VER;
    g_s2e_packet.fw_ver[2] = MAINTENANCE_VER;
}

void SaveWIZIOPacketToStorage(void)
{
    uint8_t state;

    state = g_s2e_packet.working_info.state;
    g_s2e_packet.working_info.state = 0;

    write_storage(1, &g_s2e_packet, sizeof(WIZIOPacket));
    g_s2e_packet.working_info.state = state;
}

void GetWIZIOPacketValue(void *dest, const void *src, uint16_t size)
{
    memcpy(dest, src, size);
}

void SetWIZIOPacketValue(void *dest, const void *value, const uint16_t size)
{
    memcpy(dest, value, size);
}

void SetWIZIOPacket(wiz_NetInfo *net)
{
    SetWIZIOPacketValue(g_s2e_packet.network_info_common.mac, net->mac, sizeof(g_s2e_packet.network_info_common.mac));
    SetWIZIOPacketValue(g_s2e_packet.network_info_common.local_ip, net->ip, sizeof(g_s2e_packet.network_info_common.local_ip));
    SetWIZIOPacketValue(g_s2e_packet.network_info_common.gateway, net->gw, sizeof(g_s2e_packet.network_info_common.gateway));
    SetWIZIOPacketValue(g_s2e_packet.network_info_common.subnet, net->sn, sizeof(g_s2e_packet.network_info_common.subnet));
    SetWIZIOPacketValue(g_s2e_packet.network_info_common.dns, net->dns, sizeof(g_s2e_packet.network_info_common.dns));
    if (net->dhcp == NETINFO_STATIC) g_s2e_packet.options.dhcp_use = 0;
    else g_s2e_packet.options.dhcp_use = 1;
}

void GetWIZIOPacket(wiz_NetInfo *net)
{
    GetWIZIOPacketValue(net->mac, g_s2e_packet.network_info_common.mac, sizeof(net->mac));
    GetWIZIOPacketValue(net->ip, g_s2e_packet.network_info_common.local_ip, sizeof(net->ip));
    GetWIZIOPacketValue(net->gw, g_s2e_packet.network_info_common.gateway, sizeof(net->gw));
    GetWIZIOPacketValue(net->sn, g_s2e_packet.network_info_common.subnet, sizeof(net->sn));
    GetWIZIOPacketValue(net->dns, g_s2e_packet.network_info_common.dns, sizeof(net->dns));
    if (g_s2e_packet.options.dhcp_use) net->dhcp = NETINFO_DHCP;
    else net->dhcp = NETINFO_STATIC;
}

void DisplayNetInfo(void)
{
    wiz_NetInfo gWIZNETINFO;

    ctlnetwork(CN_GET_NETINFO, (void*) &gWIZNETINFO);
    printf("[APP] MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n", gWIZNETINFO.mac[0], gWIZNETINFO.mac[1], gWIZNETINFO.mac[2], gWIZNETINFO.mac[3], gWIZNETINFO.mac[4], gWIZNETINFO.mac[5]);
    printf("[APP] IP: %d.%d.%d.%d\r\n", gWIZNETINFO.ip[0], gWIZNETINFO.ip[1], gWIZNETINFO.ip[2], gWIZNETINFO.ip[3]);
    printf("[APP] GW: %d.%d.%d.%d\r\n", gWIZNETINFO.gw[0], gWIZNETINFO.gw[1], gWIZNETINFO.gw[2], gWIZNETINFO.gw[3]);
    printf("[APP] SN: %d.%d.%d.%d\r\n", gWIZNETINFO.sn[0], gWIZNETINFO.sn[1], gWIZNETINFO.sn[2], gWIZNETINFO.sn[3]);
    printf("[APP] DNS: %d.%d.%d.%d\r\n", gWIZNETINFO.dns[0], gWIZNETINFO.dns[1], gWIZNETINFO.dns[2], gWIZNETINFO.dns[3]);
}

void ConfigurationMac(void)
{
    WIZIOPacket *value = GetWIZIOPacketPointer();
    setSHAR(value->network_info_common.mac);
}

void ConfigurationNet(void)
{
    WIZIOPacket *value = GetWIZIOPacketPointer();
    wiz_NetInfo gWIZNETINFO;

    /* wizchip netconf */
    GetWIZIOPacketValue(gWIZNETINFO.mac, value->network_info_common.mac, sizeof(gWIZNETINFO.mac[0]) * 6);
    GetWIZIOPacketValue(gWIZNETINFO.ip, value->network_info_common.local_ip, sizeof(gWIZNETINFO.ip[0]) * 4);
    GetWIZIOPacketValue(gWIZNETINFO.gw, value->network_info_common.gateway, sizeof(gWIZNETINFO.gw[0]) * 4);
    GetWIZIOPacketValue(gWIZNETINFO.sn, value->network_info_common.subnet, sizeof(gWIZNETINFO.sn[0]) * 4);
    GetWIZIOPacketValue(gWIZNETINFO.dns, value->network_info_common.dns, sizeof(gWIZNETINFO.dns));
    if (value->options.dhcp_use) gWIZNETINFO.dhcp = NETINFO_DHCP;
    else gWIZNETINFO.dhcp = NETINFO_STATIC;

    ctlnetwork(CN_SET_NETINFO, (void*) &gWIZNETINFO);
}

void SetDhcpMode(void)
{
    WIZIOPacket *value = GetWIZIOPacketPointer();

    value->options.dhcp_use = 1;
}

void SetStaticMode(void)
{
    WIZIOPacket *value = GetWIZIOPacketPointer();

    value->options.dhcp_use = 0;
}

void SetMac(uint8_t *mac)
{
    WIZIOPacket *value = GetWIZIOPacketPointer();

    memcpy(value->network_info_common.mac, mac, sizeof(value->network_info_common.mac));
}

char AsciiToNum(char ch)
{
    ch -= '0';
    if (ch > 9) ch -= 7;
    if (ch > 15) ch -= 0x20;
    return (ch);
}

uint8_t GetHex(uint8_t b0, uint8_t b1)
{
    uint8_t buf[2];
    buf[0] = b0;
    buf[1] = b1;
    buf[0] = AsciiToNum(buf[0]);
    buf[0] <<= 4;
    buf[0] += AsciiToNum(buf[1]);
    return (buf[0]);
}

