#include <stdio.h>
#include <stdbool.h>

/* Enunciado 
c) Escribı el programa del ejercicio 4b, pero utilizando las funciones del ejercicio anterior.
¿Que ventajas encontras en esta nueva version?. ¿Podrıas escribir alguna otra funcion
en ese ejercicio, cual?. ¿En que otros ejercicios de ese Proyecto lo podrıas utilizar?.
Reescribı los programas donde puedas utilizarlas.
*/

/*Primero, copio las funciones del 6.A para poder utilizarlas
en el ejercicio 4.B
*/

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

/*ejercicio 4 con pedir entero e imprimir entero*/
void ejb()
{
    int x=0;
    int y=0;
    int z=0;
    int m=0;
    x= pedir_entero_2('x');
    y= pedir_entero_2('y');
    z= pedir_entero_2('z');
    m= pedir_entero_2('m');

    if (x < y) { 
        m = x;
    
    } else{
        m = y;
    }

    if (m < z) {

    } else{
      m = z;
    }
    imprimir_entero_2('x', x);
    imprimir_entero_2('y', y);
    imprimir_entero_2('z', z);
    imprimir_entero_2 ('m', m);
    return;
}

int main(void)
{
    ejb();
    return 0;
}

/*
        Que ventajas  encontras en esta  nueva version?
La ventaja que encuentro es que es mas automatizado con respecto a tomar valores
        ¿Podrıas escribir alguna otra funcion en ese ejercicio, cual?
 no :) (no uso las funciones con booleanos porque no tengo booleanos)
        ¿En que otros ejercicios de ese Proyecto lo podrıas utilizar?.
Basicamente,todos

*/


/* Ahora, reescribo los programas del resto de la guia usando pedir_entero e imprimir_entero
en sus respectivos archivos
*/
