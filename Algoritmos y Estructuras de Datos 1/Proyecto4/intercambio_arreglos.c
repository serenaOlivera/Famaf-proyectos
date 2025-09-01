#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*). Hacer un programa en el archivo nuevo intercambio_arreglos.c
que contenga la siguiente funcion:
void intercambiar(int tam, int a[], int i, int j)
3
que recibe un tamano maximo de arreglo, un arreglo y dos posiciones como argumento, e
intercambia los elementos del arreglo en dichas posiciones. En la funcion main pedirle al
usuario que ingrese los elementos del arreglo y las posiciones, chequear que las posiciones
esten en el rango correcto y luego imprimir en pantalla el arreglo modificado.
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

void intercambiar (int tam, int a[], int i, int j){
    int i_antes;
    assert (i<= tam);
    assert (j<= tam);
    i_antes=a[i];
    a[i]= a[j];
    a[j]= i_antes;

}

// funcion que imprime los elementos de un arreglo
 void imprimo_elementos (int a[], int tam){
    printf("Los valores de los elementos del arreglo son: \n");
    while (tam>=0){
        printf("a[%d] = %d\n", tam, a[tam]);
        tam = tam-1;

    }
 }


int main(){
    int n;
    printf("Ingrese el valor maximo del arreglo\n");
    scanf(" %d", &n);
    assert (n>0);
    
    int a[n];
    pedir_arreglo(n, a);
    imprimo_elementos(a, n-1);


    int i,j;
    printf("Ingrese la posicion que desea cambiar\n");
    scanf("%d", &i);
    assert (i<n);
    printf("Ingrese la otra posicion que desea cambiar\n");
    scanf("%d", &j);
    assert (j<n);

    intercambiar(n-1, a, i, j);
    imprimo_elementos(a, n-1);

    return 0;
}