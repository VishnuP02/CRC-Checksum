CC      ?= gcc
CFLAGS  = -std=c99 -Wall -Wextra -Wpedantic -Werror -O0

all: test_crc

test_crc: crc.c test_crc.c crc.h
	$(CC) $(CFLAGS) -o $@ crc.c test_crc.c

test: test_crc
	./test_crc

coverage: clean
	$(CC) $(CFLAGS) --coverage -c crc.c -o crc.o
	$(CC) $(CFLAGS) -c test_crc.c -o test_crc.o
	$(CC) --coverage -o test_crc crc.o test_crc.o
	./test_crc
	gcov -b crc.c

clean:
	rm -f test_crc *.o *.gcda *.gcno *.gcov
