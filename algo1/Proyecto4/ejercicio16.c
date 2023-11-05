#include <stdio.h>
#include <limits.h>

/*Las tres funciones toman como argumento una longitud maxima de arreglo y un arreglo de
personas. Devuelven respectivamente el promedio de peso, la persona de mayor edad y la
persona de menor altura que se encuentra en el arreglo.*/

typedef struct _persona {
char *nombre;
int edad;
float altura;
float peso;
} persona_t;


float peso_promedio(unsigned int longitud, persona_t arr[]){
    unsigned int posicion=0;
    int suma=0;
    float promedio=0;

    while (posicion<longitud){
        suma=suma+arr[posicion].peso;
        posicion=posicion+1;
    }
    promedio=suma/longitud;
    return promedio;
}

persona_t persona_de_mayor_edad(unsigned int longitud, persona_t arr[]){
    unsigned int posicion=0;
    persona_t mayoredad;
    mayoredad.edad=0;

    while(posicion<longitud){
        if (mayoredad.edad<arr[posicion].edad){
            mayoredad=arr[posicion];
        }
        posicion=posicion+1;
    }
    return mayoredad;
}

persona_t persona_de_menor_altura(unsigned int longitud, persona_t arr[]){
    unsigned int posicion=0;
    persona_t menoraltura;
    menoraltura.altura=INT_MAX;
    while(posicion<longitud){
        if(arr[posicion].altura<menoraltura.altura){
            menoraltura=arr[posicion];
        }
        posicion=posicion+1;
    }
    return menoraltura;
}

int main(void) {
persona_t p1 = {.nombre="Paola", .edad=21, .altura=1.85, .peso=75};
persona_t p2 = {.nombre="Luis", .edad=54, .altura=1.75, .peso=69};
persona_t p3 = {.nombre="Julio", .edad=40, .altura=1.70, .peso=80};
unsigned int longitud = 3;
persona_t arr[] = {p1, p2, p3};
printf("El peso promedio es %f\n", peso_promedio(longitud, arr));
persona_t p = persona_de_mayor_edad(longitud, arr);
printf("El nombre de la persona con mayor edad es %s\n", p.nombre);
p = persona_de_menor_altura(longitud, arr);
printf("El nombre de la persona con menor altura es %s\n", p.nombre);
return 0;
}