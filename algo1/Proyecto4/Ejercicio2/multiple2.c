#include <stdio.h>
#include <stdbool.h>

/*(Asignaciones multiples) Considerar las siguientes asignaciones multiples
        {Pre: x = X, y = Y, z = Z}
        x, y, z := y, y + x + z, y + x
        {Post: x = Y, y = Y + X + Z, z = Y + X}

a) Escribir un programa equivalente que solo use secuencias de asignaciones simples.
b) Traducir los programas resultantes a C en archivos nuevos llamados multiple1.c y
multiple2.c respectivamente.
 */

/*a) Escribo el programa con asignaciones simples
        {Pre: x = X, y = Y, z = Z}
        z:= y+x
        {Post1: x= X, y=Y, z=Y+X}
        x:= y
        {Post2: x=Y, y=Y,z=X+Y}
        y:= z+Z
        {Postfinal: x=Y, y=Y+X+Z, z=X+Y}

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

void multiple2(){
    int x,y,z,antz;
    char nombre,name,nom;

    printf("Ingrese un caracter para su guarda\n");
    scanf(" %c", &name);
    x= pedir_entero(name);

    printf("Ingrese un caracter para su guarda\n");
    scanf(" %c", &nombre);
    y=pedir_entero(nombre);
    
    printf("Ingrese un caracter para su guarda\n");
    scanf(" %c", &nom);
    z=pedir_entero(nom);

    antz= z;
    z=y+x;
    x=y;
    y=z+antz;
    imprimir_entero(name, x);
    imprimir_entero(nombre, y);
    imprimir_entero(nom, z);

}

int main(){
    multiple2();
    return 0;
} 