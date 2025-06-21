#include <omp.h>
#include <stdio.h>

#ifndef N
#define N (1L<<K)
#endif

float a[N] = {[0 ... N-1] = 0.1f};


int main(void)
{
	double ti = omp_get_wtime();
	size_t i = 0L;
	float s = 0.0f;
	for (i=0L; i<N; ++i) {
		s = s+a[i];
	}
	double tf= omp_get_wtime();
	printf("cels/µs: %lf\n", N / (1.0E6*(tf-ti)));
	printf("GiB/s: %lf\n", N*sizeof(a[0]) / ((1<<30)*(tf-ti)));
	printf("%d*0.1f = %f   =?   %f\n", N, N*0.1f, s);


	return (int)s;
}
