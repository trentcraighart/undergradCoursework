#include <stdio.h>

char bin_sh_for_you[] = "/bin/sh";
char print_string[] = "This program does nothing, and /bin/sh is at %p!\n";

int main() {
    printf(print_string, bin_sh_for_you);
}
