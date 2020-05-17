#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <pthread.h>

#include <unistd.h>

#include <sys/mman.h>

#include <x86intrin.h>

#include "util.h"

// map hugepage. Use this.
void *
map_memory(size_t size) {
    if (size % 0x40000000 == 0 || size % 0x200000 == 0) {
        return mmap((void*)0x10000000, size, PROT_READ | PROT_WRITE | PROT_EXEC,
                MAP_ANONYMOUS | MAP_FIXED | MAP_PRIVATE | MAP_POPULATE | MAP_HUGETLB,
                -1, 0);
    }
    else {
        return mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC,
                MAP_ANONYMOUS | MAP_PRIVATE | MAP_POPULATE,
                -1, 0);
    }
}

volatile uint64_t global_var1, global_var2;
void *scratchpad;

int
main(int argc, char **argv, char **envp)
{

    scratchpad = map_memory(0x200000);
    // measure same bank, different row access time here.
    uint64_t row_access_time = 0ul;

    printf("Row access time: %lu\n", row_access_time);
    return 0;
}
