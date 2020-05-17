#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>

void
syscall(void) {
    asm volatile(
            "push %rbp;"
            "mov %rsp, %rbp;"
            "push $1;"
            "pop %rax;"
            "push $0x41414141;"
            "push %rsp;"
            "pop %rsi;"
            "push $1;"
            "pop %rdi;"
            "push $4;"
            "pop %rdx;"
            "syscall;"
            "leave;");
}



int main() {
    uint32_t a;
    uint64_t tsc;
    write(1, "I hope this write prints nothing!\n", 35);
    printf("I hope the following syscall prints nothing!\n");
    syscall();
    tsc = __rdtscp(&a);
    printf("RDTSCP returned %p\n", (void*)tsc);
    if (tsc != 0) {
        // I want rdtscp always returns 0
        while(1);
    }
}
