#include <stdio.h>

int pedirEntero(void)
{
    int x;

    printf("Ingrese un entero\n");
    scanf ("%d", &x);
    return x;
}

struct div_t {
    int cociente;
    int resto;
};

struct div_t division(int x, int y){
struct div_t div;
div.cociente = (x / y);
div.resto = (x % y);  
printf("El cociente es: %d con resto: %d\n",div.cociente,div.resto);
return div;
}

int main (void){

 printf("division)\n");

 int x;
 int y;

 x = pedirEntero();
 y = pedirEntero();
 if (y == 0)
 {
    printf("ERROR FATAL!\n");
 }

 division(x,y);

 return 0;
}