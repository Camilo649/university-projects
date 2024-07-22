#include <stdlib.h>

#include "strfuncs.h"

size_t string_length(const char *str){
    unsigned int current_length=0u;

    while (str[current_length] != '\0')
    {
        ++current_length;
    }
    
    return current_length;
}

char *string_filter(const char *str, char c){
    char *filtered=NULL;
    size_t length=string_length(str);
    unsigned int j=0u;
    
    for (size_t i = 0; i <= length; ++i)
    {
        if (str[i] != c)
        {
            filtered = realloc(filtered, ((j+1) * sizeof(char)));
            filtered[j] = str[i];
            ++j;
        }
    }
    
    return filtered;
}