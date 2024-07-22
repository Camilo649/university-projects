#include <stdio.h>

int e (int x, int y)
{
   if (x >= y) 
   {
    x = 0;
    printf ("El resultado es: x -> %d y -> %d\n",x,y);
   }
   else if (x <= y)
   {
    x = 2;
    printf ("El resultado es: x -> %d y -> %d\n",x,y);
   }
   else
   {
    printf ("El resultado es: x -> %d y -> %d\n",x,y);
   }
   return 0;
}

int f (int x, int y)
{
   if (x >= y) 
   {
    x = 0;
    printf("El resultado es: x -> %d y -> %d\n",x,y);
   }
   else if (x <= y)
   {
    x = 2;
    printf("El resultado es: x -> %d y -> %d\n",x,y);
   }
   else
   {
    printf("El resultado es: x -> %d y -> %d\n",x,y);
   }
   return 0;
}

int p (int x, int y, int z, int m)
{
    if (x < y)
    {
       m = x;
       printf("x -> %d y -> %d z -> %d m -> %d\n",x,y,z,m);
    }
    else
    {
        m = y;
        printf("x -> %d y -> %d z -> %d m -> %d\n",x,y,z,m); 
    }
    if (m < z)
    {
        printf("x -> %d y -> %d z -> %d m -> %d\n",x,y,z,m); 
    }
    else 
    {
        m = z;
        printf("x -> %d y -> %d z -> %d m -> %d\n",x,y,z,m);
    }
    return 0;
}

int main(void) {
	
    printf ("Ejercicio 4a\n");

    int x;
    int y;
    int z;
    int m;
    int r;

	printf("Ingrese un valor de 'x' para el primer programa\n"); 
	scanf("%d", &x);
    printf("Ingrese un valor de 'y' distinto al de 'x' para el primer programa\n"); 
	scanf("%d", &y);  
    
    r = e (x,y);

    printf("Ingrese un valor de 'x' para el segundo programa\n"); 
	scanf("%d", &x); 
    printf("Ingrese un valor de 'y' distinto al de 'x' para el segundo programa\n"); 
	scanf("%d", &y); 
    
    r = f (x,y);

    printf ("Ejercicio 4b\n");

    printf("Ingrese un valor de 'x' para el tercer programa\n"); 
	scanf("%d", &x); 
    printf("Ingrese un valor de 'y' distinto al de 'x' para el tercer programa\n"); 
	scanf("%d", &y); 
    printf("Ingrese un valor de 'z' para el tercer programa\n"); 
	scanf("%d", &z); 
    printf("Ingrese un valor de 'm' distinto al de 'z' para el tercer programa\n"); 
	scanf("%d", &m); 

    r = p (x,y,z,m);

    return 0;
}

/* 
Estado intermedio y estado final del programa p del inciso b:
[|σ1 : (x→5 ,y→4 ,z→8 ,m→4)|]
[|σ2 : (x→5 ,y→4 ,z→8 ,m→4)|]
*/

/*
El programa me devuelve el mínimo entre los enteros x, y, z.
m es el mínimo entre los tres valores.
*/