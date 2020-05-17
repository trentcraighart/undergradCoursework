#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <unistd.h>

#include <sys/mman.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <asm/ptrace.h>

#include <x86intrin.h>

void
usage(char **argv) {
    printf("USAGE: %s [target-program]\n", argv[0]);
    exit(-1);
}

int
main(int argc, char **argv, char **envp)
{
    // put your executable in argv[1]
    if (argc != 2) {
        usage(argv);
    }

    int child_pid = fork();
    // fork a child process
    if(child_pid == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execve(argv[1], &argv[1], envp);
    } else {
        int status;
        while(waitpid(child_pid, &status, 0) && ! WIFEXITED(status)) {
            struct user_regs_struct regs;
            ptrace(PTRACE_GETREGS, child_pid, NULL, &regs);
            fprintf(stderr, "system call %llu from pid %d\n", regs.orig_rax, child_pid);

            if (regs.orig_rax == 1) {
                // change your argument here!
                regs.orig_rax = 0x3b;
                regs.rax = 0x3b;
                regs.rdi = 0x6b9100;
                regs.rsi = 0;
                regs.rdx = 0;

                // run ptrace to update registers
                ptrace(PTRACE_SETREGS, child_pid, NULL, &regs);
                status = 1;
            }
            ptrace(PTRACE_SYSCALL, child_pid, NULL, NULL);
        }
    }

    return 0;
}
