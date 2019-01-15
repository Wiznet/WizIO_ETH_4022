#include <stdint.h>
#include "dhcp.h"
#include "dhcp_cb.h"
#include "config_data.h"

void dhcp_assign()
{
    WIZIOPacket *value = GetWIZIOPacketPointer();
    wiz_NetInfo gWIZNETINFO;

    getIPfromDHCP(gWIZNETINFO.ip);
    getGWfromDHCP(gWIZNETINFO.gw);
    getSNfromDHCP(gWIZNETINFO.sn);
    getDNSfromDHCP(gWIZNETINFO.dns);

    GetWIZIOPacketValue(gWIZNETINFO.mac, value->network_info_common.mac, sizeof(gWIZNETINFO.mac[0]) * 6);
    SetWIZIOPacketValue(value->network_info_common.local_ip, gWIZNETINFO.ip, sizeof(value->network_info_common.local_ip));
    SetWIZIOPacketValue(value->network_info_common.gateway, gWIZNETINFO.gw, sizeof(value->network_info_common.gateway));
    SetWIZIOPacketValue(value->network_info_common.subnet, gWIZNETINFO.sn, sizeof(value->network_info_common.subnet));
    SetWIZIOPacketValue(value->network_info_common.dns, gWIZNETINFO.dns, sizeof(value->network_info_common.dns));
    if (value->options.dhcp_use) gWIZNETINFO.dhcp = NETINFO_DHCP;
    else gWIZNETINFO.dhcp = NETINFO_STATIC;

    ctlnetwork(CN_SET_NETINFO, (void*) &gWIZNETINFO);

//	display_Net_Info();
//	printf("DHCP LEASED TIME : %d sec. \r\n", getDHCPLeasetime());
}

void dhcp_conflict()
{
    // TODO
    ;
}

