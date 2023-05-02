/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

void print_UI() {
    printf("\nSELECCIONE QUE OPERACION REALIZAR:\n"
    "   1. Mostrar el arbol por pantalla\n"
    "   2. Agregar un elemento\n"
    "   3. Eliminar un elemento\n"
    "   4. Chequear existencia de elemento\n"
    "   5. Mostrar la longitud del arbol\n"
    "   6. Mostrar raiz, maximo y minimo del arbol\n"
    "   7. Salir del programa\n\n");
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    /*dumping the tree*/
    abb_dump(tree);
    if (!abb_is_empty(tree)) {
        printf("\n");
        printf("raiz: %d\nminimo: %d\nmaximo: %d\n", abb_root(tree),
                                                       abb_min(tree),
                                                       abb_max(tree));
    } else {
        printf("\nÁrbol vacío\n");
    }

    unsigned int choise=0;
    abb_elem e;
    bool b;

    while (choise == 0) {
        print_UI();
        scanf("%u",&choise);
        if (choise > 7 || choise <= 0) {
            printf("Por favor, elija una opcion posible\n\n");
            print_UI();
        } else if (choise == 1) {
            abb_dump(tree);
        } else if (choise == 2) {
            scanf("%d",&e);
            tree = abb_add(tree,e);
        } else if (choise == 3) {
            scanf("%d",&e);
            tree = abb_remove(tree,e);
        } else if (choise == 4) {
            scanf("%d",&e);
            b = abb_exists(tree,e);
            if (b) {
                printf("El elemento %d existe\n",e);
            } else {
                printf("El elemento %d no existe\n",e);
            }
        } else if (choise == 5) {
            printf("El largo del arbol es %u\n",abb_length(tree));
        } else if (choise == 6) {
            printf("La raiz del arbol es: %d\n",abb_root(tree));
            printf("El maximo del arbol es: %d\n",abb_max(tree));
            printf("El minimo del arbol es: %d\n",abb_min(tree));
        } else {
            exit(EXIT_SUCCESS);
        }
        choise = 0;
    }

    tree = abb_destroy(tree);
    /*
     * Modificar e implementar con un ciclo una interfaz que permita al usuario
     * realizar una de las siguientes operaciones en cada iteración:
     *
     * 1 ........ Mostrar árbol por pantalla
     * 2 ........ Agregar un elemento
     * 3 ........ Eliminar un elemento
     * 4 ........ Chequear existencia de elemento
     * 5 ........ Mostrar longitud del árbol
     * 6 ........ Mostrar raiz, máximo y mínimo del árbol
     * 7 ........ Salir
     *
     * Se debe solicitar un número de entrada para realizar una de las acciones.
     *
     * Para las opciones 2, 3 y 4 se le deberá pedir al usuario que ingrese el
     * elemento a agregar, eliminar o chequear respectivamente.
     *
     * Al salir debe liberarse toda la memoria utilizada.
     *
     */
    return (EXIT_SUCCESS);
}
