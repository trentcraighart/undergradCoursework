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

    printf("Type a string: \n");
    scanf("%20s", b);

    if (b[0] == 0x41) {
        if (b[1] == 0x42) {
            if (b[2] == 0x43) {
                if (b[3] == 0x44) {
                    bug();
                }
            }
        }
    }
    return 0;

}
