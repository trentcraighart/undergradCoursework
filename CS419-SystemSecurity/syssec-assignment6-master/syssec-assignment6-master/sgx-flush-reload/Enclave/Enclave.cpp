/*
 * Copyright (C) 2011-2019 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "Enclave.h"
#include "Enclave_t.h" /* print_string */
#include <stdarg.h>
#include <stdio.h> /* vsnprintf */
#include <string.h>

#include "array.h"

/*
 * printf:
 *   Invokes OCALL to display the enclave buffer to the terminal.
 */
int printf(const char* fmt, ...)
{
    char buf[BUFSIZ] = { '\0' };
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_print_string(buf);
    return (int)strnlen(buf, BUFSIZ - 1) + 1;
}

uint64_t a_global_integer = 0x4142434445464748;
volatile char global_variable;

uint64_t
rdrand() {
    uint64_t ret;
    asm volatile("rdrand %[ret]"
            :
            [ret] "=r" (ret)
            :
            :"memory");
    return ret;
}

void
ecall_initialize(void) {
    a_global_integer = rdrand();
    printf("Initialized!\n");
}

void
ecall_check_random(uint64_t guess_random) {
    if (guess_random == a_global_integer) {
        printf("Your guess is correct: %lx vs %lx; GREAT!\n",
                guess_random, a_global_integer);
    }
    else {
        printf("Your guess is wrong: %lx vs %lx; Try again!\n",
                guess_random, a_global_integer);
    }
}

void
ecall_access(void *scratchpad, int idx) {
    // vulnerable to flush+reload
    uint8_t * random_as_character = (uint8_t*)&a_global_integer;
    uint8_t c = random_as_character[idx];
    Array *pad = (Array*)scratchpad;
    global_variable = pad[c].data[0];
}

void
ecall_example(void *scratchpad, int value) {
    uint8_t c = (uint8_t) (value & 0xff);
    Array *pad = (Array*)scratchpad;
    global_variable = pad[c].data[0];

}
