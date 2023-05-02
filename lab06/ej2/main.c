#include <stdio.h>
#include <stdlib.h>
#include "string.h"

int main(void)
{
    const char *p = "word";
    const char *r = "chona";
    string s, sp, clone;
    unsigned int length = 0, length2 = 0;

    s = string_create(p);
    sp = string_create(r);
    length = string_length(s);
    printf("%d\n",length);

    printf("%d %d",string_less(sp,s), string_eq(s,s));
    clone = string_clone(s);

    length2 = string_length(clone);
    printf("%d\n",length2);

    s = string_destroy(s);
    sp = string_destroy(sp);
    clone = string_destroy(clone);


    return EXIT_SUCCESS;
}