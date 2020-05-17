#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdint.h>
#include <inttypes.h>

inline uint64_t
__attribute__((always_inline))
rdtscp(void) {
    uint64_t ret;
    asm volatile(""
            :
            :
            : );
    return ret;
}

inline void
__attribute__((always_inline))
clflush(void *ptr) {
    asm volatile(""
            :
            :
            : );
}

inline void
__attribute__((always_inline))
mfence(void) {
    asm volatile(""
            :
            :
            :);
}

inline void
__attribute__((always_inline))
lfence(void) {
    asm volatile(""
            :
            :
            :);
}

#endif
