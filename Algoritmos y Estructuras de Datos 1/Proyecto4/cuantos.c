#include <stdio.h>
#include <stdbool.h>


/*2. (Funcion cuantos). Hacer un programa en un archivo nuevo cuantos.c que calcula cuantos
elementos menores, iguales y mayores a un numero hay en un arreglo. La funcion tiene el
siguiente prototipo:
struct comp_t cuantos(int tam, int a[], int elem)
donde la estructura comp_t se define como sigue:
struct comp_t {
int menores;
int iguales;
int mayores;
};

La funcion toma un tamano maximo de arreglo, el arreglo y un entero, y devuelve una
estructura con tres enteros que respectivamente indican cuantos elementos menores, iguales
o mayores al argumento hay en el arreglo. La funcion cuantos debe contener un unico ciclo.*/

//funcion que pide un arreglo
void pedir_arreglo(int n_max, int a[]){
    int i=0;
    while (i<n_max){
        printf("Ingrese el valor para la posicion %d\n",i);
        scanf("%d", &a[i]);
        i=i+1;
    }                                                 
    
}


struct comp_t {
int menores;
int iguales;
int mayores;
};

struct comp_t cuantos(int tam, int a[], int elem){
    struct comp_t numero;
    int posicion=0;
    numero.menores=0;
    numero.mayores=0;
    numero.iguales=0;
    while(posicion<=tam){
        if (a[posicion]<elem){
            numero.menores=numero.menores+1;
        }else if(a[posicion]>elem){
            numero.mayores=numero.mayores+1;
        }else if(a[posicion]==elem){
            numero.iguales=numero.iguales+1;
        }
        posicion=posicion+1;
    }
    printf("Hay %d numeros menores a %d en el arreglo\n", numero.menores, elem);
    printf("Hay %d numeros mayores a %d en el arreglo\n", numero.mayores, elem);
    printf("Hay %d numeros iguales a %d en el arreglo\n", numero.iguales, elem);

    return numero;
}


int main(){
    int n;
    printf("Ingrese el valor maximo del arreglo\n");
    scanf(" %d", &n);

    int a[n];
    pedir_arreglo(n,a);

    int elem;
    printf("Ingrese un numero con el que desea comparar todo el arreglo\n");
    scanf("%d", &elem);

    cuantos(n-1,a,elem);

    return 0;
}