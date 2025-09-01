#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*
7. (Arreglos, Funcion sumatoria). Hacer un programa en un archivo con nombre sumatoria.c
que contenga la funcion
int sumatoria(int tam, int a[])
que recibe un tamano maximo de arreglo y un arreglo como argumento, y devuelve la suma
de sus elementos (del arreglo). En la funcion main pedir los datos del arreglo al usuario
asumiendo un tamano constante previamente establecido (en tiempo de compilacilacion).

*/

// copio la funcion del ej 6 que pide los valores de un arreglo

void pedir_arreglo(int n_max, int a[]){
    while (n_max>=0){
    int i;
    printf("Ingrese el valor para la posicion %d\n", n_max);
    scanf(" %d", &i);
    a[n_max]= i;
    n_max= n_max-1;
    }
}

int sumatoria(int tam, int a[]){
    int sum;
    int i=0;

    while(i!=tam){
    sum = sum + a[i];
    i= i+1;    
    }
    printf("La suma de todos los valores del arreglo es: %d\n", sum);
    return 0;
}


int main(){
    int n=4;
    assert (n>0);
    
    int a[n];
    pedir_arreglo(n-1, a);

    sumatoria(n-1, a);
    return 0;
}