#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if (x>=0){
        y = x;
    } 
    else{
        y = -x;
    }

}

int main(void) {
    int a=0, res=0;
    a=-10;
    absolute (a,res);
    printf ("%d\n",res);
    
    return EXIT_SUCCESS;
}

/*El valor que regresa esta funcion es el valor 0 que es distinto al esperado 10
eso sucede porque es una funcion tipo void */

