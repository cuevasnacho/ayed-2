#include <stdlib.h>
#include "strfuncs.h"

size_t string_length(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len += 1;
    }
    return len;
}

char *string_filter(const char *str, char c) {
    char * nueva_cadena;
    size_t i = 0, j = 0, k = 0, len = 0;
    while (str[i] != '\0') {
        len = (str[i] != c) ? len+1 : len;
        ++i;
    }
    nueva_cadena = malloc(i*sizeof(char));
    while (str[k] != '\0') {
        if (str[k] != c) {
            nueva_cadena[j] = str[k];
            ++j;
        }
        ++k;
    }
    return nueva_cadena;
}