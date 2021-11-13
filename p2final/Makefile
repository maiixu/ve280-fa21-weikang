all: main

main: main.c func.c p2new.c plin.c
	gcc main.c func.c p2new.c plin.c -o main -O2 -Werror -Wall -Wextra -Wconversion -Wvla -Wpedantic -lm

clean:
	rm -f main