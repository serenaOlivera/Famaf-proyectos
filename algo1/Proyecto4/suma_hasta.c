//incluyo las librerias que voy a utilizar
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*3. (Funcion suma hasta) Crear un archivo llamado suma hasta.c, que contenga la funcion
int suma_hasta(int n)
que toma un numero entero n como argumento, y devuelve la suma de los primeros n
naturales. En la funcion main pedir al usuario que ingrese el entero n, si es negativo imprimir
un mensaje de error, y si es no negativo imprimir el resultado devuelto por suma_hasta.
Ayuda: La funcion puede hacer un ciclo o directamente usar la formula de Gauss.
*/

//defino mi funcion
int suma_hasta (int n){
        while (n>0){
        int i;
        i=n+suma_hasta(n-1);
        return i;
        }
    return 0;
}


int main (){
    int n;
    printf("Ingrese un entero positivo\n");
    scanf(" %d", &n);
    if (n<0){
        printf("El numero ingresado no es un entero positivo\n");
        assert (n>0);
    } else{
        suma_hasta(n);
        printf("La suma de los primeros %d numeros es igual a %d",n, suma_hasta(n));
    }
    
    return 0;
}