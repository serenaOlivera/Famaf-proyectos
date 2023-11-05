#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

/*
b) (Punto estrella) Hacer una segunda version del programa en el archivo minimos_estrella.c
y usar las funciones del ejercicio 8 en la fucnion main para que en caso de no haber
elementos pares no se muestre el resultado de minimo_pares() y en caso de no haber
impares no se muestre el resultado de minimo_impares()
*/


//funcion que pide un arreglo
void pedir_arreglo(int n_max, int a[]){
    while (n_max>=0){
    int i;
    printf("Ingrese el valor para la posicion %d\n", n_max);
    scanf(" %d", &i);
    a[n_max]= i;
    n_max= n_max-1;
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


// verifica que existan multiplos de un numero en el arreglo
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



// devuelve el minimo par del arreglo
int minimo_pares(int tam, int a[]){
    int posicion=0;
    int el_minimo=INT_MAX;
    while (posicion<= tam){
        if (a[posicion]%2==0 && a[posicion]<el_minimo){
            el_minimo=a[posicion];
        }else{

        }
        posicion=posicion+1;
    }
 
    return el_minimo;
}

//devuelve el minimo impar del arreglo
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

//funcion que me imprime si son pares o impares
void son_par_impar(int n, int a[]){

    if (existe_multiplo(2,n,a)== true && !todos_pares(n-1,a)){
        printf("El numero impar mas chico es: %d\n", minimo_impares(n-1,a));
        printf("El numero par mas chico es: %d\n", minimo_pares(n-1,a));
    } else if (todos_pares(n-1,a)==true){
        printf("El numero par mas chico es: %d\n", minimo_pares(n-1,a));
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
    son_par_impar(n,a);

    return 0;
}

