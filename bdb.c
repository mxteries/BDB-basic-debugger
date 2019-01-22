#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>

// a basic debugger (bdb)

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./bdb ./(program name) (program args)\n");
    }
    char* program = argv[1];
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
        perror("fork error");
    } else if (pid == 0) {
        /* execute target program */
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execv(program, &argv[1]);
        perror("exec failed");
    } else {
        /* parent */
        waitpid(pid, &status, 0);
        printf("Debugger now exiting\n");
    }
}