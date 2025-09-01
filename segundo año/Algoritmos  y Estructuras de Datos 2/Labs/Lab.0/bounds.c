#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

//funcion que pide un arreglo
void pedir_arreglo(int n_max, int a[]){
    int i=0;
    while (i<n_max){
        printf("Ingrese el valor para la posicion %d\n",i);
        scanf("%d", &a[i]);
        i=i+1;
    }                                                 
    
}

struct bound_data {
 bool is_upperbound;
 bool is_lowerbound;
 bool exists;
 unsigned int where;
 };

struct bound_data check_bound(int value, int arr[], unsigned int length){
    struct bound_data var;
    unsigned int pos=0;
    var.is_upperbound=false;
    var.is_lowerbound=false;
    var.exists=false;

    while (pos<=length +1){
        if (arr[pos]<value){
            var.is_lowerbound=true;
        }else if(arr[pos]>=value){
            var.is_upperbound=true;
        }

        if (arr[pos]==value){
            var.exists=true;
            var.where=pos;
        }

        pos=pos+1;
    }
    printf("Upperbounds: %d\n", var.is_upperbound);
    printf("Lowerbounds: %d\n", var.is_lowerbound);
    printf("exists: %d\n", var.exists);
    if (var.exists){
        printf("Where: %d\n", var.where);
    }

    return var;
}


int main(){
    int length;
    printf("Ingrese el valor maximo del arreglo:\n");
    scanf(" %d", &length);

    int a[length];
    pedir_arreglo(length,a);

    int value;
    printf("Ingrese el valor con el que quiere comparar: \n");
    scanf(" %d", &value);

    check_bound(value,a,length);

    return 0;
}