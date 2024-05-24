#include <stdio.h>
#include <stdlib.h>

#include "strfuncs.h"

char *destroy(const char *str) {
    free((char *)str);
    return NULL;
}


size_t string_length(const char *str){
    size_t counter = 0;
    unsigned int i = 0;
    while(str[i] != '\0'){
        counter++;
        i++;
    }

    return counter;    
}


char *string_filter(const char *str, char c) {
    unsigned int count = 0;
    // Calcula el tamaño de la cadena filtrada
    for (unsigned int i = 0; str[i] != '\0'; i++) {
        if (str[i] != c) {
            count++;
        }
    }
    
    char *str_ptr = malloc(count + 1); // +1 para el carácter \0
    if (str_ptr == NULL) {
        return NULL; 
    }
    

    count = 0;
    for (unsigned int i = 0; str[i] != '\0'; i++) {
        if (str[i] != c) {
            str_ptr[count] = str[i];
            count++;
        }
    }
    str_ptr[count] = '\0'; // Agregar el carácter nulo de terminación
    
    return str_ptr;
}

bool string_is_symmetric(const char *str){
    size_t length = string_length(str);
    bool res = true;
    for (size_t i = 0; i < length/2; i++){
        if (str[i] != str[length -1 -i]){       //length-1 pq las posiciones empiezan desde 0
            res=false;
        }
    }
    
    return res;
}