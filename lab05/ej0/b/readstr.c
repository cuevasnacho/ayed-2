#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

int main(void) {
    char user_input[MAX_LENGTH];

    char * p = user_input;

    printf("Ingrese su nombre y apellido: ");
    
    p = fgets(p,MAX_LENGTH,stdin);

    p[strlen(p)-1] = '\0';

    printf("Te damos la bienvenida %s a este maravilloso programa!\n", user_input);

    return EXIT_SUCCESS;
}
