#include <stdio.h>
#include <float.h>

/*13. (Funcion stats). Hacer un programa en un archivo nuevo stats.c, que calcula el mınimo, el
maximo, y el promedio de un arreglo no vacıo de numeros flotantes (tipo float). La funcion
tiene el siguiente prototipo:
struct datos_t stats(int tam, float a[])
donde la estructura datos_t se define como sigue:
struct datos_t {
float maximo;
float minimo;
float promedio;
};
La funcion pedida debe implementarse con un unico ciclo. En la funcion main pedir al usuario
los datos del arreglo e imprimir en pantalla los tres valores devueltos por la funcion.

*/

//funcion que pide un arreglo
void pedir_arreglo(int n_max, float a[]){
    int i=0;
    while (i<n_max){
        printf("Ingrese el valor decimal para la posicion %d\n",i);
        scanf("%f", &a[i]);
        i=i+1;
    }                                                 
    
}

struct datos_t {
float maximo;
float minimo;
float promedio;
};

struct datos_t stats(int tam, float a[]){
    struct datos_t stat;
    int posicion=0;
    stat.minimo=FLT_MAX;
    stat.maximo=FLT_MIN;
    while (posicion<=tam){
        if(a[posicion]<stat.minimo){
            stat.minimo=a[posicion];
        }else{

        }
        if (a[posicion]>stat.maximo){
            stat.maximo=a[posicion];
        }else{
            break;
        }
        posicion=posicion+1;
    }
    stat.promedio=(stat.minimo+stat.maximo)/2;
    
    printf("El minimo valor del arreglo es: %f\n",stat.minimo);
    printf("El maximo valor del arreglo es: %f\n",stat.maximo);
    printf("El promedio entre el minimo y maximo del arreglo es: %f\n",stat.promedio);

    return stat;
}

int main(){
    int n;
    printf("Ingrese el valor maximo del arreglo\n");
    scanf(" %d", &n);

    float a[n];
    pedir_arreglo(n,a);

    stats(n-1,a);

    return 0;
}
