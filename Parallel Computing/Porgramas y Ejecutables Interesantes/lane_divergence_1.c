#include <stdio.h>

#ifndef N
#define N (1L<<K)
#endif

float a[N];

int main(void)
{
	size_t i = 0L;
	float s = 0.0f;
	for (i=0L; i<N; ++i) {
		if (a[i]<1.4f)
			s = s+a[i];
	}

	return (int)s;
}
