CC=gcc
VAL=valgrind
NAME=abb
CFLAGS=-g -Wall -Wconversion -Wtype-limits -pedantic -Werror -std=c99 -O0
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes

build:
	$(CC) *.c -o $(NAME) $(CFLAGS)

valgrind: build
	clear
	$(VAL) $(VFLAGS) ./$(NAME)

zip:
	zip -r tda_abb *.c *.h makefile README.md tda_abb.pdf
