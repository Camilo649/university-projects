/* Camilo Gutiérrez, Matías Kühn, Lucas Nieto*/

/*Este archivo contiene todas las formas complejas utilizadas en el programa*/

.ifndef formitas_s
.equ formitas_s,0

	/*Procedimientos y funciones del archivo "formitas.s"*/
	.globl Cuadrado
	.globl Rectangulo
	.globl Circulo
	.globl Triangulo
	.globl Triangulo_inv
	.globl Triangulo_der
	.globl Triangulo_izq
	.globl Rombo
	.globl Hexagono
	.globl Trapecio
	.globl Trapecio_izq
	.globl Trapecio_der
	.globl Paralelogramo_der
	.globl Paralelogramo_izq
	.globl Pantalla
	.globl Rectangulo_degrades_amarillo


/* 
    Dibuja un cuadrado en la pantalla.
    Parámetros:
        x0 = posición de la esquina superior izquierda en x
		x1 = posición de la esquina superior izquierda en y
        x2 = lado del cuadrado
        x3 = color del cuadrado
*/

Cuadrado:
		sub sp, sp, #40 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #32] //guardo la dirección de retorno en el stack
		stur x0, [sp, #24] //guardo el valor de x0 en el stack
		stur x1, [sp, #16] //guardo el valor de x1 en el stack
		stur x2, [sp, #8] //guardo el valor de x2 en el stack
		stur x3, [sp, #0] //guardo el valor de x3 en el stack
		stur x3, [sp, #0] //guardo el valor de x3 en el stack

		mov x6, x0 // Copia la coordenada x de la esquina superior derecha del cuadrado
		mov x4, x2 // Indico el largo del cuadrado
	loop_cuadrado1:
		mov x5, x2// Indico el ancho del cuadrado
		mov x0, x6 // Devuelve el valor de x0
		BL Pantalla //calcula donde comenzar a colorear la primera línea
	loop_cuadrado2:
		stur w3, [x0] // Colorea la pantalla
		add x0, x0, #4 // Me muevo al siguiente pixel hacia la derecha
		sub x5, x5, #1 // Decrementar contador del ancho
		cbnz x5, loop_cuadrado2 // Si no terminó la fila, salto
		add x1, x1, #1 // Me posiciono en la siguiente fila
		sub x4, x4, #1 // Decrementar contador del largo
		cbnz x4, loop_cuadrado1 // Si no es la última fila, salto

		ldur x3, [sp, #0] //recupero el valor de x3
		ldur x2, [sp, #8] //recupero el valor de x2
		ldur x1, [sp, #16] //recupero el valor de x1
		ldur x0, [sp, #24] //recupero el valor de x0
		ldur lr, [sp, #32] //recupero la dirección de retorno
		add sp, sp, #40 //devuelvo la memoria pedida
		br lr

/* 
    Dibuja un rectángulo en la pantalla.
    Parámetros:
        x0 = posición de la esquina superior izquierda en x
		x1 = posición de la esquina superior izquierda en y
		x2 = ancho del rectángulo (→)
        x3 = largo del rectángulo (↓)
        x4 = color del rectángulo
*/

Rectangulo:
		sub sp, sp, #48 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #40] //guardo la dirección de retorno en el stack
		stur x0, [sp, #32] //guardo el valor de x0 en el stack
		stur x1, [sp, #24] //guardo el valor de x1 en el stack
		stur x2, [sp, #16] //guardo el valor de x2 en el stack
		stur x3, [sp, #8] //guardo el valor de x3 en el stack
		stur x4, [sp, #0] //guardo el valor de x4 en el stack

		mov x7, x0 // Copia la coordenada x de la esquina superior derecha del rectángulo
		mov x5, x3 // Indico el largo del rectángulo
	loop_rectangulo1:
		mov x6, x2// Indico el ancho del rectángulo
		mov x0, x7 // Devuelve el valor de x0
		BL Pantalla //calcula donde comenzar a colorear la primera línea
	loop_rectangulo2:
		stur w4, [x0] // Colorea la pantalla
		add x0, x0, #4 // Me muevo al siguiente pixel hacia la derecha
		sub x6, x6, #1 // Decrementar contador del ancho
		cbnz x6, loop_rectangulo2 // Si no terminó la fila, salto
		add x1, x1, #1 // Me posiciono en la siguiente fila
		sub x5, x5, #1 // Decrementar contador del largo
		cbnz x5, loop_rectangulo1 // Si no es la última fila, salto

		ldur x4, [sp, #0] //recupero el valor de x4
		ldur x3, [sp, #8] //recupero el valor de x3
		ldur x2, [sp, #16] //recupero el valor de x2
		ldur x1, [sp, #24] //recupero el valor de x1
		ldur x0, [sp, #32] //recupero el valor de x0
		ldur lr, [sp, #40] //recupero la dirección de retorno
		add sp, sp, #48 //devuelvo la memoria pedida
		br lr

/* 
    Dibuja un círculo en la pantalla.
    Parámetros:
        x0 = posicion del centro en x
        x1 = posicion del centro en y
        x2 = radio del circulo
        x3 = color del circulo
*/

Circulo:
        sub sp, sp, #40 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #32] //guardo la dirección de retorno en el stack
		stur x0, [sp, #24] //guardo el valor de x0 en el stack
		stur x1, [sp, #16] //guardo el valor de x1 en el stack
		stur x2, [sp, #8] //guardo el valor de x2 en el stack
		stur x3, [sp, #0] //guardo el valor de x3 en el stack

        mov x4, x0
        mov x5, x1

        sub x9, x4,x2 
        sub x10, x5,x2

        mul x6,x2,x2
        add x7,x2,x2
        add x18,x2,x2
	loop_circulo1:
        sub x0,x9,x4
        sub x1,x10,x5
        madd x0,x0,x0,xzr
        madd x0,x1,x1,x0
        cmp x0,x6
        B.LE loop_circulo2
        sub x7,x7,1
        add x9,x9,1
        cbnz x7,loop_circulo1
    circulo_mov_y:
        add x10,x10,1
        sub x9,x4,x2
        sub x18,x18,1
        add x7,x2,x2
        cbnz x18, loop_circulo1
    circulo_ret:
        ldur x3, [sp, #0] //recupero el valor de x3
		ldur x2, [sp, #8] //recupero el valor de x2
		ldur x1, [sp, #16] //recupero el valor de x1
		ldur x0, [sp, #24] //recupero el valor de x0
		ldur lr, [sp, #32] //recupero la dirección de retorno
		add sp, sp, #40 //devuelvo la memoria pedida
		br lr
    
    loop_circulo2:
        mov x0,x9
        mov x1,x10
        BL Pantalla
        stur w3,[x0]
        add x9,x9,1
        sub x7,x7,1
        cbz x7, circulo_mov_y
        b loop_circulo1

/* Dibuja un triangulo equilatero
	Parametros:
		x0 = pico del triangulo en x
		x1 = pico del triangulo en y
		x2 = ancho escalones
		x13 = altura del triangulo
		x4 = color del triangulo
*/

Triangulo:
		sub sp, sp, #40 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #32] //guardo la dirección de retorno en el stack
		stur x0, [sp, #24] //guardo el valor de x0 en el stack
		stur x1, [sp, #16] //guardo el valor de x1 en el stack
		stur x13, [sp, #8] //guardo el valor de x13 en el stack
		stur x4, [sp, #0] //guardo el valor de x4 en el stack
		
		mov x3, #1
		mov x2, #1
	loop_triangulo:
		bl Rectangulo
		sub x0, x0, 1
		add x1, x1, 1
		add x2, x2, 2
		sub x13, x13, 1
		cbnz x13, loop_triangulo
		
		ldur x4, [sp, #0] //recupero el valor de x4
		ldur x13, [sp, #8] //recupero el valor de x13
		ldur x1, [sp, #16] //recupero el valor de x1
		ldur x0, [sp, #24] //recupero el valor de x0
		ldur lr, [sp, #32] //recupero la dirección de retorno
		add sp, sp, #40 //devuelvo la memoria pedida
		br lr
		
/* 
	Dibuja un triangulo equilatero de cabeza
	Parametros:
		x0 = pico del triangulo en x
		x1 = pico del triangulo en y
		x13 = altura del triangulo
		x4 = color del triangulo
*/

Triangulo_inv:
		sub sp, sp, #40 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #32] //guardo la dirección de retorno en el stack
		stur x0, [sp, #24] //guardo el valor de x0 en el stack
		stur x1, [sp, #16] //guardo el valor de x1 en el stack
		stur x13, [sp, #8] //guardo el valor de x13 en el stack
		stur x4, [sp, #0] //guardo el valor de x4 en el stack
		
		mov x3, #1
		mov x2, #1
	loop_triangulo_inv:
		bl Rectangulo
		sub x0, x0, 1
		sub x1, x1, 1
		add x2, x2, 2
		sub x13, x13, 1
		cbnz x13, loop_triangulo_inv
		
		ldur x4, [sp, #0] //recupero el valor de x4
		ldur x13, [sp, #8] //recupero el valor de x13
		ldur x1, [sp, #16] //recupero el valor de x1
		ldur x0, [sp, #24] //recupero el valor de x0
		ldur lr, [sp, #32] //recupero la dirección de retorno
		add sp, sp, #40 //devuelvo la memoria pedida
		br lr


/*
	Dibuja un triángulo equilatero rotado 90° a la izquierda en la pantalla
	Parametros:
		x0 = pico del triangulo en x
		x1 = pico del triangulo en y
		x13 = altura del triangulo
		x4 = color del triangulo
 */

Triangulo_izq:
		sub sp, sp, #40 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #32] //guardo la dirección de retorno en el stack
		stur x0, [sp, #24] //guardo el valor de x0 en el stack
		stur x1, [sp, #16] //guardo el valor de x1 en el stack
		stur x13, [sp, #8] //guardo el valor de x13 en el stack
		stur x4, [sp, #0] //guardo el valor de x4 en el stack
		
		mov x3, #1
		mov x2, #1
	loop_triangulo_izq:
		bl Rectangulo
		add x0, x0, 1
		sub x1, x1, 1
		add x3, x3, 2
		sub x13, x13, 1
		cbnz x13, loop_triangulo_izq
		
		ldur x4, [sp, #0] //recupero el valor de x4
		ldur x13, [sp, #8] //recupero el valor de x13
		ldur x1, [sp, #16] //recupero el valor de x1
		ldur x0, [sp, #24] //recupero el valor de x0
		ldur lr, [sp, #32] //recupero la dirección de retorno
		add sp, sp, #40 //devuelvo la memoria pedida
		br lr
		
/*
	Dibuja un triángulo equilatero rotado 90° a la derecha en la pantalla
	Parametros:
		x0 = pico del triangulo en x
		x1 = pico del triangulo en y
		x13 = altura del triangulo
		x4 = color del triangulo
 */
		
Triangulo_der:
		sub sp, sp, #40 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #32] //guardo la dirección de retorno en el stack
		stur x0, [sp, #24] //guardo el valor de x0 en el stack
		stur x1, [sp, #16] //guardo el valor de x1 en el stack
		stur x13, [sp, #8] //guardo el valor de x13 en el stack
		stur x4, [sp, #0] //guardo el valor de x4 en el stack
		
		mov x3, #1
		mov x2, #1
	loop_triangulo_der:
		bl Rectangulo
		sub x0, x0, 1
		sub x1, x1, 1
		add x3, x3, 2
		sub x13, x13, 1
		cbnz x13, loop_triangulo_der
		
		ldur x4, [sp, #0] //recupero el valor de x4
		ldur x13, [sp, #8] //recupero el valor de x13
		ldur x1, [sp, #16] //recupero el valor de x1
		ldur x0, [sp, #24] //recupero el valor de x0
		ldur lr, [sp, #32] //recupero la dirección de retorno
		add sp, sp, #40 //devuelvo la memoria pedida
		br lr

/*
	Dibuja un rombo en la pantalla
	Parametros:
		x0 = pico del rombo en x
		x1 = pico del rombo en y
		x13 = mitad de radio
		x4 = color del rombo
*/

Rombo:
		sub sp, sp, #40 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #32] //guardo la dirección de retorno en el stack
		stur x0, [sp, #24] //guardo el valor de x0 en el stack
		stur x1, [sp, #16] //guardo el valor de x1 en el stack
		stur x13, [sp, #8] //guardo el valor de x13 en el stack
		stur x4, [sp, #0] //guardo el valor de x4 en el stack	

		bl Triangulo
		add x1, x1, x13 // x0 = inicio + x13*2
		add x1, x1, x13
		sub x1, x1, 1
		bl Triangulo_inv

		ldur x4, [sp, #0] //recupero el valor de x4
		ldur x13, [sp, #8] //recupero el valor de x13
		ldur x1, [sp, #16] //recupero el valor de x1
		ldur x0, [sp, #24] //recupero el valor de x0
		ldur lr, [sp, #32] //recupero la dirección de retorno
		add sp, sp, #40 //devuelvo la memoria pedida
		br lr
		
/*
	Dibuja un hexágono en la pantalla
	Parametros:
		x0 = posicion en x de la esquina superior del rombo izq que compone la figura
		x1 = posicion en y de la esquina superior del rombo izq que compone la figura
		x13 = mitad de diagonal
		x4 = mitad de daigonal 
*/

Hexagono:
		sub sp, sp, #40 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #32] //guardo la dirección de retorno en el stack
		stur x0, [sp, #24] //guardo el valor de x0 en el stack
		stur x1, [sp, #16] //guardo el valor de x1 en el stack
		stur x13, [sp, #8] //guardo el valor de x13 en el stack
		stur x4, [sp, #0] //guardo el valor de x4 en el stack

		bl Rombo
		mov x2, x13
		add x13, x13, x13
		mov x3, x13  
		bl Rectangulo
		add x0, x0, x2
		mov x13, x2
		bl Rombo

		ldur x4, [sp, #0] //recupero el valor de x4
		ldur x13, [sp, #8] //recupero el valor de x13
		ldur x1, [sp, #16] //recupero el valor de x1
		ldur x0, [sp, #24] //recupero el valor de x0
		ldur lr, [sp, #32] //recupero la dirección de retorno
		add sp, sp, #40 //devuelvo la memoria pedida
		br lr

/* 
    Dibuja un trapecio en la pantalla
    Parámetros:
        x0 = posición de la esquina superior izquierda en x
		x1 = posición de la esquina superior izquierda en y
        x2 = ancho de la parte de arriba del trapecio (→)
		Nota: El ancho de la aparte de abajo es equivalente a x2 + 2 * (x13 / x5)
        x13 = largo del trapecio (↓)
		x4 = color del trapecio
		x5 = ángulo
		Nota: x13 debe ser divisible por x5
*/

Trapecio:
		sub sp, sp, #56 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #48] //guardo la dirección de retorno en el stack
		stur x0, [sp, #40] //guardo el valor de x0 en el stack
		stur x1, [sp, #32] //guardo el valor de x1 en el stack
		stur x2, [sp, #24] //guardo el valor de x2 en el stack
		stur x13, [sp, #16] //guardo el valor de x13 en el stack
		stur x4, [sp, #8] //guardo el valor de x4 en el stack
		stur x5, [sp, #0] //guardo el valor de x5 en el stack

		mov x3, x5
	loop_trapecio:
		bl Rectangulo
		ldur x5, [sp, #0] //refresco el valro de x5 (pues Rectángulo lo modifica)
		sub x0, x0, #1
		add x1, x1, x5
		add x2, x2, #2
		sub x13, x13, x5
		cbnz x13, loop_trapecio

		ldur x5, [sp, #0] //recupero el valor de x5
		ldur x4, [sp, #8] //recupero el valor de x4
		ldur x13, [sp, #16] //recupero el valor de x13
		ldur x2, [sp, #24] //recupero el valor de x2
		ldur x1, [sp, #32] //recupero el valor de x1
		ldur x0, [sp, #40] //recupero el valor de x0
		ldur lr, [sp, #48] //recupero la dirección de retorno
		add sp, sp, #56 //devuelvo la memoria pedida
		br lr

/* 	
    Dibuja un trapecio rotado 90° a la izquierda en la pantalla
    Parámetros:
        x0 = posición de la esquina superior izquierda en x
		x1 = posición de la esquina superior izquierda en y
        x2 = ancho del trapecio (→)
        x13 = largo de la parte izquierda del trapecio (↓)
		Nota: El largo de la parte de la derecha es equivalente a x13 + 2 * (x2 / x5)
		x4 = color del trapecio
		x5 = ángulo
		Nota: x2 debe ser divisible por x5
*/

Trapecio_izq:
		sub sp, sp, #56 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #48] //guardo la dirección de retorno en el stack
		stur x0, [sp, #40] //guardo el valor de x0 en el stack
		stur x1, [sp, #32] //guardo el valor de x1 en el stack
		stur x2, [sp, #24] //guardo el valor de x2 en el stack
		stur x13, [sp, #16] //guardo el valor de x13 en el stack
		stur x4, [sp, #8] //guardo el valor de x4 en el stack
		stur x5, [sp, #0] //guardo el valor de x5 en el stack

		mov x10, x2 //Guardo el valor originial de x2 en x10 y utilizo este registro como contador
		mov x2, x5
		mov x3, x13
	loop_trapecio_izq:
		bl Rectangulo
		ldur x5, [sp, #0] //refresco el valro de x5 (pues Rectángulo lo modifica)
		add x0, x0, x5
		sub x1, x1, #1
		add x3, x3, #2
		sub x10, x10, x5
		cbnz x10, loop_trapecio_izq

		ldur x5, [sp, #0] //recupero el valor de x5
		ldur x4, [sp, #8] //recupero el valor de x4
		ldur x13, [sp, #16] //recupero el valor de x13
		ldur x2, [sp, #24] //recupero el valor de x2
		ldur x1, [sp, #32] //recupero el valor de x1
		ldur x0, [sp, #40] //recupero el valor de x0
		ldur lr, [sp, #48] //recupero la dirección de retorno
		add sp, sp, #56 //devuelvo la memoria pedida
		br lr

/* 
    Dibuja un trapecio rotado 90° a la derecha en la pantalla
    Parámetros:
        x0 = posición de la esquina superior izquierda en x
		x1 = posición de la esquina superior izquierda en y
        x2 = ancho del trapecio (→)
        x13 = largo de la parte izquierda del trapecio (↓)
		Nota: El largo de la parte de la derecha es equivalente a x13 - 2 * (x2 / x5)
		x4 = color del trapecio
		x5 = ángulo
		Nota: x2 debe ser divisible por x5
	PRE: x13 >= (x2 / x5) * 2
*/

Trapecio_der:
		sub sp, sp, #56 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #48] //guardo la dirección de retorno en el stack
		stur x0, [sp, #40] //guardo el valor de x0 en el stack
		stur x1, [sp, #32] //guardo el valor de x1 en el stack
		stur x2, [sp, #24] //guardo el valor de x2 en el stack
		stur x13, [sp, #16] //guardo el valor de x13 en el stack
		stur x4, [sp, #8] //guardo el valor de x4 en el stack
		stur x5, [sp, #0] //guardo el valor de x5 en el stack

		mov x10, x2 //Guardo el valor originial de x2 en x10 y utilizo este registro como contador
		mov x2, x5
		mov x3, x13
	loop_trapecio_der:
		bl Rectangulo
		ldur x5, [sp, #0] //refresco el valro de x5 (pues Rectángulo lo modifica)
		add x0, x0, x5
		add x1, x1, #1
		sub x3, x3, #2
		sub x10, x10, x5
		cbnz x10, loop_trapecio_der

		ldur x5, [sp, #0] //recupero el valor de x5
		ldur x4, [sp, #8] //recupero el valor de x4
		ldur x13, [sp, #16] //recupero el valor de x13
		ldur x2, [sp, #24] //recupero el valor de x2
		ldur x1, [sp, #32] //recupero el valor de x1
		ldur x0, [sp, #40] //recupero el valor de x0
		ldur lr, [sp, #48] //recupero la dirección de retorno
		add sp, sp, #56 //devuelvo la memoria pedida
		br lr

/* 
    Dibuja un paralelogramo rotado a la derecha en la pantalla
    Parámetros:
        x0 = posición de la esquina superior izquierda en x
		x1 = posición de la esquina superior izquierda en y
        x2 = ancho del trapecio (→)
        x13 = largo del del rombo (↓)
		x4 = color del trapecio
		x5 = ángulo
		Nota: x2 debe ser divisible por x5
*/

Paralelogramo_der:
		sub sp, sp, #56 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #48] //guardo la dirección de retorno en el stack
		stur x0, [sp, #40] //guardo el valor de x0 en el stack
		stur x1, [sp, #32] //guardo el valor de x1 en el stack
		stur x2, [sp, #24] //guardo el valor de x2 en el stack
		stur x13, [sp, #16] //guardo el valor de x13 en el stack
		stur x4, [sp, #8] //guardo el valor de x4 en el stack
		stur x5, [sp, #0] //guardo el valor de x5 en el stack

		mov x10, x2 //Guardo el valor originial de x2 en x10 y utilizo este registro como contador
		mov x2, x5
		mov x3, x13
	loop_paralelogramo_der:
		bl Rectangulo
		ldur x5, [sp, #0] //refresco el valro de x5 (pues Rectángulo lo modifica)
		add x0, x0, x5
		sub x1, x1, #1
		sub x10, x10, x5
		cbnz x10, loop_paralelogramo_der

		ldur x5, [sp, #0] //recupero el valor de x5
		ldur x4, [sp, #8] //recupero el valor de x4
		ldur x13, [sp, #16] //recupero el valor de x13
		ldur x2, [sp, #24] //recupero el valor de x2
		ldur x1, [sp, #32] //recupero el valor de x1
		ldur x0, [sp, #40] //recupero el valor de x0
		ldur lr, [sp, #48] //recupero la dirección de retorno
		add sp, sp, #56 //devuelvo la memoria pedida
		br lr

/* 
    Dibuja un paralelogramo rotado a la izquierda en la pantalla
    Parámetros:
        x0 = posición de la esquina superior izquierda en x
		x1 = posición de la esquina superior izquierda en y
        x2 = ancho del trapecio (→)
        x13 = largo del del rombo (↓)
		x4 = color del trapecio
		x5 = ángulo
		Nota: x2 debe ser divisible por x5
*/

Paralelogramo_izq:
		sub sp, sp, #56 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #48] //guardo la dirección de retorno en el stack
		stur x0, [sp, #40] //guardo el valor de x0 en el stack
		stur x1, [sp, #32] //guardo el valor de x1 en el stack
		stur x2, [sp, #24] //guardo el valor de x2 en el stack
		stur x13, [sp, #16] //guardo el valor de x13 en el stack
		stur x4, [sp, #8] //guardo el valor de x4 en el stack
		stur x5, [sp, #0] //guardo el valor de x5 en el stack

		mov x10, x2 //Guardo el valor originial de x2 en x10 y utilizo este registro como contador
		mov x2, x5
		mov x3, x13
	loop_paralelogramo_izq:
		bl Rectangulo
		ldur x5, [sp, #0] //refresco el valro de x5 (pues Rectángulo lo modifica)
		add x0, x0, x5
		add x1, x1, #1
		sub x10, x10, x5
		cbnz x10, loop_paralelogramo_izq

		ldur x5, [sp, #0] //recupero el valor de x5
		ldur x4, [sp, #8] //recupero el valor de x4
		ldur x13, [sp, #16] //recupero el valor de x13
		ldur x2, [sp, #24] //recupero el valor de x2
		ldur x1, [sp, #32] //recupero el valor de x1
		ldur x0, [sp, #40] //recupero el valor de x0
		ldur lr, [sp, #48] //recupero la dirección de retorno
		add sp, sp, #56 //devuelvo la memoria pedida
		br lr

/*
    Calcula la posición del pixel en pantalla
    Parámetros:
        x0 = Posición en x.
        x1 = Posición en y.
    Retorno(ojo que se modifica):
        x0 = Dirección del pixel en las coordenadas deseadas.
*/

Pantalla:
		madd x0, x1, x21, x0 //x0 = (posición y * 640) + posición x
		add x0,x20,x0, lsl #2  //x0 = posición base de la pantalla + [(posición y * 640) + posición x] * 4
		br lr

/*
    Dibuja un rectángulo en pantalla con un degrades descendente para colores amarillentos
    Parámetros:
        x0 = Posición en x
        x1 = Posición en y
		x2 = ancho del rectángulo (→)
        x3 = largo del rectángulo (↓)
        x4 = color base del rectángulo
		x5 = distancia entre degrade
		x6 = velocidad de degrade 
		Aclaración x3 debe ser divisble por x5
*/

Rectangulo_degrades_amarillo:
    sub sp, sp, #64 //pide memoria en el stack para la dirección de retorno y los parámetros
    stur lr, [sp, #56] //guardo la dirección de retorno en le stack
    stur x0, [sp, #48] //guarda el valor de x0 en el stack
    stur x1, [sp, #40] //guarda el valor de x1 en el stack
    stur x2, [sp, #32] //guarda el valor de x2 en el stack
    stur x3, [sp, #24] //guarda el valor de x3 en el stack
    stur x4, [sp, #16] //guarda el valor de x4 en el stack
	stur x5, [sp, #8] //guarda el valor de x5 en el stack
	stur x6, [sp, #0] //guarda el valor de x6 en el stack

		mov x12, x3 //Guardo el valor original de x3 en x12
		mov x3, x5
		mov x18, #0x000100
		mul x18, x18, x6
    loop_linea:
		BL Rectangulo // Llamo a la función rectangulo para dibujar
		ldur x5, [sp, #8] // refresco el valor de x5
		add x1, x1, x5
        sub x4, x4, x18 //Disminuye lo que indique x6 el componente verde
        sub x12, x12, x5 
        cbnz x12, loop_linea //Salta el bucle si no ha llegado a la última fila       

	ldur x6, [sp, #0] //recupero el valor de x6
	ldur x5, [sp, #8] //recupero el valor de x5
    ldur x4, [sp, #16] //recupero el valor de x4
    ldur x3, [sp, #24] //recupero el valor de x3
    ldur x2, [sp, #32] //recupero el Valor x2
    ldur x1, [sp, #40] //recupero el valor de x1
    ldur x0, [sp, #48] //recupero el valor de x0
    ldur lr, [sp, #56] //recupero la dirección de retorno
    add sp, sp, #64 //devuelvo la memoria pedida
    br lr    

.endif
