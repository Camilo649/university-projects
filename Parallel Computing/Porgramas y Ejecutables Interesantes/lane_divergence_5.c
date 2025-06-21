#include <stdio.h>

#ifndef N
#define N (1L<<K)
#endif

float a[N];
float b[N];

int main(void)
{
	size_t i = 0L;
	for (i=0L; i<(N-3); ++i) {
		a[i] = a[i] + b[i+3];
	}

}
