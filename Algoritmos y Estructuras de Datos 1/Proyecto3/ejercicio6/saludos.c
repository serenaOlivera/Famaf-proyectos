#include <stdio.h>
#include <stdbool.h>

/*      Enunciado:

d) En un archivo saludos.c implementar las siguientes funciones (ademas de la main):
    --una que imprime el string "hola", que no toma ni devuelve parametros, con
    prototipo:
        void imprimir_hola(void)
    --similar a la anterior con la el string "chau":
        void imprimir_chau(void)
ese programa tiene que imprimir dos veces “hola” seguido de dos veces “chau”, llamando
 a las dos ultimas funciones desde el main.

ayuda: Se debe entender como corre el flujo de ejecucion de este programa leyendo su
codigo fuente.

*/

//defino mis funciones

void imprimir_hola(){
    printf("hola\n");
}

void imprimir_chau(){
    printf("chau\n");
}

int main(){
    imprimir_hola();
    imprimir_hola();
    imprimir_chau();
    imprimir_chau();

    return 0;
}