	.equ SCREEN_WIDTH,   640
	.equ SCREEN_HEIGH,   480
	.equ BITS_PER_PIXEL, 32

	.equ GPIO_BASE,    0x3f200000
	.equ GPIO_GPFSEL0, 0x00
	.equ GPIO_GPLEV0,  0x34

	.equ BLUE_SQUARE_SIDE, 40

	.globl main

main:
	// x0 contiene la direccion base del framebuffer
	mov x20, x0 // Guarda la dirección base del framebuffer en x20
	mov x21, SCREEN_WIDTH // Guardo el largo de la pantalla x21
	mov x22, SCREEN_HEIGH // Guardo el ancho de la pantalla x22
	//---------------- CODE HERE ------------------------------------

	movz x10, 0xC7, lsl 16
	movk x10, 0x1585, lsl 00

	mov x2, SCREEN_HEIGH         // Y Size
loop1:
	mov x1, SCREEN_WIDTH         // X Size
loop0:
	stur w10,[x0]  // Colorear el pixel N
	add x0,x0,4    // Siguiente pixel
	sub x1,x1,1    // Decrementar contador X
	cbnz x1,loop0  // Si no terminó la fila, salto
	sub x2,x2,1    // Decrementar contador Y
	cbnz x2,loop1  // Si no es la última fila, salto

//---------------------------------------------------
	mov x0, xzr
	mov x1, xzr
	mov x2, BLUE_SQUARE_SIDE
	movz x3, #0xFF, lsl #0 
	BL Cuadrado //Dibuja un cuadrado azul en la esquina superior izquierda de la pantalla

	sub x0, x21, BLUE_SQUARE_SIDE
	mov x1, xzr
	mov x2, BLUE_SQUARE_SIDE
	movz x3, #0xFF, lsl #0
	BL Cuadrado //Dibuja un cuadrado azul en la esquina superior derecha de la pantalla
	
	mov x0, xzr
	sub x1, x22, BLUE_SQUARE_SIDE
	mov x2, BLUE_SQUARE_SIDE
	movz x3, #0xFF, lsl #0 
	BL Cuadrado //Dibuja un cuadrado azul en la esquina inferior izquierda de la pantalla

	sub x0, x21, BLUE_SQUARE_SIDE
	sub x1, x22, BLUE_SQUARE_SIDE
	mov x2, BLUE_SQUARE_SIDE
	movz x3, #0xFF, lsl #0
	BL Cuadrado //Dibuja un cuadrado azul en la esquina inferior derecha de la pantalla

	B InfLoop // finaliza el programa
//---------------------------------------------------

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

	mov x6, x0 // Copia la coordenada x de la esquina superior derecha del cuadrado
	mov x4, x2 // Indico el largo del cuadrado
loop3:
	mov x5, x2// Indico el ancho del cuadrado
	mov x0, x6 // Devuelve el valor de x0
	BL pixel //calcula donde comenzar a colorear la primera línea
loop2:
	stur w3, [x0] // Colorea la pantalla
	add x0, x0, #4 // Me muevo al siguiente pixel hacia la derecha
	sub x5, x5, #1 // Decrementar contador del ancho
	cbnz x5, loop2 // Si no terminó la fila, salto
	add x1, x1, #1 // Me posiciono en la siguiente fila
	sub x4, x4, #1 // Decrementar contador del largo
	cbnz x4, loop3 // Si no es la última fila, salto

	ldur x3, [sp, #0] //recupero el valor de x3
	ldur x2, [sp, #8] //recupero el valor de x2
	ldur x1, [sp, #16] //recupero el valor de x1
	ldur x0, [sp, #24] //recupero el valor de x0
	ldur lr, [sp, #32] //recupero la dirección de retorno
	add sp, sp, #40 //devuelvo la memoria pedida
	br lr

/*
    Realiza los cálculos necesarios para generar un "puntero" al pixel deseado.
    Parámetros:
        x0 = Posición deseada en x
        x1 = Posición deseada en y
    Retorno:
        x0 = Puntero al pixel en las coordenadas deseadas
*/
pixel:
	madd x0, x1, x21, x0 //fila.|Columnas| + columna
	add x0,x20,x0, lsl #2 //baseArray + (fila.|Columnas| + columna)*4
	br lr

	//---------------------------------------------------------------
	// Infinite Loop

InfLoop:
	b InfLoop
