/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    bool result = true;
    if (x.rank > y.rank){
        result = false;
    }
    return result;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}


static unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int i = izq + 1;
    unsigned int j = der;
    unsigned int piv = izq;

    while (i <= j)
    {
        if (goes_before (a[i], a[piv]))
        {
            i++;
        } else if (goes_before (a[piv], a[j]))
        {
            j--;
        }else
        {
            swap(a, i, j);
            i++;
            j--;
        }
    }

    swap(a, piv, j);
    piv = j;
    return piv;
    
}

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
    if (der > izq)
    {
        unsigned int piv = partition(a, izq, der);
        if (piv != 0)
        {
            quick_sort_rec(a, izq, piv- 1);
        }
        if (piv != der)
        {
            quick_sort_rec(a, piv + 1, der);
        }
    }

}

void quick_sort_player(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}
