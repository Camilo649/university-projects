#include <stdio.h>

#ifndef N
#define N (1L<<K)
#endif

float a[N];
float b[N];

int main(void)
{
	size_t i = 0L;
	float s = 0.0f;
	for (i=0L; i<N; ++i) {
		if (b[i]>a[i])
			break; // GoTos considered harmful, but not me
		a[i] = a[i]+b[i];
	}

	return (int)s;
}
