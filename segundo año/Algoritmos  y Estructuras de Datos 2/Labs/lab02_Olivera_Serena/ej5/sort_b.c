#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"
#include "fixstring.h"


static unsigned int partition_length(fixstring a[], unsigned int izq, unsigned int der) {
    unsigned int i = izq + 1;
    unsigned int j = der;
    unsigned int piv = izq;

    while (i <= j)
    {
        if (goes_before_length (fstring_length(a[i]), fstring_length(a[piv])))
        {
            i++;
        } else if (goes_before_length (fstring_length(a[piv]), fstring_length(a[j])))
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

static void quick_sort_rec_length(fixstring a[], unsigned int izq, unsigned int der) {
    if (der > izq)
    {
        unsigned int piv = partition_length(a, izq, der);
        if (piv != 0)
        {
            quick_sort_rec_length(a, izq, piv- 1);
        }
        if (piv != der)
        {
            quick_sort_rec_length(a, piv + 1, der);
        }
    }
}

void quick_sort_length(fixstring a[], unsigned int length) {
    quick_sort_rec_length(a, 0, (length == 0) ? 0 : length - 1);
}


