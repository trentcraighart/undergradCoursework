#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

volatile int b;
void bug(void) {
    int *a = 0x41414141;
    b = *a;
}

int main(int argc, char **argv, char **envp) {
    uint8_t a,b,c,v;

    printf("Input first character (a): \n");
    scanf("%c", &a);

    printf("Input second character (b): \n");
    scanf("%c", &b);

    printf("Input third character (c): \n");
    scanf("%c", &c);

    if (((a + b) * c) != 50) {
        return -1;
    }

    if (((c + b) * a) != 50) {
        return -1;
    }

    if (a == b) {
        return -1;
    }

    if (c == a) {
        return -1;
    }

    if (c == b) {
        return -1;
    }


    bug();

    return 0;

}
