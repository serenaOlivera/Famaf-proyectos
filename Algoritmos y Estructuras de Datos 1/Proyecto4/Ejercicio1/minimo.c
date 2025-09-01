#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*
b) Los ejemplos a continuacion han sido vistos en el teorico practico. Para cada uno de
ellos, se debe obtener la pre y post condicion y la derivacion. Luego, se debe traducir a
Lenguaje C el programa y las pre y post condiciones utilizando el comando assert.

--(Mınimo) Calculo del mınimo entre dos variables enteras x e y. El programa en C
se debe llamar minimo.c.
*/


void minimo (int x, int y){
    if (x>y){
        assert (x>y);
        printf("El minimo entre %d y %d es %d", x, y, y);
    } else if (x<y){
        assert(x<y);
        printf("El minimo entre %d y %d es %d", x, y, x);
    } else if (x==y){   
        assert (x==y);
        printf("%d y %d son iguales, por lo tanto no hay minimo", x, y);
    }
}

int pedir_entero (char name)
{
    int x;
    printf("Ingrese un valor para la guarda %c\n", name);
    scanf(" %d", &x);

    return x;
}



int main (){
    char name;
    int x;
    printf("Ingrese un caracter para su guarda\n");
    scanf(" %c", &name);
    x= pedir_entero(name);

    int y;
    printf("Ingrese un caracter para su guarda\n");
    scanf(" %c", &name);
    y= pedir_entero(name);
    
    minimo(x, y);

    return 0;
}