
#include <stdio.h>
#include <stdbool.h>


// defino  mis funciones auxuliares

int pedir_entero (char name)
{
    int x;
    printf("Ingrese un valor para la guarda %c\n", name);
    scanf(" %d", &x);

    return x;
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

void unoA () 
{
	int x, y, z;
	x= pedir_entero('x');
	y= pedir_entero('y');
	z= pedir_entero('z');
	
	printf ("para valores de x=%d, y=%d, z=%d la funcion x+y+1 = %d\n",x, y, z, x + y + 1);
	printf ("para valores de x=%d, y=%d, z=%d la funcion z * z + y * 45 - 15 * x = %d\n", x, y, z, z * z + y * 45 - 15 * x);
	printf ("para valores de x=%d, y=%d, z=%d la funcion y - 2 == (x * 3 + 1) mod 5 = %s\n", x, y, z, bol (y - 2 == (x * 3 + 1) % 5));
	printf("para valores de x=%d, y=%d, z=%d la funcion y / 2 * x = %d\n", x, y, z, y / 2 * x);
	printf("para valores de x=%d, y=%d, z=%d la funcion y < x * z = %s\n", x, y, z,bol (y < x * z));
	
	return;
}

int main (void) 
{
	unoA ();
	return 0;
}
/*PS C:\Users\seren\OneDrive\Documentos\famaf\algo1\Proyecto3> gcc -Wall -Wextra -std=c99 ejercicio_1.c -o unoa
PS C:\Users\seren\OneDrive\Documentos\famaf\algo1\Proyecto3> ./unoa
Ingrese un valor para x
7
Ingrese un valor para y
3
Ingrese un valor para z
5
para valores de x=7, y=3, z=5 la funcion x+y+1 = 11
para valores de x=7, y=3, z=5 la funcion z * z + y * 45 - 15 * x = 55
para valores de x=7, y=3, z=5 la funcion y - 2 == (x * 3 + 1) mod 5 = False
para valores de x=7, y=3, z=5 la funcion y / 2 * x = 7
para valores de x=7, y=3, z=5 la funcion y < x * z = True
PS C:\Users\seren\OneDrive\Documentos\famaf\algo1\Proyecto3> ./unoa
Ingrese un valor para x
1
Ingrese un valor para y
10
Ingrese un valor para z
8
para valores de x=1, y=10, z=8 la funcion x+y+1 = 12
para valores de x=1, y=10, z=8 la funcion z * z + y * 45 - 15 * x = 499
para valores de x=1, y=10, z=8 la funcion y - 2 == (x * 3 + 1) mod 5 = False
para valores de x=1, y=10, z=8 la funcion y / 2 * x = 5
para valores de x=1, y=10, z=8 la funcion y < x * z = False
*/


