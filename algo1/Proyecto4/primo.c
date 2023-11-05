#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

/*15. (Funcion nesimo primo) En un archivo nuevo primo.c hacer una funcion
int nesimo_primo(int N)
que devuelve el n-esimo primo.
a) En la funcion main pedir al usuario que ingrese el entero n, si es negativo imprimir un
mensaje de error, y si es no negativo imprimir el resultado devuelto por nesimo_primo.
b) Modificar la funcion main, para que al ingresar un valor negativo, solicite un nuevo
valor hasta que se ingrese un n no negativo*/

bool es_primo (int n){
    int i=2;    
    if (n<=1){
        return false;
    }
    while(i*i<=n){
        if (n%i==0){
            return false;
        }
        i=i+1;
    }
    return true;
}

int nesimo_primo(int N){
    int contador=0;
    int numero=2;    //como n no puede ser<=1, no tomo ningun numero de ellos.
    while (contador<N){
        if (es_primo(numero)){
            contador=contador+1;
        }
        if (contador< N){
            numero=numero+1;
        }
    }
    return numero;
}

int main(){
    int n;
    printf("Ingrese un entero\n");
    scanf("%d", &n);

    while (n<0){
        printf("El numero ingresado debe ser positivo, intentelo de nuevo\n");
        printf("Ingrese un entero\n");
        scanf("%d", &n);
    }
    
    int resultado= nesimo_primo(n);
    printf("el %d-esimo numero primo es: %d\n",n,resultado);

    return 0;
}
