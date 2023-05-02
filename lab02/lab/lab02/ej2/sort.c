#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv;
    if (der > izq) {
        ppiv = partition(a,izq,der);
        
        if (ppiv != 0) {
            quick_sort_rec(a,izq,ppiv-1);
        }
        else {
            quick_sort_rec(a,izq,ppiv);
        }
        quick_sort_rec(a,ppiv+1,der);
        
    }

    return;
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}

