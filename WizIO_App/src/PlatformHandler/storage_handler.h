#ifndef STORAGEHANDLER_H_
#define STORAGEHANDLER_H_

#include <stdint.h>

#define EEPROM_BLOCK_SIZE       	256
#define EEPROM_BLOCK_COUNT       	4
#define EEPROM_PAGE_SIZE       		16

int read_storage(uint8_t isConfig, void *data, uint16_t size);
int write_storage(uint8_t isConfig, void *data, uint16_t size);

#endif /* STORAGEHANDLER_H_ */
