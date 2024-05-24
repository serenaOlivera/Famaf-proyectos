#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfuncs.h"

#define MAX_LENGTH 20

#define SIZEOF_ARRAY(s) (sizeof(s) / sizeof(*s))
 
int main(void) {
    char user_input[MAX_LENGTH];
    char ignore_chars[] = {' ', '?', '!', ',', '-', '.'};
    char *filtered=NULL;
    size_t length = 0;
 
    printf("Ingrese un texto (no más de %d símbolos) para verificar palíndromo: ", MAX_LENGTH);
    if (fgets(user_input, sizeof(user_input), stdin)==NULL){
        printf("El texto es vacio\n");
        exit(EXIT_FAILURE);
    }

    length = string_length(user_input);
    if (length > 0 && user_input[length-1] == '\n'){
        user_input[length-1]='\0';
    }

    filtered = string_filter(user_input, ignore_chars[0]);
    if (filtered == NULL){
        printf("El texto fue mal filtrado\n");
        exit(EXIT_FAILURE);
    }

    printf("El texto:\n\n"
            "\"%s\" \n\n"
            "%s un palíndromo.\n\n", user_input, string_is_symmetric(filtered) ? "Es": "NO es");
    destroy(filtered);

    return EXIT_SUCCESS;

}
