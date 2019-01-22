all: bdb example
clean:
	-rm -f bdb example

bdb: bdb.c
	gcc -Wall bdb.c -o bdb

example: example.c
	gcc example.c -Og -g -o example