#include <stdio.h>

#include "pivot.h"

int main()
{
    int a[4] = {1, 1, 1, 5};

    is_pivot(a, 4, 1) ? printf("Era pivot.\n") : printf("NO era pivot.\n");

    return 0;
}
