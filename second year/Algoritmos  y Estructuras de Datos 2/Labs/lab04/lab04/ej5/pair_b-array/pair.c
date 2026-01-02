#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pair.h"

pair_t pair_new(int x, int y){
    pair_t pair;
    pair.values[0]= x;
    pair.values[1]= y;

    assert (&pair != NULL);
    assert(x == pair.values[0] && y == pair.values[1]);
    return pair;
}

int pair_first(pair_t p){
    int first = 0;
    assert(&p != NULL);

    first = p.values[0];
    assert( first == p.values[0]);

    return first;
}


int pair_second(pair_t p){
    int second = 0;
    assert(&p != NULL);

    second = p.values[1];
    assert( second == p.values[1]);
    
    return second;
}

pair_t pair_swapped(pair_t p){
    assert( &p != NULL);

    pair_t q = pair_new(p.values[1], p.values[0]);
    /*tmp = p.values[0];
    p.values[0] = p.values[1];
    p.values[1] = tmp;
    */
    assert  (q.values[0] == p.values[1] && q.values[1] == p.values[0]);
    return p;
}

pair_t pair_destroy(pair_t p){
    return p;                   //there is no destroy in arrays
}
