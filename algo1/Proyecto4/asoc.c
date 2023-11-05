#include <stdio.h>
#include <stdbool.h>

/*14. (Arreglo de asociaciones) En asoc.c programar la funcion
bool asoc_existe(int tam, struct asoc a[], clave_t c)
Donde la estructura struct asoc y los tipos clave_t, valor_t se definen como:
typedef char clave_t;
typedef int valor_t;
struct asoc {
clave_t clave
valor_t valor
};
El llamado a asoc_existe(tam, a, c) debe indicar si la clave c se encuentra en el arreglo
de asociaciones a[]. En la funcion main pedir al usuario los datos del arreglo (asumiendo un
tamano constante) y luego pedir una clave. Finalmente usar la funcion asoc_existe para
verificar la existencia de la clave ingresada y mostrar por pantalla un mensaje indicando si la
clave existe o no en el arreglo de asociaciones.
*/

typedef char clave_t;
typedef int valor_t;

struct asoc {
    clave_t clave;
    valor_t valor;
};

void pedir_arreglo(int n_max, struct asoc a[]){
    int i=0;
    while (i<n_max){
        printf("Ingrese la clave para la posicion %d\n",i);
        scanf(" %c", &a[i].clave);
        printf("Ingrese el valor para la posicion %d\n",i);
        scanf("%d", &a[i].valor);
        i=i+1;
    }                                                 
    
}

bool asoc_existe(int tam, struct asoc a[], clave_t c){
    int posicion=0;
    while(posicion<=tam){
        if (a[posicion].clave==c){
            return true;
        }
        posicion=posicion+1;
    }
    return false;
}

int main(){
    int n=5;
    struct asoc a[n];
    pedir_arreglo(n,a);

    clave_t c;
    printf("Ingrese una clave (solo de letras)\n");
    scanf(" %c", &c);

    if (asoc_existe(n,a,c)==true){
        printf("La clave se encuentra en el arreglo");
    }else{
        printf("La clave no se encuentra en el arreglo");
    }
    
    return 0;
}
