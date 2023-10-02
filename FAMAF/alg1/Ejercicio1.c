#include <stdio.h>
#include <stdbool.h>

void unoA () 
{
	int x, y, z;
	printf ("Ingrese un valor para x\n");
	scanf ("%d", &x);
	printf ("Ingrese un valor para y\n");
	scanf ("%d", &y);
	printf ("Ingrese un valor para z\n");
	scanf ("%d", &z);
	
	printf ("para valores de x=%d, y=%d, z=%d la funcion x+y+1 = %d\n",x, y, z, x + y + 1);
	printf ("para valores de x=%d, y=%d, z=%d la funcion z * z + y * 45 - 15 * x = %d\n", x, y, z, z * z + y * 45 - 15 * x);
	printf ("para valores de x=%d, y=%d, z=%d la funcion y - 2 == (x * 3 + 1) mod 5 = %d\n", x, y, z, y - 2 == (x * 3 + 1) % 5);
	printf("para valores de x=%d, y=%d, z=%d la funcion y / 2 * x = %d\n", x, y, z, y / 2 * x);
	printf("para valores de x=%d, y=%d, z=%d la funcion y < x * z = %d\n", x, y, z, y < x * z);
	
	return;
}

int main (void) 
{
	unoA ();
	return 0;
}
*/En la ultima expresión el resultado en lenguaje "C" es de tipo Int porque "C" no tiene definido el tipo Bool
*/
