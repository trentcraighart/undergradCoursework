#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "cache.h"
#include "rdtsc.h"

// You can define any global variables here to use for sharing it
// between flush and reload, and also share with your_answer
// functions.

// Example
static char temp_values[512];
static int temp_size = 0;
static int total_time = 0;



void flush(l1_entire_blocks *l1_cache) {
  // TODO: flush cache lines using clflush(&l1_cache->blocks[i])
    for(int i = 0; i < 512; i++){
        clflush(&l1_cache->blocks[i]);

    }
    mfence();

}

void reload(l1_entire_blocks *l1_cache) {
  // TODO: 1. get a timestamp using rdtsc
  // TODO: 2. access cache line
  //        e.g., volatile int i = l1_cache->blocks[i].u8val;
  // TODO: 3. get a timestamp using rdtsc
  // TODO: 4. get time diff
  // TODO: 5. determine the value of the secret

    volatile char c;
    volatile uint64_t t1, t2, diff;
    uint32_t a;
    volatile int i;

    t1 = rdtsc();
    i = l1_cache->blocks[0].u8val;
    t2 = rdtsc();

    diff = t2 - t1;
    printf("%lu\n", diff);
    total_time += diff;

//    if( diff >= (total_time / (temp_size + 1))){
    if(diff > 100){
        temp_values[temp_size / 8] = temp_values[temp_size / 8] | (0x01 << ((temp_size % 8)+ 0));
    }

    temp_size++;

}

void your_answer(char* answer) {
  // TODO: collect all bits and write two bytes.
  // we only use 16 bits, 2 bytes. So mark the third byte as zero

  answer[0] = temp_values[0];
  answer[1] = temp_values[1];

  //anwser[0] = temp_values[0];
  //anwser[1] = temp_values[1];
  //anwser[2] = 0x00;
  //temp_values[2] = 0x00;
  //print_in_hex(temp_values, 2);

}

