#ifndef CRC_H
#define CRC_H

#include <stddef.h>
#include <stdint.h>

/* Bitwise (table-free) CRC routines. A NULL data pointer is treated as empty input. */

uint8_t  crc8(const uint8_t *data, size_t len);          /* CRC-8/SMBUS: poly 0x07, init 0x00 */
uint16_t crc16_ccitt(const uint8_t *data, size_t len);   /* CRC-16/CCITT-FALSE: poly 0x1021, init 0xFFFF */

uint32_t crc32_init(void);                                /* CRC-32 (IEEE 802.3), incremental use */
uint32_t crc32_update(uint32_t crc, const uint8_t *data, size_t len);
uint32_t crc32_final(uint32_t crc);
uint32_t crc32(const uint8_t *data, size_t len);          /* one-shot */

#endif
