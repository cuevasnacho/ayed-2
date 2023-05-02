#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

char *parse_filepath(int argc, char *argv[]) {
    char *result = NULL;

    if (argc < 2) {
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

unsigned int data_from_file(const char *path,unsigned int indexes[],
    char letters[], unsigned int max_size) {
    FILE *file;

    unsigned int length = 0;

    file = fopen(path, "r");
    while (feof(file) == 0 && length < max_size) {
        //fscanf(file,"%u '%c'\n",&indexes[length],&letters[length]);
        fscanf(file,"%u ",&indexes[length]);
        fscanf(file,"'%c'\n",&letters[length]);
        length++;
    }

    fclose(file);
    
    return length;
}

void order(unsigned int indexes[], char letters[], char array[], unsigned int length) {
    unsigned int j;
    for (unsigned int i = 0; i < length; ++i) {
        j = indexes[i];
        array[j] = letters[i];
    }
    
    return;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0; 
    
    filepath = parse_filepath(argc, argv);

    length = data_from_file(filepath,indexes,letters,MAX_SIZE);

    order(indexes,letters,sorted,length);

    dump(sorted, length);

    return EXIT_SUCCESS;
}

