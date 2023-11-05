#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*
6. (Arreglos, entrada-salida) Escribir un programa que solicite el ingreso de un arreglo de enteros
int a[] y luego imprime por pantalla. El programa debe utilizar dos nuevas funciones ademas
de la funcion main:
    --una que dado un tamano maximo de arreglo y el arreglo, solicita los valores para el
    arreglo y los devuelve, guardandolos en el mismo arreglo int a[]; funcion con prototipo
    (tambien conocido como signatura o firma):
    void pedir_arreglo(int n_max, int a[])
    --otra que imprime cada uno de los valores del arreglo int a[], de prototipo:
    void imprimir_arreglo(int n_max, int a[])
*/

//funcion que pide un arreglo
void pedir_arreglo(int n_max, int a[]){
    int i=0;
    while (i<n_max){
        printf("Ingrese el valor para la posicion %d\n",i);
        scanf("%d", &a[i]);
        i=i+1;
    }                                                 
    
}

void imprimir_arreglo(int n_max, int a[]){
    printf("a[%d]= %d\n", n_max, a[n_max]);
}


int main(){
    int n;
    printf("Ingrese el valor maximo del arreglo\n");
    scanf(" %d", &n);
    assert (n>0);
    
    int a[n];
    pedir_arreglo(n, a);

    while (n>0){
        imprimir_arreglo(n-1, a);
        n= n-1;
    }
    return 0;
}