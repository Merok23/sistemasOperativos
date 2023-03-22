.PHONY: all tests clean
all:
	mkdir -p bin/
	gcc  -Werror -Wall -ggdb -O0 -o bin/ejemplo.exe ejemplo/*.c

clean:
	rm -f *.o bin/*
