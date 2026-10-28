/* Requirements-based tests. Each check names the requirement (see README.md) it verifies. */
#include <stdio.h>
#include <string.h>
#include "crc.h"

static int tests_run = 0;
static int tests_failed = 0;

#define CHECK(req, cond)                                                     \
    do {                                                                     \
        tests_run++;                                                         \
        if (!(cond)) {                                                       \
            tests_failed++;                                                  \
            printf("FAIL [%s] %s:%d: %s\n", req, __FILE__, __LINE__, #cond); \
        }                                                                    \
    } while (0)

static const uint8_t CHECK_STR[9] = {'1','2','3','4','5','6','7','8','9'};

static void test_known_vectors(void)
{
    CHECK("CRC-001", crc8(CHECK_STR, 9) == 0xF4);
    CHECK("CRC-002", crc16_ccitt(CHECK_STR, 9) == 0x29B1);
    CHECK("CRC-003", crc32(CHECK_STR, 9) == 0xCBF43926u);
}

static void test_empty_input(void)
{
    CHECK("CRC-004", crc8(CHECK_STR, 0) == 0x00);
    CHECK("CRC-004", crc16_ccitt(CHECK_STR, 0) == 0xFFFF);
    CHECK("CRC-004", crc32(CHECK_STR, 0) == 0x00000000u);
    CHECK("CRC-004", crc8(NULL, 5) == 0x00);
    CHECK("CRC-004", crc16_ccitt(NULL, 5) == 0xFFFF);
    CHECK("CRC-004", crc32(NULL, 5) == 0x00000000u);
}

static void test_incremental(void)
{
    size_t split;
    int ok = 1;
    for (split = 0; split <= 9; split++) {
        uint32_t c = crc32_init();
        c = crc32_update(c, CHECK_STR, split);
        c = crc32_update(c, CHECK_STR + split, 9 - split);
        ok &= (crc32_final(c) == crc32(CHECK_STR, 9));
    }
    CHECK("CRC-005", ok);
}

static void test_bit_flip_detection(void)
{
    uint8_t buf[16];
    size_t i;
    int bit, ok8 = 1, ok16 = 1, ok32 = 1;
    uint8_t  base8;
    uint16_t base16;
    uint32_t base32;
    for (i = 0; i < sizeof buf; i++) {
        buf[i] = (uint8_t)(i * 17u + 3u);
    }
    base8 = crc8(buf, sizeof buf);
    base16 = crc16_ccitt(buf, sizeof buf);
    base32 = crc32(buf, sizeof buf);
    for (i = 0; i < sizeof buf; i++) {
        for (bit = 0; bit < 8; bit++) {
            buf[i] ^= (uint8_t)(1u << bit);
            ok8 &= (crc8(buf, sizeof buf) != base8);
            ok16 &= (crc16_ccitt(buf, sizeof buf) != base16);
            ok32 &= (crc32(buf, sizeof buf) != base32);
            buf[i] ^= (uint8_t)(1u << bit);
        }
    }
    CHECK("CRC-006", ok8);
    CHECK("CRC-006", ok16);
    CHECK("CRC-006", ok32);
}

int main(void)
{
    test_known_vectors();
    test_empty_input();
    test_incremental();
    test_bit_flip_detection();
    printf("%d checks, %d failed\n", tests_run, tests_failed);
    return tests_failed == 0 ? 0 : 1;
}
