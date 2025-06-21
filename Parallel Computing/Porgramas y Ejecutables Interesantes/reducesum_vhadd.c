#include <immintrin.h>

#define N (1<<27)

float a[N];
float s = 0.0f;

// versión horizontal, mantiene el resultado

int main(void) {
	for (unsigned int i=0; i<N; i+=8) {
		__m256 v = _mm256_load_ps(&a[i]);

		__m256 psum = _mm256_hadd_ps(_mm256_hadd_ps(v,v), _mm256_hadd_ps(v,v));

		s += _mm_cvtss_f32(_mm_add_ps(_mm256_extractf128_ps(psum,0), _mm256_extractf128_ps(psum,1)));
	}
	return (int)s;
}

// gcc-10 -O1 -march=haswell reducesum_vhadd.c && perf stat -r 4 ./a.out
