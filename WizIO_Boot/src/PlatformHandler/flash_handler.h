#ifndef __FLASHHANDLER_H__
#define __FLASHHANDLER_H__

#include <stdint.h>

#define DAT0_START_ADDR     0x0003FE00
#define DAT1_START_ADDR     0x0003FF00
#define BLOCK_SIZE      	4096
#define SECT_SIZE       	256

#define FLASH_PAGE0_BASE	0x00000000
#define FLASH_CONFIG_PAGE	4
#define FLASH_PAGE_SIZE		0x100
#define FLASH_PAGE			512
#define FLASH_BOOT_PAGE		128//240//112					// 1 page 256
#define CONFIG_PAGE_ADDR	(0x00000000+(FLASH_PAGE_SIZE*508))	// Page 508,509,510,511	(W7500, the last page of 128kB on-chip flash, 1kB size)
#define FLASH_APP_PAGE		(FLASH_PAGE - FLASH_BOOT_PAGE - FLASH_CONFIG_PAGE)

int addr_to_page(uint32_t addr);
void erase_flash_page(uint32_t page_addr);
void erase_flash_block(uint32_t block_addr);
int write_flash(uint32_t addr, uint8_t *data, uint32_t data_len);
int read_flash(uint32_t addr, uint8_t *data, uint32_t data_len);
void save_data(uint8_t *data, uint32_t data_len, uint16_t block_number);

#endif
