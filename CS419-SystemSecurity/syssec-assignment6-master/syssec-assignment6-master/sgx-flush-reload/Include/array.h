#ifndef __ARRAY_H__
#define __ARRAY_H__

// cache scratchpad array type, each element sized 0x1000 (4096 bytes)
typedef struct Array {
    char data[1299827];
} __attribute__((packed)) Array;

#endif
