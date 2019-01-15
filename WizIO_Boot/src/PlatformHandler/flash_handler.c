#include <string.h>
#include <stdio.h>
#include "w7500x.h"
#include "w7500x_flash.h"

#include "tftp.h"
#include "flash_handler.h"
#include "common.h"

int addr_to_page(uint32_t addr)
{
    uint32_t mask = 0;

    mask = APP_BASE - FLASH_PAGE0_BASE - 1;

    addr &= mask;

    return (addr / FLASH_PAGE_SIZE);
}

void erase_flash_page(uint32_t page_addr)
{
    __disable_irq();
    FLASH_IAP(IAP_ERAS_SECT, page_addr, 0, 0);
    __enable_irq();
}

void erase_flash_block(uint32_t block_addr)
{
    __disable_irq();
    FLASH_IAP(IAP_ERAS_BLCK, block_addr, 0, 0);
    __enable_irq();
}

int write_flash(uint32_t addr, uint8_t *data, uint32_t data_len)
{
    __disable_irq();
    FLASH_IAP(IAP_PROG, addr, (unsigned char*) data, data_len);
    __enable_irq();

    return data_len;
}

int read_flash(uint32_t addr, uint8_t *data, uint32_t data_len)
{
    uint32_t i;

    for (i = 0; i < data_len; i++) {
        data[i] = *(uint8_t *) (addr + i);
    }

    return i;
}

/*
 * TFTP Dependency
 */
static uint8_t *g_write_point = (uint8_t *) APP_BASE;
void save_data(uint8_t *data, uint32_t data_len, uint16_t block_number)
{
    static uint32_t cnt = 0;
    int i;

    if (block_number == 1) {
        for (i = 0; i < 23; i++) {
            erase_flash_block(APP_BASE + (BLOCK_SIZE * i));
        }
    }

    //DBG_PRINT(INFO_DBG, "#");
    cnt += data_len;
    write_flash((uint32_t) g_write_point, data, data_len);
    g_write_point += data_len;
}

