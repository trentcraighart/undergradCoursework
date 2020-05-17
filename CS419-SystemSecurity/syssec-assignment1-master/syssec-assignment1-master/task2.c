#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <pthread.h>

#include <unistd.h>

#include <sys/mman.h>

#include <x86intrin.h>

#include "util.h"

volatile uint64_t gloval_var1;

int
main(int argc, char **argv, char **envp)
{

    // measure cache-miss time here.
    uint64_t *array = malloc(0x1000);

    // do something..

    // update this
    uint64_t cache_miss_time  = 0ul;

    printf("Cache miss time %lu\n", cache_miss_time);
    return 0;
}
