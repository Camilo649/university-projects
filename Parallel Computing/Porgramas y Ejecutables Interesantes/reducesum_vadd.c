#include <immintrin.h>

#define N (1<<27)

float a[N];
float s = 0.0f;

// Versión manual de la vectorización, reordena sumas

int main(void) {
	__m256 vsum = {0.0f};
	for (unsigned int i=0; i<N; i+=8) {
		__m256 v = _mm256_load_ps(&a[i]);
		vsum = _mm256_add_ps(vsum, v);
	}
	// { vsum[j] = \sum{a[i] : 0≤i<N, i%8 = j}, 0≤j<8 }
	for (unsigned int i=0; i<8; ++i)
		s += vsum[i]; // idiom para acceder a las coords!
	return (int)s;
}


// gcc-10 -O1 -march=haswell reducesum_vadd.c && perf stat -r 4 ./a.out

// Mirar assembler con -O{1,2,3} en {gcc-10, clang-9} para ver que hacer con el for final

// No hay forma de promoverlo de AVX a AVX-512 con gcc o clang con -ftree-vectorize
// ¿Será algo que me imaginé que hacía el compilador?
// Quien lo haga se gana unas Polvoritas™.

// Notar que estamos bajado el resultado de SIMD (paralelo) a SISD (secuencial) con un
// `return (int)(vsum[0]+vsum[1]+vsum[2]+vsum[3])`
// ¡Análogo a lo que haremos en GPU!
