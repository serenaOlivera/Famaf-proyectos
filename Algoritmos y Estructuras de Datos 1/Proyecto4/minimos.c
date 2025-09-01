#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

/*
10. (Mınimos). Hacer un programa en un archivo con nombre minimos.c que contenga las
siguientes funciones:
int minimo_pares(int tam, int a[])
int minimo_impares(int tam, int a[])
Estas funciones reciben un tamano maximo de arreglo y un arreglo como argumentos,
devolviendo el elemento par mas pequeno del arreglo y el elemento impar mas pequeno del
arreglo respectivamente.
a) En la funcion main se debe pedir al usuario los elementos del arreglo (asumiendo un
tamano constante) y luego mostrar por pantalla:
El resultado de minimo_pares(), para el arreglo ingresado
El resultado de minimo_impares(), de nuevo, para el arreglo ingresado
El elemento mınimo del arreglo ingresado (utilizando el resultado de ambas funciones
para calcularlo).
Pueden definir alguna funcion auxiliar si les resulta necesario.
NOTA: Investigar las constantes definidas en la librerıa <limits.h> para definir el
neutro de la operacion mınimo
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

//busca el minimo par de un arreglo
int minimo_pares(int tam, int a[]){
    int posicion=0;
    int el_minimo=INT_MAX;
    while (posicion<= tam){
        if (a[posicion]%2==0 && a[posicion]<el_minimo){  //compara el valor en la posicion con el ult min. guardado
            el_minimo=a[posicion];
        }else{

        }
        posicion=posicion+1;
    }
 
    return el_minimo;
}

int minimo_impares(int tam, int a[]){
    int posicion=0;
    int el_minimo=INT_MAX;
    while (posicion<= tam){
        if (a[posicion]%2!=0 && a[posicion]<el_minimo){
            el_minimo=a[posicion];
        }else{

        }
        posicion=posicion+1;
    }
    return el_minimo;
}

//funcion que elige que texto imprimir segun el caso 
void que_imprimo(int n, int a[]){
    if (minimo_pares(n-1,a)==0){
        printf("No hay elementos pares en el array\n");
    } else{
        printf("El numero par mas chico es: %d\n", minimo_pares(n-1,a));
    }

    if (minimo_impares(n-1,a)==0){
        printf("No hay elementos impares en el array\n");
    } else{
        printf("El numero impar mas chico es: %d\n", minimo_impares(n-1,a));
    }

    if (minimo_impares(n-1,a)<minimo_pares(n-1,a)){
        printf("El valor mas chico de todo el array es: %d \n", minimo_impares(n-1,a));
    } else if (minimo_pares(n-1,a)<minimo_impares(n-1,a)){
        printf("El valor mas chico de todo el array es: %d \n", minimo_pares(n-1,a));
    }
}

int main(){
    int n=4;
    assert (n>0);
    
    int a[n];
    pedir_arreglo(n, a);
    minimo_pares(n-1, a);
    minimo_impares(n-1,a);
    que_imprimo(n,a);


    return 0;
}