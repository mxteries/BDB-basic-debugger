all: debug example
clean:
	-rm -f debug example

debug: debug.c
	gcc -Wall debug.c -o debug

example: example.c
	gcc example.c -Og -g -o example