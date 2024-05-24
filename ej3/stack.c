#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

stack stack_empty(){
    stack s = malloc(sizeof(_s_stack));
    s->elems = NULL;
    return s;
}

stack stack_push(stack s, stack_elem e){

}

