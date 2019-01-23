all: debugger example test_exec
clean:
	-rm -f example debugger.o test_exec

debugger: debugger.c
	gcc -Wall -c debugger.c -o debugger.o

example: example.c
	gcc example.c -Og -g -o example

test_exec: test_exec.c
	gcc -Wall test_exec.c debugger.c -o test_exec
