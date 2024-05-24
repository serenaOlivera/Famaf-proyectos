#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct _s_stack{
    stack_elem elem;
    struct _s_stack *next;  
};
 
stack stack_empty(){
    stack s = NULL;
    return s;
}

stack stack_push(stack s, stack_elem e){
    stack p = malloc(sizeof(struct _s_stack));
    p->elem = e;
    p->next = s;
    
    return p;
}

stack stack_pop(stack s){
    if (s == NULL){
        printf ( "The stack is null\n");
        return NULL;
    }
    return s->next;
}

unsigned int stack_size(stack s){
    unsigned int counter = 0;
    stack p = s;
    if (p == NULL){
        return 0;
    }
    while (! stack_is_empty(p)){
        p = p->next;
        counter ++;     
    }
    return counter;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    return s->elem;        
    
}

bool stack_is_empty(stack s){
    if (s == NULL){
        return true;
    }
    return false;
}

stack_elem *stack_to_array(stack s){
    //checks if the stack is empty

    if (s == NULL){
        printf("The stack has no elements\n");
        return NULL;
    }

    //turns the stack into an array
    stack p = s;
    unsigned int size = stack_size(p);
    stack_elem *array = calloc(size, sizeof(struct _s_stack));

    for (unsigned int  i = size; i > 0; i--){
       array[i-1] = p->elem;
       p = p->next;
    }
    return array;    
}

stack stack_destroy(stack s){
    stack p = s;
    while(p != NULL){
        stack t = p;
        p = p->next;
        free(t);
    }
    return NULL;
}