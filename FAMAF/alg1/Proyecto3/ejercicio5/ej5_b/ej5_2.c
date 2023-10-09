//FIJARSE QUE ESTA MAL

#include <stdio.h>
#include <stdbool.h>

/*      Enunciado
 Traducı a lenguaje C los programas que siguen a continuacion, agregando las instrucciones necesarias
 para que el usuario pueda ingresar los valores. Luego, completa los
 estados, donde el estado a completar es el resultado de realizar 1, 2, 3 o 4 iteraciones
 del ciclo. Una iteracion es la ejecucion completa del cuerpo del ciclo.
*/


/*Defino mis funciones auxiliares*/

int pedir_entero (char name)
{
    int x;
    printf("Ingrese un valor para la guarda %c\n", name);
    scanf(" %d", &x);

    return x;
}


void imprimir_entero (char name, int x)
{
    printf("El valor de la guarda %c es %d\n", name, x);
}


// Traduccion del ejercicio 2 
  
/*Ahora copio la funcion del ejercicio 2c que me devuelve True si mi int es 1, y False otherwise*/

char* int_a_bol (int vof)
{
	if (vof == 1)
	{
		return "True";
	} else 
    {
		return "False";
    }
}

/*Ahora, creo la funcion 2*/

int main(void)
{
    int x=0;
    int i=0;
    int res=false;

    x=pedir_entero('x');

    i=2;
    res=true;
    
    while (i<x && res)
        {  
            res = res && ((x % i)!=0);
            i = i+1;
            printf ("Los valores de las variables son x=%i, i=%i, res=%s\n", x, i, int_a_bol(res));        
        }
    return 0;
}

/*Ejemplos de ejecución

PS C:\Users\seren\OneDrive\Documentos\famaf\algo1\Proyecto3\ejercicio5\ej5_b> gcc -Wall -Wextra -std=c99 ej5_2.c  -o do
PS C:\Users\seren\OneDrive\Documentos\famaf\algo1\Proyecto3\ejercicio5\ej5_b> ./do
Ingrese un valor para x
5
Los valores de las variables son x=5, i=3, res=True
Los valores de las variables son x=5, i=4, res=True
Los valores de las variables son x=5, i=5, res=True



PS C:\Users\seren\OneDrive\Documentos\famaf\algo1\Proyecto3\ejercicio5\ej5_b> gcc -Wall -Wextra -std=c99 ej5_2.c  -o do
PS C:\Users\seren\OneDrive\Documentos\famaf\algo1\Proyecto3\ejercicio5\ej5_b> ./do
Ingrese un valor para x
7
Los valores de las variables son x=7, i=3, res=True
Los valores de las variables son x=7, i=4, res=True
Los valores de las variables son x=7, i=5, res=True
Los valores de las variables son x=7, i=6, res=True
Los valores de las variables son x=7, i=7, res=True


En conclusión esta función te dice si un numero es impar
*/