	.equ SCREEN_WIDTH,   640
	.equ SCREEN_HEIGH,   480
	.equ BITS_PER_PIXEL, 32

	.equ GPIO_BASE,    0x3f200000
	.equ GPIO_GPFSEL0, 0x00
	.equ GPIO_GPLEV0,  0x34

	.globl main

main:
	// x0 contiene la direccion base del framebuffer
	mov x20, x0 // Guarda la dirección base del framebuffer en x20
	mov x21, SCREEN_WIDTH
	//---------------- CODE HERE ------------------------------------

	//Pixel blanco
	movz x10, 0xFF, lsl 16
	movk x10, 0xFFFF, lsl 00

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


/* 
    Dibuja un círculo en la pantalla.
    Parámetros:
        x0 = posicion del centro en x
        x1 = posicion del centro en y
        x2 = radio del circulo
        x3 = color del circulo
*/
circle:
			mov x0, #100 
			mov x1, #100
			mov x2, #40
			movz x3, 0xFF, lsl 16 //Pixel Rojo

			mov x4, x0 //x4 = x0
			mov x5, x1 //x5 = x1

            sub x9, x4, x2 
            sub x10, x5, x2

            mul x6,x2,x2
            add x7,x2,x2
            add x8,x2,x2
    circle_loop:
            sub x0,x9,x4
            sub x1,x10,x5
            madd x0,x0,x0,xzr
            madd x0,x1,x1,x0
            cmp x0,x6
            B.LE circle_loop2
            sub x7,x7,#1
            add x9,x9,#1
            cbnz x7,circle_loop
    circle_mov_y:
            add x10,x10,#1
            sub x9,x4,x2
            sub x8,x8,#1
            add x7,x2,x2
            cbnz x8, circle_loop
    
    circle_loop2: 
            mov x0,x9
            mov x1,x10
            BL pixel
            stur w3,[x0]
            add x9,x9,#1
            sub x7,x7,#1
            cbz x7, circle_mov_y
            b circle_loop

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
