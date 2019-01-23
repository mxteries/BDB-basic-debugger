#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <signal.h>
#include <stdlib.h>

// a basic debugger, source: http://system.joekain.com/2015/06/08/debugger.html

static void trace_target(pid_t pid) {
    while(1) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
            printf("Target program stopped by SIGTRAP, continuing on\n");
            // restart the target process and don't send a signal (0)
            ptrace(PTRACE_CONT, pid, NULL, 0);
        } 
        else if (WIFEXITED(status)) {
            printf("Target program finished. Debugger now exiting\n");
            exit(0);
        }
    }
}

int debug(char *argv[]) {
    char *program = argv[0];
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork error");
    } else if (pid == 0) {
        /* execute target program */
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        if (execvp(program, &argv[1]) < 0) {
            perror("exec failed");
            return 1;
        }
    } else {
        /* parent */
        trace_target(pid);
    }
    return 0;
}
// int main(int argc, char* argv[]) {
//     if (argc < 2) {
//         printf("Usage: ./bdb (program name) (program args)\n");
//     }
//     char* program = argv[1];
//     pid_t pid;
//     int status;

//     if ((pid = fork()) < 0) {
//         perror("fork error");
//     } else if (pid == 0) {
//         /* execute target program */
//         ptrace(PTRACE_TRACEME, 0, NULL, NULL);
//         execvp(program, &argv[1]);
//         perror("exec failed");
//     } else {
//         /* parent */
//         waitpid(pid, &status, 0);
//         if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
//             printf("Target program stopped by SIGTRAP, continuing on");
//             // restart the target process and don't send a signal (0)
//             ptrace(PTRACE_CONT, pid, NULL, 0);
//         }
//         printf("Debugger now exiting\n");
//     }
// }