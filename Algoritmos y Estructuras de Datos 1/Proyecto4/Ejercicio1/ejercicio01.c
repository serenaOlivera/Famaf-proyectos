#include <stdio.h>
#include <stdbool.h>
#include <assert.h>



/*a) ejercicio01.c que lee una variable n de tipo int e imprime por pantalla la palabra
“hola” repetida n veces. En esta ocasion el programa debe utilizar dos funciones a definir
(ademas de la funcion main). 
        --Programa en un archivo ejercicio01.c la funcion de
            prototipo (tambien conocido como signatura o firma):
            void hola_hasta(int n)
        que dado un int n, imprime n veces “Hola”. (Usar una bucle while). 
        --La funcion main pide un numero en la entrada antes de
             llamar hola_hasta (¿que funcion podes usar
            ya implementada?). Usa la funcion assert (ver teorico) para chequear que x > 0.
*/


/* Primero escribo la funcion auxiliar*/
void hola_hasta (int n) {
    while (n>0){
        printf("Hola!\n");
        n= n-1;
    }
}

/*Para pedir el entero, uso la funcion antes definida pedir_entero*/

int pedir_entero (char name)
{
    int x;
    printf("Ingrese un valor para la guarda %c\n", name);
    scanf(" %d", &x);

    return x;
}

int main () {
    char x;
    int n;
    n=pedir_entero(x);
    assert (n>0);
    hola_hasta (n);

    return 0;
}