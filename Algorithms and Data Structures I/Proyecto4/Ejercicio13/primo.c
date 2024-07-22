#include <stdio.h>
#include <stdbool.h>

int pedirPrimo(void)
{
    int n;

    printf("Ingrese su candidato a primo: \n");
    scanf ("%d", &n);
    return n;
}

//función auxiliar sacada del Proyecto 3
bool es_primo (int x)
{
    int i;
    bool res;

    i = 2;
    
    //0 y 1 son positivos pero no son primos
    if ((x == 0)  ||  (x == 1))
    {
        res = false;
    }
    else
    {
        while (i < x && res)
        {
         res = true && (x % i != 0);
         i = i + 1;
        }
    }
    return res;
} 

int nesimo_primo(int N)
{
    int i, n;

    i = 0;

    while ((N+1)-i != 0)
    {
         if (es_primo(i))
        {
            n = i;
            i = i+1;
        }
        else
        {
            i = i+1;
        }
    }
    return n;  
}

int main(void)
{
    printf("primo\n");

    int N;

    N = pedirPrimo();

    if (N<0)
    {
        while (N<0)
        {
            printf("Error! Solo numeros positivos por favor.\n");
            N = pedirPrimo();
        }
    }
    else if (N==nesimo_primo(N))
    {
        printf("%d es el n-esimo primo\n",N);
    }
    else
    {
        printf("%d no es el n-esimo primo\n",N);
    }
    
    return 0;
}