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
#include "util.h"

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


Array *oram;

// trusted memory (not for its access pattern...)
Array in_enclave_array_storage;

void
ecall_initialize_oram(void *oram_memory) {
    oram = (Array*)oram_memory;
    printf("Initialized!\n");
}

void
ecall_oram_access(uint64_t *ret) {

    uint64_t element_idx = rdrand() & 0xff;

    //printf("We're inside the ecall_oram_access function\n");
    for (int i=0; i<256; ++i) {
        // TODO: use predicate to copy the data at element_idx to
        //       in_enclave_array_stroage...
        uint64_t predicate = 0;
        o_memcpy(predicate, &in_enclave_array_storage, &oram[i], sizeof(Array));
        //printf("in_enclave_array_storage: %s\n", in_enclave_array_storage);
    }



    *ret = 0;
    return;
}


void
ecall_insecure_access(uint64_t *ret) {
    uint64_t element_idx = rdrand() & 0xff;
    memcpy(&in_enclave_array_storage, &oram[element_idx], sizeof(Array));
    uint64_t *ptr = (uint64_t*)&in_enclave_array_storage.data[0];
    if (*ptr == element_idx && *(ptr+3) == element_idx) {
        *ret = 0;
    }
    else {
        *ret = 1;
    }
}

