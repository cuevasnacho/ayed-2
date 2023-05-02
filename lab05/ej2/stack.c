#include <stdlib.h>
#include <assert.h>
#include "stack.h"

typedef struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
} _s_stack;

stack stack_empty() {
    stack s = NULL;
    s = malloc(sizeof(_s_stack));
    s->elems = calloc(1,sizeof(stack_elem));
    s->size = 0;
    s->capacity = 1;
    assert(s->size == 0 && s!=NULL);
    return s;
}

stack stack_push(stack s, stack_elem e) {
    assert(s->capacity >= s->size);
    if (s->size >= s->capacity) {
        s->capacity = s->capacity*2;
        s->elems = realloc(s->elems, sizeof(_s_stack)*s->capacity);
    }
    s->elems[s->size] = e;
    s->size += 1;
    return s;
}

stack stack_pop(stack s) {
    assert(s->size>0);
    s->size -= 1;
    return s;
}

unsigned int stack_size(stack s) {
    return s->size;
}

stack_elem stack_top(stack s) {
    assert(s->size>0);
    return s->elems[s->size-1];
}

bool stack_is_empty(stack s) {
    return (s->size == 0);
}

stack_elem *stack_to_array(stack s) {
    assert(s!=NULL);
    stack_elem *new = NULL;
    new = calloc(s->size,sizeof(stack_elem));
    for (unsigned int i=0; i<s->size; ++i) {
        new[i] = s->elems[i];
    }
    return new;
}

stack stack_destroy(stack s) {
    free(s->elems);
    free(s);
    return NULL;
}
