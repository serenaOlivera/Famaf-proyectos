#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


void stack_dump(stack s){
    if (s == NULL){
        printf ("The stack is empty\n");
    }

    stack p = s;
    unsigned int size = stack_size(p);
    printf("\n TOP \n");
    for (unsigned int i = 0; i < size; i++){
        printf("%d \n", stack_top(p));
        p = stack_pop(p);
    }
    printf("\n BOTTOM \n");

    p = stack_destroy(p);
}

void print_array(stack_elem *array, unsigned int size){
    printf("[");
    for (unsigned int  i = 0; i < size; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("] \n");
    
}

int main (void){
    stack s = stack_empty();

    //Testing stack pop for stacks of 1 element:
    printf("\n Testing if there can be a stack pop for 1 element in a stack\n");
    stack p = s;
    p = stack_push(s, 1);
    s = p;
    stack_dump(s);
    s = stack_pop(s);
    stack_dump(s);
    p = stack_destroy(p);


    // testing if i can still add numbers when my stack is empty
    printf("\n Testing if we can add numbers when the stack is empty\n");
    for (unsigned int  i = 0; i < 4; i++){
        p = stack_push(s,i);
        s = p;
    }
    stack_dump(s);
    stack_destroy(p);

    //checking stack_to_array for an empty stack
    printf ("\n checking stack_to_array for an empty stack \n");
    s = stack_empty(s);
    stack_elem *array = stack_to_array(s);
    print_array(array, stack_size(s));
    
    s = stack_destroy(s);

    return EXIT_SUCCESS;
}