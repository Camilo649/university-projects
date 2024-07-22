#include <stdbool.h>
#include <assert.h>
#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int length = 0;
    
    while (s[length] != '\0')
    {
        ++length; 
    }

    return length;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    unsigned int i = 0;
    bool equals = true;

    while (i <= fstring_length(s1) && equals)
    {
        if (s1[i] == s2[i])
        {
            ++i;
        }
        else
        {
            equals = false;
        }
    }

    return equals;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int s1_length = fstring_length(s1);
    unsigned int s2_length = fstring_length(s2);
    bool less_or_equal;
        
    while (i <= s1_length && j <= s2_length && s1[i] == s2[j])
    {
        ++i;
        ++j;
    }
    if (i <= s1_length )
    {
        if (s1[i] < s2[j])
        {
            less_or_equal = true;
        }
        else
        {
            less_or_equal = false;
        }
    }
    else if (j <= s2_length)
    {
        less_or_equal = false;
    }
    else
    {
        less_or_equal = true;
    }

    return less_or_equal;
}

void fstring_set(fixstring s1, const fixstring s2) {
    int i=0;
    while (i<FIXSTRING_MAX && s2[i]!='\0') {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

void fstring_swap(fixstring s1,  fixstring s2) {
    fixstring aux;
    fstring_set(aux, s1);
    fstring_set(s1, s2);
    fstring_set(s2, aux);
}