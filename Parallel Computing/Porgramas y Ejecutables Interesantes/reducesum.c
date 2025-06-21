#define N (1<<27)

float a[N];
float s;

int main(void) {
	for (unsigned int i=0; i<N; ++i) {
		s += a[i];
	}
	return (int)s;
}

// Vectoriza:
// gcc-10 -S -march=haswell -O1 -ftree-vectorize -fopt-info-vec -fopt-info-vec-missed reducesum.c
// Interesante, muy interesante.
// Comparar clang y gcc
// gcc-8 no vectoriza!

// Si le damos libertad de reordenar -ffast-math
// gcc-10 -S -march=haswell -O1 -ffast-math -ftree-vectorize -fopt-info-vec reducesum.c
// En realidad alcanza con "-fassociative-math -fno-signed-zeros -fno-trapping-math".
// Pero tiene mucho overhead, dice "loop peeled for vectorization to enhance alignment" entonces ...

// Alineamos a 256 bits o sea a 32 bytes con `__attribute__((aligned(32)))`
// gcc-10 -S -march=haswell -O1 -ffast-math -ftree-vectorize -fopt-info-vec reducesum.c
// Se pierde de algo?
// gcc-10 -S -march=haswell -O1 -ffast-math -ftree-vectorize -fopt-info-vec-missed reducesum.c
// Dice mucho, pero es nonsense.

// Ver un poco el assembler y compararlo con la versión a mano.
