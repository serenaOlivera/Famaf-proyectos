#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*
8. (Multiplos) . Hacer un programa en un archivo multiplos.c que contenga las siguientes
funciones:
bool todos_pares(int tam, int a[])
bool existe_multiplo(int m, int tam, int a[])
La primera recibe un tamano maximo de arreglo y un arreglo como argumento devolviendo
true cuando todos los elementos del arreglo a[] son numeros pares y false en caso
contrario. La segunda determina si hay en el arreglo a[] algun elemento que es multiplo
de m. En la funcion main se debe pedir al usuario los elementos del arreglo (asumiendo un
tamano constante) y luego permitirle elegir que funcion ejecutar. En caso que se elija la
funcion existe_multiplo() se le debe pedir al usuario un valor para m.
*/

//funcion que me devuelve true o false segun el numero sea 0 o 1
char vof(int a){
    if (a==1){
        printf("True\n");
    }else{
        printf("False\n");
    }
}

//funcion que pide un arreglo
void pedir_arreglo(int n_max, int a[]){
    int i=0;
    while (i<n_max){
        printf("Ingrese el valor para la posicion %d\n",i);
        scanf("%d", &a[i]);
        i=i+1;
    }                                                 
    
}

// verifica que todos los elementos en el arreglo sean pares
bool todos_pares(int tam, int a[]){
    int i=0;
    bool t = true;
    while(i!=tam){
    if (a[i]%2==0){
        
    }else{
        t=false;
    }
      i= i+1;  
    }
    return t;
}


bool existe_multiplo(int m, int tam, int a[]){
    int i=0;
    bool t = false;

    while (i!=tam){
    if (m% a[i]==0){
        t=true;
    }else{
    }
    i=i+1;
    }
    return t;
    
}

int main(){
    int n;
    printf("Ingrese el valor maximo del arreglo\n");
    scanf(" %d", &n);
    assert (n>0);
    
    int a[n];
    pedir_arreglo(n, a);

    int h;
    printf("Ingrese 0 si quiere ejecutar todos_pares y 1 si quiere ejecutar existe_multiplo\n");
    scanf(" %d", &h);
    if (h==0){

    int t;
    t=todos_pares(n, a);
    printf(" %c",vof(t));

    } else if (h==1){

    int m;
    printf("Ingrese un entero para verificar si hay al menos un multiplo de el en el arreglo\n");
    scanf(" %d", &m);
    assert (m>0);
    int ñ = existe_multiplo(m, n, a);
    printf(" %c", vof(ñ));

    } else{
        printf("El entero ingresado no es valido\n");
    }

    return 0;
}