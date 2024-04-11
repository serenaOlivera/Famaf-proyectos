#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "fixstring.h"

bool goes_before_length (unsigned int x, unsigned int y) {
    if (x <= y)
    {
        return true;
    }
    return false;
}

bool array_is_sorted_length (fixstring array[], unsigned int length) {
    unsigned int i = 1;
    while (i < length && goes_before_length(fstring_length(array[i-1]), fstring_length(array[i]))) {
        i++;
    }
    return (i >= length);
}

