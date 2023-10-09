#include <stdio.h>
#include <stdbool.h>

/* Enunciado:
b) entradas_bool.c que lee una variable de tipo bool y la imprime por pantalla. El
programa debe utilizar dos funciones a definir (ademas de la funcion main):
    --una funcion que le pide un booleano al usuario y lo devuelve, con prototipo:
        bool pedir_booleano(void)
    --que toma un booleano como parametro e imprime un mensaje "verdadero" o
    "falso" segun sea su valor de verdad:   
        void imprimir_booleano(bool x)
        4
    --Agregar a las funciones un parametro llamado name de tipo char con la misma
    funcionalidad descripta en el tercer ´ıtem del apartado 6a

*/

/*Primero, creo mis funciones auxiliares*/


bool pedir_booleano (char name)
{
    int valor;
    printf("Ingrese un booleano (0 para False, 1 para True) para la guarda %c\n", name);
    scanf(" %d", &valor);
    
    if (valor == 0){
        return false;
    } else if (valor == 1) {
        return true;
    } else{
        return false;
    }
}

void imprimir_booleano (char name, bool x)
{
    if (x==1)
    {
        printf(" %c = True\n", name);
    } else if (x==0){
        printf(" %c = False\n", name);
    } else 
    {
        printf("El valor ingresado para la guarda %c no es un booleano\n", name);
    }

    return;
}
/*Ahora, las llamo en el main para ejecutarlas*/

int main()
{ 
    printf("-----Ejercicio con el parametro name-----\n");
    char name;
    bool n;
    printf("Ingrese un caracter para su guarda\n)");
    scanf (" %c", &name);
    n= pedir_booleano(n);
    imprimir_booleano(name, n);

    return 0;
}

