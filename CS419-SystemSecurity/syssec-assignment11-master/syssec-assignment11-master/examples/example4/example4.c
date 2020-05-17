#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile int b;
void bug(void) {
    int *a = 0x41414141;
    b = *a;
}

int main(int argc, char **argv, char **envp) {
    char a,b,c,v;

    printf("Input first character (a): \n");
    scanf("%c", &a);

    printf("Input second character (b): \n");
    scanf("%c", &b);

    printf("Input third character (c): \n");
    scanf("%c", &c);

    // only gets uppercase alphabets
    if (a < 'A' || a > 'Z') return -1;
    if (b < 'A' || b > 'Z') return -1;
    if (c < 'A' || c > 'Z') return -1;

    if (a != 'G') {
        return -1;
    }

    if (b - a != 3) {
        return -1;
    }

    if (c - b != 3) {
        return -1;
    }

    bug();
    return 0;

}
