#include <stdio.h>
#include <stdbool.h>

/*Defino mis funciones auxiliares*/

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


int main(void)
{
    //Traduccion del ejercicio 1h del practico
    
    printf ("-----Traduccion del ejercicio 1.h-----\n");

    int i=0;
    i=pedir_entero('i');

    while (i!=0)
    {
        i= (i-1);
        imprimir_entero('i', i);
    }
    

    //Traduccion del ejercicio 1i del practico

    printf ("-----Traduccion del ejercicio 1.i-----\n");
    i=0;
    i=pedir_entero('i');

    while (i!=0)
    {
        i=0;
        imprimir_entero('i', i);
    }
   
    return 0;

}

/* 
    Ejemplo de ejecucion
    
    PS C:\Users\seren\OneDrive\Documentos\famaf\algo1\Proyecto3\ejercicio5> gcc -Wall -Wextra -std=c99 ej5_a.c  -o a
    PS C:\Users\seren\OneDrive\Documentos\famaf\algo1\Proyecto3\ejercicio5> ./a
    -----Traduccion del ejercicio 1.h-----
    Ingrese un valor para i
    6
    El valor de i es de 5
    El valor de i es de 4
    El valor de i es de 3
    El valor de i es de 2
    El valor de i es de 1
    El valor de i es de 0
    -----Traduccion del ejercicio 1.i-----
    Ingrese un valor para i
    9
    El valor de i es 0
*/