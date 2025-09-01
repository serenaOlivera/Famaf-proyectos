#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*5. (Algoritmo de la division) Crear un archivo llamado division.c que contenga la siguiente
funcion:
struct div_t division(int x, int y){
...
}
donde la estructura div_t se define como
struct div_t {
int cociente;
int resto;
};
Esta funcion recibe dos enteros no negativos (divisor no nulo) y devuelve el cociente junto
con el resto de la division entera. En la funcion main pedir al usuario los dos numeros enteros,
imprimir un mensaje de error si el divisor es cero, o imprimir tanto el cociente como el resto
en otro caso.
*/

struct div_t {
int cociente;
int resto;
};

struct div_t division(int x, int y){

    struct div_t resultado;
    if (y<=0){
        printf("El divisor no puede ser menor o igual a 0\n");
        resultado.cociente=0;
        resultado.resto=0;
        assert (y<=0);
    } else {
        resultado.cociente= x/y;
        resultado.resto= x%y;
    }
 return resultado;
}

int main(){
    int divisor, dividendo;
    printf("Designe un divisor (mayor estricto que cero)\n");
    scanf("%d",&divisor);
    printf("Designe un dividendo (mayor que cero)\n");
    scanf("%d",&dividendo);

    struct div_t resultado= division(dividendo, divisor);
    if (divisor !=0){
        printf("El cociente de la division es: %d \n", resultado.cociente);
        printf("El resto de la division es: %d \n", resultado.resto);
    }
    return 0;
}