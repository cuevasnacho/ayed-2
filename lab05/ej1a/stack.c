#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "stack.h"
 
typedef struct _s_stack {
    stack_elem top;
    stack next;
} _s_stack; 

static stack create_elem() {
    stack p = NULL;
    p = malloc(sizeof(_s_stack));
    p->top = 0;
    p->next = NULL;
    return p;
}

stack stack_empty() {
    return NULL;
}

stack stack_push(stack s, stack_elem e) {
    stack p = create_elem();
    p->next = s;
    p->top = e;
    assert(p->top == e);
    return p;
}

stack stack_pop(stack s) {
    assert(s!=NULL);
    stack p = s;
    s = s->next;
    free(p);
    return s;
}

unsigned int stack_size(stack s) {
    stack p = s;
    unsigned int size = 0;
    while (p != NULL) {
        p = p->next;
        ++size;
    }
    assert(size>=0);
    return size;
}

stack_elem stack_top(stack s) {
    assert(s!=NULL);
    return s->top;
}

bool stack_is_empty(stack s) {
    return (s == NULL);
}

stack_elem *stack_to_array(stack s) {
    stack_elem * p = NULL;
    int len = stack_size(s), i=len-1;
    if (len != 0) {
        p = calloc(len,sizeof(stack_elem));
        while (i>=0) {
            p[i] = s->top;
            s = stack_pop(s);
            --i;
        }
    }
    return p;
}

stack stack_destroy(stack s) {
    stack p = s, q = s;
    while (q != NULL) {
        q = q->next;
        free(p);
        p = q;
    }
    return NULL;
}