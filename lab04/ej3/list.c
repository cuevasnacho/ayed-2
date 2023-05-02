#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"

struct _list {
    list_elem elem;
    list next;
};

typedef struct _list node;

static list create_node() {
    list p;
    p = malloc(sizeof(node));
    p->elem = 0;
    p->next = NULL;
    return p;
}

// constructors

list empty() {
    return NULL;
}

list addl(list l, list_elem e) {
    list p = create_node();
    p->elem = e;
    p->next = l;
    return p;
}

// destroy

list destroy(list l) {
    list p = l, q = l;
    while (q != NULL) {
        q = q->next;
        free(p);
        p = q;
    }
    return NULL;
}

// operations

bool is_empty(list l) {
    return l == NULL;
}

list_elem head(list l) {
    assert(l != NULL);
    return l->elem;
}

list tail(list l) {
    list p = l->next;
    free(l);
    return p;
}

list addr(list l, list_elem e) {
    list p = l, r = l, q = NULL;
    q = create_node();
    q->elem = e;
    q->next = NULL;
    while (r != NULL) {
        r = r->next;
        p = (r != NULL) ? r : p;
    }
    p->next = q;
    return l;
}

unsigned int length(list l) {
    list p = l;
    unsigned int len = 0;
    while (p != NULL) {
        p = p->next;
        ++len;
    }
    return len;
}

list concat(list l, list lp) {
    list p = l, q = l;
    while (q != NULL) {
        q = q->next;
        p = (q != NULL) ? q : p;
    }
    p->next = lp;
    return l;
}

list_elem index(list l, unsigned int i) {
    list p = l;
    for (unsigned int j = 0; j < i; ++j) {
        p = p->next;
    }
    return p->elem;
}

list take(list l, unsigned int t) {
    list p = l, q, r;
    unsigned int i = 0;
    while (i < t && p != NULL) {
        p = p->next;
        ++i;
    }
    if (p->next != NULL) {
        q = p->next;
        p->next = NULL;
        r = q;
        while (r != NULL) {
            r = r->next;
            free(q);
            q = r;
        }
    }
    return l;
}

list drop(list l, unsigned int d) {
    list p = l;
    unsigned int i = 0;
    while (i < d && p != NULL) {
        p = p->next;
        free(l);
        l = p;
    }
    return l;
}

list copylist(list l) {
    list copy = NULL, p = l, q = NULL;
    if (l != NULL) {
        q = create_node();
        copy = q;
        q->elem = p->elem;
        q->next = NULL;
        p = p->next;
        while (p != NULL) {
            q->next = create_node();
            q = q->next;
            q->elem = p->elem;
            q->next = NULL;
            p = p->next;
        }
    }
    return copy;
}
