#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile int b;
void bug(void) {
    int *a = 0x41414141;
    b = *a;
}

int main(int argc, char **argv, char **envp) {
    char b[512];
    int *a = (int*)b;

    printf("Type a string: \n");
    scanf("%20s", b);

    if (*a == 0x44434241) {
        bug();
    }
    return 0;

}
