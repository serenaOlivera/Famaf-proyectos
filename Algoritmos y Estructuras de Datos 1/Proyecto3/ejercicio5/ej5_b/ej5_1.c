#include <stdio.h>
#include <stdbool.h>

/* Enunciado:
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


// Traduccion del ejercicio 1

void uno()
{
  int x=0;
  int y=0;
  int i=0;
  x=pedir_entero('x');
  y=pedir_entero('y');
  i=pedir_entero('i');

  i = 0;
  while (x>=y)
   {
     x=x-y;
     i = i+1;
     printf("El valor de las variables es de x=%d, y=%d, i=%d\n", x, y, i);
     
   }
  return;
    
}

int main(void)
{
  printf("-----Traduccion del ejercicio 1-----\n");
  uno();
  return 0; 
}

/* Resultados pedidos 

    Luego de iteracion 1:
    x:=10, y:=3, i:=1
    Luego de iteracion 2:
    x:=7, y:=3, i:=2
    Luego de iteracion 3:
    x:=4, y:=3, i:=3
    Luego de iteracion 1:
    x:=1, y:=3, i:=4

*/
