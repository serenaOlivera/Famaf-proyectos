#include <stdio.h>
#include <stdbool.h>

/* (Funcion prim iguales) Programar en el archivo prim_iguales.c la funcion
int prim_iguales(int tam, int a[])
que siendo tam el tamano del arreglo a[] devuelve la longitud del tramo inicial mas largo
cuyos elementos son todos iguales (parecida a la funcion primIguales del Proyecto 1).
a) En la funcion main se le debe pedir al usuario los elementos del arreglo asumiendo un
tamano constante previamente establecido (en tiempo de compilacion) y luego mostrar
el resultado de la funcion prim_iguales por pantalla
b) (Punto Estrella) Mostrar por pantalla el mayor tramo inicial del arreglo a[] que tiene
a todos sus elementos iguales.
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

int prim_iguales (int tam, int a[]){
    int posicion=0;
    int longitud_inicial=1;
    int longitud_max=1;
    while(posicion<= tam){
        if (a[posicion]==a[posicion+1]){
           longitud_inicial=longitud_inicial+1;
           if (longitud_inicial>longitud_max){
            longitud_max=longitud_inicial;
           }
        }else{
            longitud_inicial=1;
        }
        posicion=posicion+1;
    }
    return longitud_max;
}


int prim_iguales_estrella(int tam, int a[]){
    int posicion=0;
    while(posicion<tam){
        if(a[posicion]<=a[posicion-1]){
            printf("%d\n",a[posicion]);
            posicion=posicion+1;
            while(posicion<=tam && a[posicion]==a[posicion+1]){
                printf("%d \n", a[posicion]);
                posicion=posicion+1;
            }
        }else{
            break;
        }
    }
 return 0;  
}


int main(){
    int n=4;
    int a[n];

    pedir_arreglo(n,a);   //pido los elementos del arreglo
    int longitud_maxima=prim_iguales(n-1,a);
    printf("La longitud maxima del tramo inicial de elementos iguales de un arreglo es: %d\n ", longitud_maxima);
    printf("-----Ejercicio estrella-----\n");
    prim_iguales_estrella(n-1,a);

    return 0;
}