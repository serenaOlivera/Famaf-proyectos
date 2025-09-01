#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s)
{
    unsigned int pos = 0;
    bool var = true;

    while (pos < FIXSTRING_MAX && var)
    {
        if (s[pos] == '\0')
        {
            var=false;
        }
        pos++;
    }
    return pos-1;
}

bool fstring_eq(fixstring s1, fixstring s2) 
{
    int pos = 0;
    bool var = true;
    int length_s1 = fstring_length(s1);
    int length_s2 = fstring_length(s2);

    while ((pos < length_s1 || pos < length_s2) && var)
    {
        if (length_s1 != length_s2 || s1[pos] != s2[pos])
        {
            var = false;
        }

        pos++;
        
    }

    return var;    
}

bool fstring_less_eq(fixstring s1, fixstring s2)
{
    unsigned int pos = 0;

    while(pos < FIXSTRING_MAX)
    {
        if (s1[pos] < s2[pos])
        {
            return true;
        } else if (s1[pos] > s2[pos])
        {
            return false;
        }
        pos++;

    }
    return true;        
}
