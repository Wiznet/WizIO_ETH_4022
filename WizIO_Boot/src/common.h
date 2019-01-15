#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>

#define MAJOR_VER               101
#define MINOR_VER               0
#define MAINTENANCE_VER         0

#define ANALOG_IN_CHANNEL_NUM   4
#define ANALOG_OUT_CHANNEL_NUM  0
#define DIGITAL_IN_CHANNEL_NUM  2
#define DIGITAL_OUT_CHANNEL_NUM 2

#define SOCK_DATA               0
#define SOCK_TFTP               1
#define SOCK_CONFIG             2
#define SOCK_DHCP               3
#define SOCK_DNS                4
#define SOCK_TEST               5

#define APP_BASE                0x00008000          // Boot Size 32K
#define WORK_BUF_SIZE           2048

#define DEVICE_BOOT_ADDR        0x00000000
#define DEVICE_BOOT_SIZE        (32*1024)
#define DEVICE_APP_MAIN_ADDR    (DEVICE_BOOT_ADDR + DEVICE_BOOT_SIZE)

#define WIZWIKI_W7500           0
#define WIZIO_ETH4022           1

#define BOARD                   WIZIO_ETH4022

#endif
