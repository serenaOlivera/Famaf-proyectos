#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pair.h"

struct s_pair_t {
    elem fst;
    elem snd;
};

pair_t pair_new(elem x, elem y){
    pair_t pair = malloc(sizeof(struct s_pair_t));
    if (pair == NULL){
        printf("The direction saved is NULL\n");
        exit(EXIT_FAILURE);
    }
 
    pair->fst = x;
    pair->snd = y;
    assert(pair->fst == x && pair->snd == y);

    return pair;
}

elem pair_first(pair_t p){
    assert(p != NULL);
    return p->fst;
} 
 
elem pair_second(pair_t p){
    assert(p != NULL);    
    return p->snd;
}

pair_t pair_swapped(pair_t p){
    pair_t swapped = NULL;
    swapped = pair_new (p->snd, p->fst);
    return swapped;
}

pair_t pair_destroy(pair_t p){
    free(p);
    return NULL;
}
