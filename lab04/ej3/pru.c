#include <stdio.h>
#include "list.h"
#include <stdbool.h>

int main() {
    bool b;
    int len, len2;
    list_elem e;
    list l = empty(), lp = empty(), cc;
    l = addl(l,2);
    l = addl(l,5);
    l = addl(l,7);
    l = addl(l,2);
    l = addl(l,5);
    l = addl(l,7);
    l = addl(l,2);
    l = addl(l,5);
    l = addl(l,7);
    l = addr(l,12);
    len = length(l);
    lp = addl(lp,2);
    lp = addl(lp,2);
    lp = addl(lp,2);
    cc = concat(l,lp);
    len2 = length(cc);
    b = is_empty(l);
    printf("%d", b);
    e = head(l);

    //destroy(l);

    printf("%d", e);
    printf("%d", len);
    printf("%d", len2);
    return 0;
}