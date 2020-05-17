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

    if(strncmp(b, "asdf", 4) == 0) {
        if(strncmp(&b[4], "ASDF", 4) == 0) {
            bug();
        }
    }

    return 0;

}
