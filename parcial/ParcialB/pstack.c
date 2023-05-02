#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size;
    struct s_node *front;
};

struct s_node {
    pstack_elem elem;
    priority_t priority;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;

    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}

static bool invrep(pstack s) {
    bool b=true;
    struct s_node *p = s->front, *q = s->front;
    while (b && p!=NULL) {
        p = p->next;
        if (p!=NULL) {
            b = q->priority >= p->priority;
        }
        q = p;
    }
    return b;
}

pstack pstack_empty(void) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    s->size = 0;
    s->front = NULL;
    assert(pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority), *priority_checker=s->front, *refer=s->front;
    if (s->front!=NULL) {
        while (priority_checker!=NULL && priority_checker->priority>priority) {
            priority_checker = priority_checker->next;
            if (priority_checker!=NULL && priority_checker->priority>priority) {
                refer = priority_checker;
            }
        }
        if (priority_checker != s->front) {
            refer->next = new_node;
            new_node->next = priority_checker;
        } else {
            s->front = new_node;
            new_node->next = priority_checker;
        }
    } else {
        s->front = new_node;
    }
    s->size += 1;
    assert(!pstack_is_empty(s) && invrep(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    return (s->size==0);
}

pstack_elem pstack_top(pstack s) {
    assert(!pstack_is_empty(s));
    return (s->front->elem);
}

priority_t pstack_top_priority(pstack s) {
    assert(!pstack_is_empty(s));
    return (s->front->priority);
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(!pstack_is_empty(s) && invrep(s));
    struct s_node *pop = s->front;
    s->front = pop->next;
    free(pop);
    s->size -= 1;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *destroyer = s->front, *refer = s->front;
    while (refer!=NULL) {
        refer = refer->next;
        destroy_node(destroyer);
        destroyer = refer;
    }
    free(s);
    s = NULL;
    assert(s==NULL);
    return s;
}