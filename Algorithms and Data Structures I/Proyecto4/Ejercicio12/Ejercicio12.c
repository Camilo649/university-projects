#include <stdio.h>
#include <stdbool.h>
#define N 6 //x2

typedef char clave_t;
typedef int valor_t;

struct asoc {
clave_t clave;
valor_t valor;
};

void pedirArreglo_asoc(struct asoc a[], int n_max)
{
 int i;

 i = 0;
 while (i<n_max)
 {
    printf("ingrese la clave %d del arreglo: \n",i+1);
    scanf (" %c", &a[i].clave);
    printf("ingrese el valor correspondiete a la clave anterior: \n");
    scanf ("%d", &a[i].valor);
    i = i + 1;
 }
}

/*void imprimeArreglo_asoc(struct asoc a[], int n_max) 
{ 
 int i;
 
 i = 0;
 while (i<n_max)
 {
    printf(" %c -> %d\n", a[i].clave, a[i].valor );
    i = i + 1;
 }
}*/

int pedirClave(void)
{
    char y;

    printf("Ingrese la clave que desea saber si existe: \n");
    scanf (" %c", &y);
    return y;
}

bool asoc_existe(struct asoc a[], int tam, clave_t c)
{
    int i;
    bool e;

    i = 0;
    e = false;

    while (i<tam && !e)
    {
        if (c == a[i].clave)
        {
            e = true;
        }
        else
        {
            i = i+1;
        }
    }
    return e;
}

int main(void)
{
    printf("Ejercicico12\n");

    struct asoc a[N];

    pedirArreglo_asoc(a, N);
    //imprimeArreglo_asoc(a, N); (Prueba para ver este nuevo tipo de arreglo)
    
    clave_t c;

    c = pedirClave();

    if (asoc_existe(a, N, c))
    {
        printf("La clave '%c' se encuentra en el arreglo\n", c);
    }
    else
    {
        printf("Desafortunadamente, '%c' no se encuentra en el arreglo\n:(\n", c);
    }
    
    return 0;
}