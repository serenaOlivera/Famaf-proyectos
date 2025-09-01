#include <stdio.h>
#include <stdbool.h>

/*(Asignaciones multiples) Considerar las siguientes asignaciones multiples
        {Pre: x = X, y = Y}
        x, y := x + 1, x + y
        {Post: x = X + 1, y = X + Y}
a) Escribir un programa equivalente que solo use secuencias de asignaciones simples.
b) Traducir los programas resultantes a C en archivos nuevos llamados multiple1.c y
multiple2.c respectivamente.
 */

/*a) Escribo el programa con asignaciones simples
        {Pre: x = X, y = Y}
        y:= x+y
        {Post: x = x, y = X + Y}
        x:= x + 1
        {Postfinal: x = X + 1, y = X + Y}

*/

/*b) Traduzco el programa a C*/


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

void multiple1(){
    int x;
    int y;
    char nombre;
    char name;

    printf("Ingrese un caracter para su guarda\n");
    scanf(" %c", &name);
    x= pedir_entero(name);

    printf("Ingrese un caracter para su guarda\n");
    scanf(" %c", &nombre);
    y=pedir_entero(nombre);

    y= x+y;
    x= x+1;
    imprimir_entero(name, x);
    imprimir_entero(nombre, y);
}

int main(){
    multiple1();
    return 0;
}