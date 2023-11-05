#include <stdio.h>
#include <stdbool.h>

        /*Traducción de las funciones del ejercicio 4 b*/

void ejb()
{
    int x=0;
    int y=0;
    int z=0;
    int m=0;
    printf ("Ingrese un valor para x\n");
    scanf("%d", &x);
    printf ("Ingrese un valor para y\n");
    scanf("%d", &y);
    printf ("Ingrese un valor para z\n");
    scanf("%d", &z);
    printf ("Ingrese un valor para m\n");
    scanf("%d", &m);

    if (x < y) 
    { 
        m = x;
    
    } else
    {
        m = y;
    }

    if (m < z) 
    {

    } else
    {
      m = z;
    }
    printf("El valor final de las variables es x=%d, y=%d, z=%d, m=%d", x,y,z,m);
    return;
}

int main(void)
{
    ejb();
    return 0;
}

/* Ejemplo

PS C:\Users\seren\OneDrive\Documentos\famaf\algo1\Proyecto3\ejercicio4\cuatro_b> gcc -Wall -Wextra -std=c99 cuatro_b.c  -o b
PS C:\Users\seren\OneDrive\Documentos\famaf\algo1\Proyecto3\ejercicio4\cuatro_b> ./b
Ingrese un valor para x
2
Ingrese un valor para y
3
Ingrese un valor para z
4
Ingrese un valor para m
5
El valor final de las variables es x=2, y=3, z=4, m=2

*/

/*. ¿Que hace este programa?
Este programa cambia el estado de las variables según el valor de x e y
¿Cual es el valor final de la variable m?
m es igual a x si x es menor a y , sino es igual a y
*/