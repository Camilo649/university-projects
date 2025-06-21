#include <stdio.h>

#ifndef N
#define N (1L<<K)
#endif

float a[N];
float b[N];

int main(void)
{
	size_t i = 0L;
	for (i=0L; i<N; ++i) {
		if (a[i]<b[i])
			b[i] = b[i]+a[i];
	}
}
