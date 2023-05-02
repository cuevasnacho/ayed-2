#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

typedef struct _list * list;

typedef int list_elem;

// constructors

list empty();

list addl(list l, list_elem e);

// destroy

list destroy(list l);

// operations

bool is_empty(list l);

list_elem head(list l);

list tail(list l);

list addr(list l, list_elem e);

unsigned int length(list l);

list concat(list l, list lp);

list_elem index(list l, unsigned int i);

list take(list l, unsigned int t);

list drop(list l, unsigned int d);

list copylist(list l);

#endif
