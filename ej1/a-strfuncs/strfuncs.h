#ifndef _STRFUNCS_H
#define _STRFUNCS_H

#include <stdbool.h>

char *destroy(const char *str);
/*destruye el puntero.*/

size_t string_length(const char *str);
/* Calcula la longitud de la cadena apuntada por str*/

char *string_filter(const char *str,char c);
/*Devuelve una cadena en MEMORIA DINAMICA que se obtiene tomando los caracteres de 
str que son distintos de c*/

bool string_is_symmetric(const char *str);
/*que indica si la cadena apuntada por str es simétrica en cuanto que el primer caracter coincide con el
último, el segundo con el penúltimo, etc; como por ejemplo las cadenas "aba", "abcba", "a", "".
*/

#endif