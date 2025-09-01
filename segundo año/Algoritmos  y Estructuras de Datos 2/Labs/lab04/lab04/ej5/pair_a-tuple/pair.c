#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pair.h"

pair_t pair_new(int x, int y){
    pair_t pair;
    pair.fst = x;
    pair.snd = y;

    assert (pair.fst == x && pair.snd == y);

    return pair;
}

int pair_first(pair_t p){
    int first = 0;  
    assert (&p != NULL);

    first = p.fst;
    assert(first == p.fst);

    return first;
}

int pair_second(pair_t p){
    int second = 0;
    assert (&p != NULL);

    second = p.fst;
    assert(second == p.snd);

    return second;
} 

pair_t pair_swapped(pair_t p){

    assert(&p != NULL);

    pair_t q = pair_new(p.snd, p.fst);

    assert(q.fst == p.snd && q.snd == p.fst);
    return q;
}

pair_t pair_destroy(pair_t p){
    return p;                   //I'm working with intergers ergo i cannot free memory
}
