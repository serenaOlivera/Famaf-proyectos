#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*b) Los ejemplos a continuacion han sido vistos en el teorico practico. Para cada uno de
ellos, se debe obtener la pre y post condicion y la derivacion. Luego, se debe traducir a
Lenguaje C el programa y las pre y post condiciones utilizando el comando assert.


(Valor Absoluto) Especificar un programa que calcule el valor absoluto de un
numero entero. Verificar que el programa es correcto, y luego traducir el programa
a C en un archivo nuevo llamado absoluto.c.*/

void valor_absoluto (int x){
    if (x>=0){
        x=x;
        printf("El valor absoluto de %d es %d", x, x);
    } else if (x<=0){
        int z;
        z= -x;
        printf("El valor absoluto de %d es %d", x, z);
    }
}

int pedir_entero (char name)
{
    int x;
    printf("Ingrese un valor para la guarda %c\n", name);
    scanf(" %d", &x);

    return x;
}



int main (){
    char name;
    int x;
    printf("Ingrese un caracter para su guarda\n");
    scanf(" %c", &name);
    x= pedir_entero(name);

    valor_absoluto(x);

    return 0;
}