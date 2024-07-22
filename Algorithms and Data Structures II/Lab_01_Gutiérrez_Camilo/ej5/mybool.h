#ifndef true
#define true 1
#ifndef false
#define false 0

typedef int mybool;

#endif 
#endif 

/*
Respondiendo a la pregunta: ¿Por qué falla la compilación?

A mi entender, es porque, al ya estar definido el tipo int y como mybool es solamente un sinonimo del tipo int, es como que se esta redefiniendo y debido a ello el programa no compila. 
*/

/*
Respondiendo a la pregunta: ¿Cómo se resuelve el problema?

El problema se resolvió aclarando con "#ifndef" que solo defina true y false si es que ya no se definieron previamente, evitando así la redefinición. Y por supuesto cada vez que utilizo "#ifndef" o "#ifdef" debo aclarar el dominio de la definición con "#endif".
*/