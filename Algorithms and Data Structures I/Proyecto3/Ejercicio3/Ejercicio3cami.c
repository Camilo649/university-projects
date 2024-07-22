#include <stdio.h>

int a (int x){
    printf ("El resultado es %d\n", x = 5);
    return x;
}

int b (int x, int y){
    x = x + y;
    y = y + y;
    printf ("El resultado es x -> %d y -> %d\n",x,y);
    return 0;
}

int c (int y, int x){
    y = y + y;
    x = x + y;
    printf ("El resultado es x -> %d y -> %d\n",x,y);
    return 0;
}

int main(void) {

    printf ("Ejercicio 3a\n");
	
    int x;
    int y;
    int r;

	printf("Ingrese un valor de 'x' para el primer programa\n"); 
	scanf("%d", &x); 
    
    r = a (x);

    printf ("Ejercicio 3b\n");

    printf("Ingrese un valor de 'x' para el segundo programa\n"); 
	scanf("%d", &x); 
    printf("Ingrese un valor de 'y' para el segundo programa\n"); 
	scanf("%d", &y); 
   
    r = b (x, y);

    printf ("Ejercicio 3c\n");

    printf("Ingrese un valor de 'x' para el tercer programa\n"); 
	scanf("%d", &x); 
    printf("Ingrese un valor de 'y' para el tercer programa\n"); 
	scanf("%d", &y);

    r = c (y, x);

    return 0;
}

/*
|programa        |usuario ingresa un σ0 |produce una salida σ   |
|1.a ejecucion 1 |      x -> 123        |        x -> 5         |
|1.a ejecucion 2 |      x -> 64         |        x -> 5         |
|1.a ejecucion 3 |      x -> 4000       |        x -> 5         |
|1.b ejecucion 1 |   x -> 8 y -> 9      |  x -> 17 y -> 18      |
|1.b ejecucion 2 |   x -> 65 y -> 48    |  x -> 113 y -> 96     |
|1.b ejecucion 3 |   x -> 123 y -> 968  |  x -> 1091 y -> 1936  |
|1.c ejecucion 1 |   x -> 7 y -> 2      |  x -> 11 y -> 4       |
|1.c ejecucion 2 |   x -> 21 y -> 10    |  x -> 41 y -> 20      |
|1.c ejecucion 3 |   x -> 174 y -> 852  |  x -> 1878 y -> 1704  |
*/