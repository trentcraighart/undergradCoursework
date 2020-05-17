#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <pthread.h>

#include <unistd.h>

#include <sys/mman.h>

#include <x86intrin.h>

/*
 * we will use x86 intrinsics in gcc compiler, defined in x86intrin.h
 *
 * _mm_clflush(ptr);
 * _mm_lfence();
 * _mm_mfence();
 * uint32_t a;
 * __rdtscp(&a);
 */


// for warming up the CPU to make it run with in a stable frequency...
volatile uint64_t count = 0;
void
warmup(void) {
    for (int i=0; i<10000000; ++i) {
        count += i;
    }
}

uint64_t
read_random(void) {
    uint64_t data = 0ul;
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp == NULL) {
        fprintf(stderr, "Failed in opening /dev/urandom..\n");
        exit(-1);
    }
    fread(&data, 1, 8, fp);
    fclose(fp);
    return data;
}


// map memory..
void *
map_memory(size_t size) {
    return mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC,
                MAP_ANONYMOUS | MAP_PRIVATE | MAP_POPULATE,
                -1, 0);
}

uint8_t *scratchpad;
uint64_t random_int;
uint8_t *random_as_chars;

volatile char value;

void
action(int i) {
    uint64_t read_pos = 4096 * random_as_chars[i];
    value = scratchpad[4096 * random_as_chars[i]];
    _mm_lfence();
}



// TODO:IMPLEMENT THIS FUNCTION!
// flush all cache blocks (i.e., i-th 4096 byte location.., i * 4096)
// in the scratchpad. Don't forget to run mfence at the end.
void
flush_all(void) {
    for(int i=0; i<256; ++i){
        _mm_clflush(&scratchpad[4096 * random_as_chars[i]]);
    }
    _mm_mfence();
}

// TODO: IMPLEMENT THIS FUNCTION
// reload cache blocks and measure timings.
uint64_t
reload(int j) {
    volatile char c;
    volatile uint64_t t1, t2, diff;
    uint32_t a;

    t1 = __rdtscp(&a);
    c = scratchpad[4096 * j];
    t2 = __rdtscp(&a);
    return(t2 - t1);
}


uint64_t access_time_table[256];

int
main(int argc, char **argv, char **envp)
{

    char data[512];

    scratchpad = (uint8_t *) map_memory(256 * 4096);
    printf("Mapped at %p\n", scratchpad);

    random_int = read_random();
    random_as_chars = (uint8_t *) &random_int;

    printf("I will not let you read my random... you must guess all 8 bytes..\n");


    // guess each character
    for (int i=0; i<8; ++i) {
        printf("If you press ENTER, I will read scratchpad[random_as_chars[%d] * 4096] in action()\n", i);
        fgets(data, 20, stdin);

        // measure timing for each position...
        for (int j=0; j<256; ++j) {
            warmup();
            flush_all();
            action(i);
            access_time_table[j] = reload(j);
            printf("Access time for 0x%02x: %lu\n", j, access_time_table[j]);
        }

        // TODO: IMPLEMENT here...
        // GET YOUR GUESS here..
        int your_guess = 0;
        uint64_t min = -1ul;
        for (int j = 0; j < 256; ++j){
            if(min > access_time_table[j]){
                min = access_time_table[j];
                your_guess = j;
            }
        }


        if (your_guess != random_as_chars[i]) {
            printf("Wrong guess!\n");
            printf("Random bytes were 0x%016lx\n", random_int);
            printf("Your guess for random_as_chars[%d] = 0x%02x\n", i, your_guess&0xff);
            exit(-1);
        }
    }

    printf("Great!\n");

    return 0;
}
