#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void) {

    data_t messi = {"Leo Messi", 36, 169};
    print_data(messi);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n", sizeof(messi.name), sizeof(messi.age),
                                        sizeof(messi.height), sizeof(messi));

    
    data_t *p = NULL;
    p = &messi;
    printf("name-direction: %lu \n"
            "age-direction: %lu \n"
            "height-direction: %p \n"
            "data_t-direction: %p \n", (uintptr_t) &(p->name), (uintptr_t) &(p->age),
                                        (void *) &(p->height), (void *)p);
    return EXIT_SUCCESS;
}

/*
* La suma de los miembros NO coincide con el total
* El tamaño del campo name NO depende del nombre que contiene
* NO hay nada raro en las direcciones de memoria, solo que las que se imprimieron con %p muestran el
* numero en hexadecimal y las que se imprimieron con %lu no
*/