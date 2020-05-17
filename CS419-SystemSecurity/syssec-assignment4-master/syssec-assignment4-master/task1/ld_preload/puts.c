#include <stdlib.h>

int puts(char *str)
{
    system("echo hijacked!");
}
