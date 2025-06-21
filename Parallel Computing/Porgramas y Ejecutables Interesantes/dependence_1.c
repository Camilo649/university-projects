#include <stdio.h>

#ifndef N
#define N (1L<<K)
#endif

int a[N];

int main(void)
{
	size_t i = 0L;
	for (i=1L; i<N; ++i) {
		a[i] = a[i]+a[i-1];
	}
}
