#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "stack.h"

typedef struct _s_stack {
    stack_elem top;
    struct _s_stack *next;
} _s_stack; 

typedef struct _s_stack_ {
    _s_stack *start;
    unsigned int size;
} _s_stack_;

static _s_stack* create_elem() {
    _s_stack *p = NULL;
    p = malloc(sizeof(_s_stack));
    p->top = 0;
    p->next = NULL;
    return p;
}

stack stack_empty() {
    stack new = NULL;
    new = malloc(sizeof(_s_stack_));
    new->start = NULL;
    new->size = 0;
    return new;
}

stack stack_push(stack s, stack_elem e) {
    _s_stack *p = create_elem();
    p->next = s->start;
    s->start = p;
    p->top = e;
    s->size += 1;
    assert(s->start!=NULL && s->size>0);
    return s;
}

stack stack_pop(stack s) {
    assert(s->start!=NULL);
    _s_stack *p = NULL;
    p = s->start;
    s->start = s->start->next;
    free(p);
    s->size -= 1;
    return s;
}

unsigned int stack_size(stack s) {
    return s->size;
}

stack_elem stack_top(stack s) {
    assert(s->start!=NULL);
    return s->start->top;
}

bool stack_is_empty(stack s) {
    return (s->size == 0);
}

stack_elem *stack_to_array(stack s) {
    assert(s!=NULL);
    stack_elem * p = NULL;
    _s_stack *aux = s->start;    
    unsigned int len = s->size;
    if (len != 0) {
        p = calloc(len,sizeof(stack_elem));
        for (unsigned int i=0; i<len; ++i) {
            p[len-i-1] = aux->top;
            aux = aux->next;
        }
    }
    return p;
}

stack stack_destroy(stack s) {
    _s_stack *p = s->start, *q = s->start;
    while (q != NULL) {
        q = q->next;
        free(p);
        p = q;
    }
    free(s);
    return NULL;   
}
