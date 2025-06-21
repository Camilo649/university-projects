#include <stdio.h>
#include <assert.h>
#include <pthread.h>

int x = 0; // variable global, en .data
pthread_mutex_t lock;

void *IncDec(void *arg) {
	int d = 1; // variable local, en stack o registros
	while(1) {
		pthread_mutex_lock(&lock);
		x = x+d;
		pthread_mutex_unlock(&lock);
		pthread_mutex_lock(&lock);
		x = x-d;
		pthread_mutex_unlock(&lock);
	}
}

int main(void) {
	pthread_t t0id,t1id;
	pthread_create(&t0id, NULL, IncDec, NULL);
	pthread_create(&t1id, NULL, IncDec, NULL);
	pthread_mutex_init(&lock, NULL);
	/* sonda que comprueba el Invariante */
	while(1) {
		assert(0<=x && x<=2); /* Inv: 0<=x<=2 */
		printf("%1d", x);
	}
}

// usando bashplotlib
// gcc incdec_lock.c -lpthread && for i in {0..63}; do ./a.out | wc -c; done | sort -n | hist -b 32
