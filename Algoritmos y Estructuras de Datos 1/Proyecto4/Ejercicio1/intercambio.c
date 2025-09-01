#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*(Intercambio de variables) Traducir en intercambio.c el siguiente programa que
intercambia los valores de dos variables x e y de tipo Int.
z := x;
x := y;
y := z;
Nota: En todos los casos el programa en C, debe solicitar los valores de las variables
de entrada, e imprimir el resultado para que lo pueda ver el usuario.
*/

//defino mis funciones auxiliares



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

void intercambio (){
   char name, nombre, nomb;
    int x, y,z;

    printf("Ingrese un caracter para su guarda\n");
    scanf(" %c", &name);
    x= pedir_entero (name);

    printf("Ingrese un caracter para su guarda\n");
    scanf(" %c", &nombre);
    y= pedir_entero(nombre);

    printf("Ingrese un caracter para su guarda\n");
    scanf(" %c", &nomb);
    z= pedir_entero (nomb);

    int antx;
    antx=x;
    x=y;
    y=z;
    z=antx;

    imprimir_entero (name, x);
    imprimir_entero (nombre, y);
    imprimir_entero (nomb, z);
    
}

int main() {
    intercambio();
    return 0;
}