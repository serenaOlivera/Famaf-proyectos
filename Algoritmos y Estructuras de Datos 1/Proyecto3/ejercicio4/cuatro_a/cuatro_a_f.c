#include <stdio.h>
#include <stdbool.h>

/*defino mis funciones auxiliares:*/

int pedir_entero (char name)
{
    int x;
    printf("Ingrese un valor para la guarda %c\n", name);
    scanf(" %d", &x);

    return x;
}


void imprimir_entero (char name, int x)
{
    printf("El valor de la guarda %c es %d\n", name, x);
}


/*Traducción del ejercicio 1e del practico*/
void unoe()
{
    int x=0;
    int y=0;
    x=pedir_entero('x');
    y=pedir_entero('y');

    if (x>=y)
    {
        x=0;
    } else if (x<=y)
    {
        x=2;
    };
    imprimir_entero('x',x);
    imprimir_entero('y',y);

    return;
}

int  main ()
{
    unoe();
    return 0;
}

/*Ejemplo de prueba cuando estaba definido sin pedir_entero e imprimir_entero

PS C:\Users\seren\OneDrive\Documentos\famaf\algo1\Proyecto3\ejercicio4\cuatro_a> gcc -Wall -Wextra -std=c99 cuatro_a_f.c  -o unof
PS C:\Users\seren\OneDrive\Documentos\famaf\algo1\Proyecto3\ejercicio4\cuatro_a> ./unof
Ingrese un valor para x
-1000
Ingrese un valor para y mayor a x
1
El valor de x es 2
y el valor de y es 1

*/