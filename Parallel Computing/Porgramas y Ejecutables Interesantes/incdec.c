#include <stdio.h>
#include <assert.h>
#include <pthread.h>

int x = 0; // variable global, en .data

void *IncDec(void *arg) {
	int d = 1; // variable local, en stack o registros
	while(1) {
		x = x+d;
		x = x-d;
	}
}

int main(void) {
	pthread_t t0id, t1id;
	pthread_create(&t0id, NULL, IncDec, NULL);
	pthread_create(&t1id, NULL, IncDec, NULL);
	/* sonda que comprueba el Invariante */
	while(1) {
		assert(0<=x && x<=2); /* Inv: 0<=x<=2 */
		printf("%1d", x);
	}
}

// usando bashplotlib, instalar con pip install bashplotlib
// gcc incdec.c -lpthread && for i in {0..63}; do ./a.out | wc -c; done | sort -n | hist -b 32
