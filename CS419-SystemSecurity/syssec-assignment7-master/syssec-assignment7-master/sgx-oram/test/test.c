#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "util.h"

char *string1 = "Lorem ipsum dolor amet pok pok drinking vinegar kale chips kinfolk echo park vinyl ethical truffaut forage hammock man bun hip\n";
char *string2 = "Gastropub godard art party unicorn, tofu viral tacos stumptown intelligentsia locavore taiyaki shoreditch. Roof party manld ou\n";
char buf[128];

int main() {
    printf("%ld\n", check_equal(1,2));
    printf("%ld\n", check_equal(2,1));
    printf("%ld\n", check_equal(1,1));
    printf("\n\n");
    printf("%ld\n", check_greater(1,2));
    printf("%ld\n", check_greater(2,1));
    printf("%ld\n", check_greater(1,1));
    printf("\n\n");
    printf("%ld\n", check_greater_than_equal(1,2));
    printf("%ld\n", check_greater_than_equal(2,1));
    printf("%ld\n", check_greater_than_equal(1,1));

    strcpy(buf, string1);
    printf("%s", buf);

    o_memcpy_byte(0, buf, string2, strlen(string2));
    printf("%s", buf);
    o_memcpy_byte(15, buf, string2, strlen(string2));
    printf("%s", buf);

    strcpy(buf, string1);
    printf("%s", buf);
    o_memcpy_8byte(0, buf, string2 + 16, 32);
    printf("%s", buf);
    o_memcpy_8byte(0, buf, string2 + 32, 32);
    printf("%s", buf);
}
