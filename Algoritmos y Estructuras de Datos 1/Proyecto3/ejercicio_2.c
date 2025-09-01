#include <stdio.h>
#include <stdbool.h>

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

char* bol (int vof)
{
	if (vof == 1)
	{
		return "True";
	} else {
		return "False";
};
}

void dos ()
{
  int x, y, z, b, w ;
      x= pedir_entero('x');
      y= pedir_entero('y');
      z= pedir_entero('z');
      b= pedir_entero('b');
      w= pedir_entero('w');

      printf ("para valores de x=%d, la funcion x mod 4 = %s\n",x, bol(x % 4 == 0));
      printf ("para valores de x=%d, y=%d, z=%d la funcion x+y == 0 && y-x == (-1) * z = %s\n", x, y, z, bol( x+y == 0 && y-x == (-1) * z));
      printf ("para valores de b=%d, w=%d la funcion not b && w = %s\n", b, w, bol (!b && w));
	  
}

int main (void) {
  dos();
  return 0;
}

/*Encontre las soluciones (en la funcion antes de aplicar pedir_entero) tal que
Expresion                          Valor
x % 4 == 0                         True
x + y == 0 && y - x == (-1) * z    True
not b && w                         False

y son:
PS C:\Users\seren\OneDrive\Documentos\famaf\algo1\Proyecto3> ./dos
Ingrese un valor para x
8
Ingrese un valor para y
-8
Ingrese un valor para z
16
Ingrese un valor para b
5
Ingrese un valor para w
-5
para valores de x=8, la funcion x mod 4 = True
para valores de x=8, y=-8, z=16 la funcion x+y == 0 && y-x == (-1) * z = True
para valores de b=5, w=-5 la funcion not b && w = False
*/
