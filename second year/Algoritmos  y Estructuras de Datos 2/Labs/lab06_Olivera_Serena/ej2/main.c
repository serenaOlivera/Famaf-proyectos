#include <stdio.h>
#include <stdlib.h>

#include "string.h"

int main (void){
    string str1 = string_create ("hola");
    string str2 = string_create("biblioteca");

    bool less = false;
    less = string_less(str1, str2);
    if (less == true){
        printf("La cadena 1 es menor a la cadena 2 \n");
    }else{
        printf("La cadena 2 es menor a la cadena 1 \n");
    }

    bool eq = false;
    eq = string_eq(str1, str2);
    if (eq == true){
        printf("la cadena 1 es igual a la cadena 2 \n");
    }else{
        printf("las cadenas no son iguales \n");
    }

    string str3 = string_create("chau");
    string str4 = string_create("hola");

    less = string_less(str3, str4);
    if (less == true){
        printf("La cadena 3 es menor a la cadena 4 \n");
    }else{
        printf("La cadena 4 es menor a la cadena 3 \n");
    }

    eq = string_eq(str1, str2);
    if (eq == true){
        printf("la cadena 1 es igual a la cadena 2 \n");
    }else{
        printf("las cadenas no son iguales \n");
    }

    string_destroy(str1);
    string_destroy(str2);
    string_destroy(str3);
    string_destroy(str4);

    return 0;
}
