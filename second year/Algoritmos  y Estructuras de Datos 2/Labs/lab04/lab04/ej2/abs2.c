#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void absolute(int x, int *y) {
    if (x>=0){
        *y = x;
    } 
    else{
        *y = -x;
    }

}

int main(void) {
    int a=0, res=0;  
    a=-10;
    absolute (a,&res);
    printf ("%d\n",res);
    
    assert(res >= 0 && (res == a || res == -a));
    return EXIT_SUCCESS;
}

/* Esta implementacion de la funcion si devielve el valor esperado 10 
el parámetro int *y se comporta como tipo in/out ya que su principal función es devolver un valor modificado, pero también porque su valor inicial se pasa desde el exterior de la función.*/

