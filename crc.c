#include "crc.h"

uint8_t crc8(const uint8_t *data, size_t len)
{
    uint8_t crc = 0x00;
    size_t i;
    int bit;
    if (data == NULL) {
        return crc;
    }
    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (bit = 0; bit < 8; bit++) {
            crc = (uint8_t)((crc & 0x80u) ? (uint8_t)((crc << 1) ^ 0x07u) : (uint8_t)(crc << 1));
        }
    }
    return crc;
}

uint16_t crc16_ccitt(const uint8_t *data, size_t len)
{
    uint16_t crc = 0xFFFFu;
    size_t i;
    int bit;
    if (data == NULL) {
        return crc;
    }
    for (i = 0; i < len; i++) {
        crc ^= (uint16_t)((uint16_t)data[i] << 8);
        for (bit = 0; bit < 8; bit++) {
            crc = (uint16_t)((crc & 0x8000u) ? (uint16_t)((crc << 1) ^ 0x1021u) : (uint16_t)(crc << 1));
        }
    }
    return crc;
}

uint32_t crc32_init(void)
{
    return 0xFFFFFFFFu;
}

uint32_t crc32_update(uint32_t crc, const uint8_t *data, size_t len)
{
    size_t i;
    int bit;
    if (data == NULL) {
        return crc;
    }
    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (bit = 0; bit < 8; bit++) {
            crc = (crc & 1u) ? ((crc >> 1) ^ 0xEDB88320u) : (crc >> 1);
        }
    }
    return crc;
}

uint32_t crc32_final(uint32_t crc)
{
    return crc ^ 0xFFFFFFFFu;
}

uint32_t crc32(const uint8_t *data, size_t len)
{
    return crc32_final(crc32_update(crc32_init(), data, len));
}
