.PHONY: all tests clean
all:
	mkdir -p bin/
	gcc  -Werror -Wall -ggdb -O0 -o bin/pingpong.exe pingpong/*.c
	gcc  -Werror -Wall -ggdb -O0 -o bin/primes.exe primes/*.c
clean:
	rm -f *.o bin/*
