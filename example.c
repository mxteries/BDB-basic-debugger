#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a simple target program for our debugger
// taken from: https://en.wikipedia.org/wiki/GNU_Debugger

size_t foo_len(const char *s) {
  return strlen(s);
}

int main(int argc, char *argv[]) {
  const char *a = NULL;
  printf("Example program running\n");
  printf("size of a = %lu\n", foo_len(a));
  exit(0);
}