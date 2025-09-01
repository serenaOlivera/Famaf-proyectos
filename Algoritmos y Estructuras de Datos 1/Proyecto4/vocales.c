#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*
4. (vocales) Crear un archivo vocales.c que contenga la funcion:
bool es_vocal(char letra)
que dado el caracter letra devuelve true si es una vocal y false en caso contrario. En la
funcion main se le debe solicitar al usuario que ingrese un caracter y luego se debe mostrar
un mensaje que indique si dicho caracter es una vocal o no segun el resultado de la funcion
es_vocal(). Tener en cuenta vocales mayusculas y minusculas.
NOTA: Definir una funcion que pida un caracter analoga a pedir_entero() pero para el
tipo char.
NOTA: Recordar usar %c en vez de %d en el uso de scanf() y printf() para obtener /
mostrar caracteres al usuario.
*/


//defino la funcion analoga a pedir entero pero con char
char pedir_char (char i)
{
    printf("Ingrese un caracter\n");
    scanf(" %c", &i);

    return i;
}

//defino la funcion de vocales
bool es_vocal(char letra){
    if (letra == 'A'){
        return true;
    } else if (letra == 'a'){
        return true;
    }else if (letra == 'E'){
        return true;
    }else if (letra == 'e'){
        return true;
    }else if (letra == 'I'){
        return true;
    }else if (letra == 'i'){
        return true;
    }else if (letra == 'O'){
        return true;
    }else if (letra == 'o'){
        return true;
    }else if (letra == 'U'){
        return true;
    }else if (letra == 'u'){
        return true;
    } else{
        return false;
    }
}


int main(){
    char i;
    i = pedir_char (i);
    es_vocal(i);
    if (es_vocal(i) == false){
       printf("El caracter ingresado no es una vocal, intente de nuevo\n");
       assert (es_vocal(i) == true);
    } else{
        printf("El caracter %c es una vocal\n", i);
    }
    return 0;
}

