#include <stdio.h>

#ifndef N
#define N (1L<<K)
#endif

float a[N];
float b[N];
float c[N];

int main(void)
{
	size_t i = 0L;
	for (i=0L; i<N; ++i) {
		if (b[i]<=c[i])
			a[i] = c[i];
		//a[i] = ((b[i] > c[i]) ? a[i] : c[i]);
	}

}
