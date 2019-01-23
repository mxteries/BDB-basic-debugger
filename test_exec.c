#include "debugger.h"
#include <unistd.h>
#include <string.h>

int main() {
    // src: https://stackoverflow.com/a/1088667/10634812
    // ^ comments have good info on how to read c arrays
    char *a[2];
    a[0] = "./example";
    a[1] = NULL;
    debug(a);
    return 0;
}