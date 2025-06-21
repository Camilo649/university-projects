// https://en.algorithmica.org/hpc/algorithms/prefix/

#include <immintrin.h>

#define N (1L<<K)

int a[N];

typedef __m128i v4i;
typedef __m256i v8i;

int main(void)
{
	//intralane butterfly sum, using AVX, but acc in SSE
	for (size_t i=0L; i<N; i+=8L) {
		v8i x = _mm256_load_si256((v8i*) &a[i]);
		x = _mm256_add_epi32(x, _mm256_slli_si256(x, 4));
		x = _mm256_add_epi32(x, _mm256_slli_si256(x, 8));
		_mm256_store_si256((v8i*) &a[i], x);
	}

	v4i s = _mm_setzero_si128();

	//propagate
	for (size_t i=4L; i<N; i+=4L) {
		v4i d = (v4i) _mm_broadcast_ss((float*) &a[i+3]);
		v4i x = _mm_load_si128((v4i*) &a[i]);
		x = _mm_add_epi32(s, x);
		_mm_store_si128((v4i*) &a[i], x);
		s = _mm_add_epi32(s, d);
	}

	return (int)s[0];
}
