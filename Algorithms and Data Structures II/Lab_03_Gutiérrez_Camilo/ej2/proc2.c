#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int *y) {
    if (x >= 0)
    {
        *y = x;
    }
    else
    {
        *y = -x;
    }
}

int main(void) {
    int a=0, res=0;
    
    a = -10;
    absolute(a, &res);
    printf("%d \n", res);
    printf("%d \n", a);

    return EXIT_SUCCESS;
}

/*
Respondiendo a "El parámetro int *y de absolute() es de tipo in, de tipo out o de tipo in/out":
En términos del lenguaje del teórico/práctico, el parámetro es solamente de tipo 'out' porque lo estoy modificando y luego lo devuelvo con el valor absoluto de a. Se puede comprobar que es independiente del valor de res cambiando el valor de dicha variable o quitándole la signación. 

Respondiendo a ¿Qué tipo de parámetros tiene disponibles C para sus funciones?
                ○ Parámetros in
                ○ Parámetros out
                ○ Parámetros in/out
Para mí los tiene todos. En la función anterior tenemos a x que es de tipo 'in', pues solamente leemos x sin modificarla, e y es tipo 'out' como ya vimos. Además, podemos ver que puede tomar variables 'in/out' como por ejemplo los arreglos que leíamos de los archivos .in en los ejercicios del laboratorio anterior que luego eran modificados, dejándolos ordenados de manera ascendente.
*/