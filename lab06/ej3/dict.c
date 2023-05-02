#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static struct _node_t *create_word(key_t word, value_t def) {
    struct _node_t *new_word=NULL;
    new_word = malloc(sizeof(struct _node_t));
    new_word->left = NULL;
    new_word->right = NULL;
    new_word->key = word;
    new_word->value = def;
    return new_word;
}

static key_t key_max(dict_t dict) {
    key_t max_e;
    if (dict->right==NULL) {
        max_e = dict->key;
    } else {
        max_e = key_max(dict->right);
    }
    return max_e;
}

static bool invrep(dict_t d) {
    bool b = true;
    if (d!=NULL) {
        if (d->left!=NULL) {
            b = b && string_less(d->left->key,d->key) && invrep(d->left);
        }
        if (d->right!=NULL) {
            b = b && string_less(d->key,d->right->key) && invrep(d->right);
        }
    }
    return b;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(invrep(dict));
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    if (dict==NULL) {
        dict = create_word(word,def);
    } else {
        if (string_less(word,dict->key)) {
            dict->left = dict_add(dict->left,word,def);
        } else if (string_less(dict->key,word)) {
            dict->right = dict_add(dict->right,word,def);
        }
    }
    assert(invrep(dict) && dict_exists(dict, word));
    return dict;
}

static dict_t dict_searching(dict_t dict, key_t word) {
    if (dict->key!=word) {
        if (string_less(dict->key,word)) {
            dict->right = dict_searching(dict->right,word);
        } else {
            dict->left = dict_searching(dict->left,word);
        }
    }
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    value_t def=NULL;
    dict = dict_searching(dict,word);
    def = dict->value;
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    bool exists=false;
    assert(invrep(dict));
    if (dict!=NULL) {
        if (string_eq(dict->key,word)) {
            exists = true;
        } else if (string_less(dict->key,word)) {
            exists = dict_exists(dict->right,word);
        } else {
            exists = dict_exists(dict->left,word);
        }
    }

    return exists;
}

unsigned int dict_length(dict_t dict) {
    unsigned int length=0;
    assert(invrep(dict));
    if (dict!=NULL) {
        length += dict_length(dict->left);
        length += dict_length(dict->right);
        ++length;
    }

    assert(invrep(dict));
    return length;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    if (dict!=NULL) {
        if (dict->key==word) {
            if (dict->left==NULL && dict->right==NULL) { // caso trivial
                free(dict);
                dict=NULL;
            } else if (dict->left!=NULL && dict->right==NULL) { // caso tiene un hijo
                dict_t a1=dict->left, a2=dict;
                dict=a1;
                free(a2);
                a2=NULL;
            } else if (dict->left==NULL && dict->right!=NULL) { // caso tiene un hijo
                dict_t a1=dict->right, a2=dict;
                dict=a1;
                free(a2);
                a2=NULL;
            } else { // caso con dos hijos
                key_t max = key_max(dict->left);
                dict->left = dict_remove(dict->left,max);
                dict->key = max;
            }
        }
        else if (string_less(dict->key,word)){
            dict->right = dict_remove(dict->right,word);
        } else {
            dict->left = dict_remove(dict->left,word);
        }
    }
    
    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    dict_t p=dict;
    if (dict!=NULL) {
        dict->left = dict_remove_all(dict->left);
        dict->right = dict_remove_all(dict->right);
        free(p);
    }
    dict=NULL;
    assert(dict == NULL);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    fprintf(file,"%s\n",(char *)dict->key);
}

dict_t dict_destroy(dict_t dict) {
    dict_remove_all(dict);
    return dict;
}

