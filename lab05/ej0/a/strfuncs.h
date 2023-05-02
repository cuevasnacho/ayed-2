#ifndef _STRFUNCS_H
#define _STRFUNCS_H

#include <stddef.h>

size_t string_length(const char *str);
/* calcula la longitud de la cadena apuntada por str */

char *string_filter(const char *str, char c);
/* devuelve una nueva cadena en memoria dinamica que se obtiene tomando los
caracteres de str que son distintos del caracter c */

#endif