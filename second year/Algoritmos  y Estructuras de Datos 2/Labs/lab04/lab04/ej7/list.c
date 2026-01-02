/*First including the libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"


/*Now, implementing*/

list empty(){
    list l = malloc(sizeof(struct node_of_T));
    l->elem = 0;
    l->next = NULL;
    return l;
}

list add_l (list_elem e, list l){
    list p = malloc(sizeof(struct node_of_T));
    p->elem = e;
    p->next = l;

    return p;
}

list destroy (list l){
    while(l != NULL){
        list temp = l;
        l = l->next;
        free(temp);
    }
    return l;
} 

bool is_empty(list l){
    return l == NULL;
}

list_elem head (list l){
    assert (!is_empty(l));
    return l->elem;
}

list tail (list l){
    assert(!is_empty(l));
    list p = l->next;

    return p;
}

list addr (list_elem e, list l){
    list p = malloc (sizeof(struct node_of_T));
    p->elem = e;
    p ->next = NULL;
    if (!is_empty(l)){
        list q = l;
        while (q->next != NULL){
            q = q->next;
        }
        q->next = p;
    }else{
        l=p;
    }

    return l;
}

unsigned int length (list l){
    unsigned int counter = 0;
    list p = l;
    while (p->next != NULL){
        p = p->next;
        counter++;
    }
    return counter;
}

list concat (list l, list l0){
    list p = malloc(sizeof(struct node_of_T));
    p = l;
    if (l == NULL && l0 == NULL){
        return NULL;
    }
    if (l==NULL){
        return l0;
    }
    else if (l0 == NULL){
        return l;
    }else{
        while (p->next!=NULL){
            p = p->next;
        }
        p->next = l0;
    }
    return p;
}

list_elem index (list l, unsigned int n){
    assert(length(l)>n);
    list p = l;
    for (unsigned int i = 0; i < n; i++)
    {
        p = p->next;
    }
    return p->elem;
}

list take (list l, unsigned int n){
    assert(length(l)>n);
    list p = NULL;
    list q = NULL;
    p = l;
    unsigned int i = 0;
    if(n == 0) {
        while(l != NULL) {
            p = l;
            l = l->next;
            free(p);
        }
        return NULL;
    }
    while(l != NULL && i < n) {
        p = p->next;                //llego hasta el ultimo nodo antes de que sea n
        i++;
    }

    q = p-> next;
    p->next = NULL;

    while(p != NULL) {
        p = q;
        q = q->next;                //elimino el resto
        free(p);
    }

    return l;
}


list drop(list l, unsigned int n) {
    list p = NULL;
    unsigned int i = 0;

    while(l != NULL && i < n) {
        p = l;
        l = l->next;
        free(p);
        i++;
    }
    return l;
}

list copy_list(list l) {
    list copy = malloc(sizeof(struct node_of_T));
    list p = l;
    while(p != NULL) {
		copy = add_l(p->elem, copy);
		p = p->next;
	}

	return(copy);
}
