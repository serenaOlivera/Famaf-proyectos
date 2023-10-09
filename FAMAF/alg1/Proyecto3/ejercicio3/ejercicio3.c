#include <stdio.h>
#include <stdbool.h>

/* Traducı al lenguaje C los programas 1.a, 1.b y 1.c del p´actico que se encuentra en este
enlace. El estado σ0 debe solicitarse al usuario utilizando el comando scanf(). Luego, ejecute cada
programa 3 veces con diferentes valores de las variables solicitadas y escriba los valores del
estado final resultante en la siguiente tabla:
programa            usuario ingresa un σ0        produce una salida σ
-----------------------------------------------------------------------
1.a ejecucion 1|          x:=1                          x:=5
-----------------------------------------------------------------------
1.a ejecucion 2|          x:=5                          x:=5
-----------------------------------------------------------------------
1.a ejecucion 3|          x:=9                         x:=5
-----------------------------------------------------------------------
1.b ejecucion 1|       x:=2, y:=5                 x:=7, y:=10
-----------------------------------------------------------------------
1.b ejecucion 2|       x:=2, y:=3                 x:=5, y:=6
-----------------------------------------------------------------------
1.b ejecucion 3|      x:=7, y:=6                  x:=13, y:=12
-----------------------------------------------------------------------
1.c ejecucion 1|     x:=2, y:=5                  x:=12, y:=10
-----------------------------------------------------------------------
1.c ejecucion 2|     x:=5, y:=6                  x:=17, y:=12
-----------------------------------------------------------------------
1.c ejecucion 3|    x:=5, y:=9                  x:=23, y:=18
*/

/* Agrego mis funciones auxiliares: */
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

/* dearrolllo las funciones principales*/

void unoa ()
{
  int x;
  x=pedir_entero('x');
  x = 5;
  imprimir_entero('x', x);

}

void unob ()
{
    int x, y;
    x=pedir_entero('x');
    y=pedir_entero('y');

    x = x+y;
    imprimir_entero('x',x);
    y = y+y;
    imprimir_entero('y',y);
    
}

//ejercicio 1c ( y=y+y y x=x+y (notar que x toma el nuevo valor de y no el del input ))

void unoc()
{
    int x, y;
    x=pedir_entero('x');
    y=pedir_entero('y');

    y=y+y;
    imprimir_entero('y',y);
    x = x+y;
    imprimir_entero('x',x);
    

}

int main (void)
{
    printf("-----Traduccion del ejrcicio 1a------\n");
    unoa();
    printf("-----Traduccion del ejrcicio 1b------\n");
    unob();
    printf("-----Traduccion del ejrcicio 1c------\n");
    unoc ();
    return 0;
}
