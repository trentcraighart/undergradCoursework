#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <pthread.h>

#include <unistd.h>

#include <sys/mman.h>

#include <x86intrin.h>

#include "util.h"

int
main(int argc, char **argv, char **envp)
{
    uint64_t t1, t2, diff;

    t1 = rdtscp();
    t2 = rdtscp();
    diff = t2 - t1;
    printf("Diff %lu\n", diff);

    t1 = rdtscp();
    sleep(1);
    t2 = rdtscp();
    diff = t2 - t1;
    printf("Diff %lu\n", diff);
    return 0;
}
