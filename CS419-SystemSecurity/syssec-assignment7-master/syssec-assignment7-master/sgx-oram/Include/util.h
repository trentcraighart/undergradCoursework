#ifndef ___UTIL_H___
#define ___UTIL_H___

static inline uint64_t
__attribute__((always_inline))
check_equal(uint64_t a, uint64_t b) {
    uint64_t ret;
    uint8_t v;
    // TODO: Write assembly here!
    // Hint: use sete
    asm volatile("cmp %[a], %[b];"
            "sete %[c];"
            :   [c] "=r" (v)
            :   [a] "r" (a),
                [b] "r" (b)
            :
            );

    // v == 1 if a == b
    // v == 0 if a != b
    ret = v;
    return ret;
}

static inline uint64_t
__attribute__((always_inline))
check_greater(uint64_t a, uint64_t b) {
    uint64_t ret;
    uint8_t v;

    // TODO: Write assembly here!
    // Hint: use seta   (unsigned)
    asm volatile("cmp %[a], %[b];"
            "seta %[c];"
            :   [c] "=r" (v)
            :   [a] "r" (a),
                [b] "r" (b)
            :
            );

    ret = v;
    return ret;
}

static inline uint64_t
__attribute__((always_inline))
check_greater_than_equal(uint64_t a, uint64_t b) {
    uint64_t ret;
    uint8_t v;

    // TODO: Write assembly here!
    // Hint: use setae  (unsigned)
    asm volatile("cmp %[a], %[b];"
            "setae %[c];"
            :   [c] "=r" (v)
            :   [a] "r" (a),
                [b] "r" (b)
            :
            );

    ret = v;
    return ret;
}

static size_t
o_memcpy_byte(uint64_t predicate, void *dst, void *src, size_t size) {
    size_t copied_size;

    // TODO: Write assembly here!
    // Hint: read from both src and dst to registers and then write one..
    //       cmove will be helpful...

    asm volatile(
            "push %%r11;"
            "push %%r12;"
            "push %%r13;"
            "push %%r14;"
            "push %%r15;"

            // r15 stores predicate
            "mov %[pred], %%r15;"
            // use r12 as loop counter, store size to r11
            "mov %[size], %%r11;"
            "mov $0, %%r12;"
            "loop_start%=:"
            "cmp %%r11, %%r12;"
            // exit if r11 (size) == r12 (loop counter)
            "je loop_exit%=;"

            // read from dst, store that byte to r13b
            "movb (%[dst], %%r12, 1), %%r13b;"
            // read from src, store that byte to r13b
            "movb (%[src], %%r12, 1), %%r14b;"
            // test predicate
            "test %%r15, %%r15;"
            // if predicate != 0, real copy, so overwrite r13 (dst) with
            // r14 (src)
            "cmovne %%r14, %%r13;"
            // store that byte to memory
            "movb %%r13b, (%[dst], %%r12, 1);"
            // loop condition. increase r12 and jump back to start.
            "inc %%r12;"
            "jmp loop_start%=;"
            "loop_exit%=:"
            // return value
            "mov %%r12, %[copy];"
            "pop %%r15;"
            "pop %%r14;"
            "pop %%r13;"
            "pop %%r12;"
            "pop %%r11;"
            :
                [copy] "=r" (copied_size)
            :
                [size] "r" (size),
                [pred] "r" (predicate),
                [dst] "r" (dst),
                [src] "r" (src)
            : "r11", "r12", "r13", "r14", "r15", "memory");

    return copied_size;
}

static size_t
o_memcpy_8byte(uint64_t predicate, void *dst, void *src, size_t size) {
    size_t copied_size;

    // TODO: Write assembly here!
    // Hint: read from both src and dst to registers and then write one..
    //       cmove will be helpful...

    for(uint64_t i = 0; i < 8; i++){
        copied_size = o_memcpy_byte((predicate + i), dst, src, size);
    }

    return copied_size;
}

static size_t
o_memcpy(uint64_t predicate, void *dst, void *src, size_t size) {
    size_t aligned_size = ((size >> 3) << 3);
    size_t remaining_size = size - aligned_size;

    size_t copied_size = o_memcpy_8byte(predicate, dst, src, aligned_size);
    assert(copied_size == aligned_size);
    if (remaining_size) {
        uint8_t *_dst = (uint8_t*)dst;
        uint8_t *_src = (uint8_t*)src;
        size_t byte_copied_size = o_memcpy_byte(predicate,
                _dst + aligned_size, _src + aligned_size,
                remaining_size);
        assert(byte_copied_size == remaining_size);
        return copied_size + byte_copied_size;
    }
    else {
        return copied_size;
    }
}



#endif
