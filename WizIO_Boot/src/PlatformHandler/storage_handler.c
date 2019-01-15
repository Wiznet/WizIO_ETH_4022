#include <string.h>
#include "w7500x.h"
#include "flash_handler.h"
#include "storage_handler.h"

int read_storage(uint8_t isConfig, void *data, uint16_t size)
{
    uint32_t address;

    if (isConfig == 1) {
        address = (FLASH_PAGE_SIZE * 2) + CONFIG_PAGE_ADDR;
    } else {
        address = 0x00000000 + CONFIG_PAGE_ADDR;
    }

    return read_flash(address, data, size);
}

int write_storage(uint8_t isConfig, void *data, uint16_t size)
{
    uint32_t address;
    int ret;

    if (isConfig == 1) {
        address = (FLASH_PAGE_SIZE * 2) + CONFIG_PAGE_ADDR;  //256*2 +
    } else {
        address = 0x00000000 + CONFIG_PAGE_ADDR;
    }

    erase_flash_page(address);
    erase_flash_page(address + FLASH_PAGE_SIZE);

    ret = write_flash(address, data, size);

    return ret;
}
