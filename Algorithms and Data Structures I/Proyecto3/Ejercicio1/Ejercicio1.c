#include <stdio.h>
#include <stdbool.h>

int main (void)

{
    printf ("Ejercicio 1\n");
    
    int x;
    int y;
    int z;
    
    printf ("Ingrese un valor para x\n");
    scanf ("%d", &x);
    printf ("Ingrese un valor para y\n");
    scanf ("%d", &y);
    printf ("Ingrese un valor para z\n");
    scanf ("%d", &z);
    
    int r;
    r = expresion1 (x, y);
    r = expresion2 (x, y, z);
    r = expresion3 (x, y);
    r = expresion4 (x, y);
    r = expresion5 (x, y, z);

    return 0;
}

int expresion1 (int x, int y) 
{
    printf ("El resultado de la expresion 1 es: %d\n", x + y + 1);
    return x + y + 1;
}

int expresion2 (int x, int y, int z)
{
    printf ("El resultado de la expresion 2 es: %d\n", z * z + y * 45 - 15 * x);
    return z * z + y * 45 - 15 * x;
}

int expresion3 (int x, int y)
{
    if ((y - 2 == (x * 3 + 1) % 5)) printf("El resultado de la expresion 3 es: true\n");
    else printf("El resultado de la expresion 3 es: false\n");
}

int expresion4 (int x, int y)
{
    printf ("El resultado de la expresion 4 es: %d\n", y / 2 * x);
    return y / 2 * x;
}

int expresion5 (int x, int y, int z)
{
    if (y < x * z) printf("El resultado de la expresion 5 es: true\n");
    else printf("El resultado de la expresion 5 es: false\n");
}

/* |Expresion                |(x→7, y→3, z→5)|(x→1, y→10, z→8)|
   |x + y + 1                |11             |12              |
   |z * z + y * 45 - 15 * x  |55             |499             |
   |y - 2 == (x * 3 + 1) % 5 |False          |False           |
   |y / 2 * x                |7              |5               |
   |y < x * z                |True           |False           |
*/

/* En la úiltima expresión el tipo sería un int (0 si es False y 1 si es True), que nosotros hacemos pasar por un string */