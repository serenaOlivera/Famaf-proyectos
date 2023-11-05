#include <stdio.h>


/* Enunciado:
Escribir el siguiente programa:
--entradas.c que lee una variable de tipo int y la imprime por pantalla. En esta ocasion
el programa debe utilizar dos funciones a definir (ademas de la funcion main):
    --una funcion que le pide un entero al usuario y lo devuelve, con prototipo:
    int pedir_entero(void)
    Recordar avisarle al usuario mediante un mensaje que se espera que ingrese un
    valor.
    --que toma un entero como parametro y lo imprime:
    void imprimir_entero(int x)
    --Pensa como agregar un parametro mas llamado name de tipo char a las funciones
    anteriores y usarlo en el mensaje que se muestra al usuario. Entonces por ejemplo
    para la funcion pedir_entero si se ejecuta:
    n = pedir_entero('n')
    deberıa indicarse en el mensaje que se esta pidiendo un valor para almacenar en la
    variable de nombre n. Notar que no hay forma de impedir que alguien use ”mal”la
    funcion:
    x = pedir_entero('n')
    en ese caso el mensaje indicara que el valor se almacena en n aunque en realidad
    se guarda en una variable llamada x.
    Escribı de nuevo ambas funciones con este parametro extra (debe estar como
    primer parametro de las funciones).
*/

/*Primero, defino mis funciones auxiliares*/


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


/*Ahora llamo a mis funciones en el main tomandolas como parametro una de la otra*/

int main ()
{
    printf("-----Ejercicio con el parametro name-----\n");
    char name;
    int n;
    printf("Ingrese un caracter para su guarda\n");
    scanf(" %c", &name);
    n=pedir_entero(name);
    imprimir_entero(name, n);

    return 0;
}

