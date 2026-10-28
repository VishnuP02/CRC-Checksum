# CRC-Checksum

Table-free CRC-8, CRC-16, and CRC-32 routines in C99, verified against published check values and with structural coverage analysis.

## Requirements

| ID | Requirement |
|----|-------------|
| CRC-001 | `crc8` (CRC-8/SMBUS) shall return 0xF4 for the ASCII input "123456789". |
| CRC-002 | `crc16_ccitt` (CRC-16/CCITT-FALSE) shall return 0x29B1 for "123456789". |
| CRC-003 | `crc32` (IEEE 802.3) shall return 0xCBF43926 for "123456789". |
| CRC-004 | Each routine shall return its defined empty-input value for zero-length input and for a NULL data pointer. |
| CRC-005 | Incremental CRC-32 over any split of the input shall equal the one-shot result. |
| CRC-006 | Each routine shall detect every single-bit error in a 16-byte message. |

Every check in `test_crc.c` is tagged with the requirement it verifies.

## Build and test

    make test        # build with -Wall -Wextra -Wpedantic -Werror and run the tests
    make coverage    # rebuild with gcov instrumentation and print line/branch coverage

## Results

- 13 checks, 0 failures
- gcov: 100% of lines (32) and 100% of branches (22) in `crc.c`
