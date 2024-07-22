/* Camilo Gutiérrez, Matías Kühn, Lucas Nieto*/

/*Este archivo contiene todos los gráficos de figuras básicas y con degrades*/

.ifndef figuras_s
.equ figuras_s,0

	.equ SCREEN_WIDTH,   640
	.equ SCREEN_HEIGH,   480
	.equ SCREEN_MIDDLE_WIDTH, 320
	.equ SCREEN_MIDDLE_HEIGH, 240

    .include "constantes.s"

    /*Procedimientos del archivo "figuras.s"*/
    .globl nave_star_wars
    .globl Sol
    .globl arturito
    .global Background

	mov x21, SCREEN_WIDTH // Guardo el largo de la pantalla en x21
	mov x22, SCREEN_HEIGH // Guardo el ancho de la pantalla en x22
	mov x23, SCREEN_MIDDLE_WIDTH // Guardo la mitad del largo de la pantalla en x23
	mov x24, SCREEN_MIDDLE_HEIGH // Guardo la mitad del ancho de la pantalla en x24


/*
	Dibuja una nave de starwars 
	Parametros: 
		X0 = inicio de la nave en x
		x1 = inicio de la nave en y
		x2 = ancho de la nave (alas + radio circulo)
		x13 = tamaño en x (alto de las alas)
*/

nave_star_wars:
		sub sp, sp, #32 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #24] //guardo la dirección de retorno en el stack
		stur x0, [sp, #16] //guardo el valor de x0 en el stack
		stur x1, [sp, #8] //guardo el valor de x1 en el stack
		stur x13, [sp, #0] //guardo el valor de x13 en el stack

		
		movz x4, DARK_GREY_1, lsl 16 // gris oscuro
		movk x4, DARK_GREY_2, lsl 00 
		bl Hexagono 
		
		add x0, x0, x13 // me voy al borde sup del rectangulo
		add x1, x1, 20 // bajo 10 la posicion de y
		movz x3, LIGHT_GREY_1, lsl 16 // gris mas claro
		movk x3, LIGHT_GREY_2, lsl 00 
		mov x2, #15 //radio del circulo
		bl Circulo // llamo a ciruclo (x1 = x1 + 5, x0 = x2, x2 = x2)
		
		add x0, x0, 10 // me separo 5 del borde del rect
		sub x1, x1, 20 // regreso a la posicion inicial de y
		movz x4, LIGHTER_GREY_1, lsl 16 // gris mas claro
		movk x4, LIGHTER_GREY_2, lsl 00 
		bl Hexagono
		
		ldur x13, [sp, #0] //recupero el valor de x13
		ldur x1, [sp, #8] //recupero el valor de x2
		ldur x0, [sp, #16] //recupero el valor de x1
		ldur lr, [sp, #24] //recupero el valor de x0
		add sp, sp, #32 //devuelvo la memoria pedida
		br lr

/*
	Imprime los soles de Tatooine en pantalla
	Parametros:
		x0 = posicion del centro en x del sol pequeño
		x1 = posicion del centro en y del sol pequeño
		x2 = radio del sol pequeño
		x3 = color del contorno sol pequeño
		x4 = color del sol pequeño
		x5 = color del contorno sol grande
		x6 = color del sol grande
*/

Sol:
		sub sp, sp, #64 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #56] //guardo la dirección de retorno en el stack
		stur x0, [sp, #48] //guardo el valor de x0 en el stack
		stur x1, [sp, #40] //guardo el valor de x1 en el stack
		stur x2, [sp, #32] //guardo el valor de x2 en el stack
		stur x3, [sp, #24] //guardo el valor de x3 en el stack
		stur x4, [sp, #16] //guardo el valor de x4 en el stack
		stur x5, [sp, #8] //guardo el valor de x5 en el stack
		stur x6, [sp, #0] //guardo el valor de x6 en el stack

		mov x2, #32
		bl Circulo
		ldur x3, [sp, #16]
		sub x2, x2, #2
		bl Circulo 

		add x0, x0, x2
		add x0, x0, #40
		add x1, x1, #50

		mov x2, #40
		ldur x3, [sp, #8] //recupero el valor de x3
		bl Circulo
		ldur x3, [sp, #0] //recupero el valor de x3
		sub x2, x2, 2
		bl Circulo 

		ldur x6, [sp, #0] //recupero el valor de x6
		ldur x5, [sp, #8] //recupero el valor de x5
		ldur x4, [sp, #16] //recupero el valor de x4
		ldur x3, [sp, #24] //recupero el valor de x3
		ldur x2, [sp, #32] //recupero el valor de x2
		ldur x1, [sp, #40] //recupero el valor de x1
		ldur x0, [sp, #48] //recupero el valor de x0
		ldur lr, [sp, #56] //devuelvo la memoria pedida
		add sp, sp, #64 //recupero la dirección de retorno
		br lr

/*
	Imprime a "arturito"
	No sobreescribe registros que no sean auxiliares
	Parámetros:
		x1 = posición en y
		x8 = distancia
*/

arturito:
		sub sp, sp, #48 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #40] //guardo la dirección de retorno en el stack
		stur x0, [sp, #32] //guardo el valor de x0 en el stack
		stur x1, [sp, #24] //guardo el valor de x1 en el stack
		stur x2, [sp, #16] //guardo el valor de x2 en el stack
		stur x3, [sp, #8] //guardo el valor de x3 en el stack
		stur x8, [sp, #0] //guardo el valor de x8 en el stack

	cabeza:
		//x0 ya viene dado
		//x1 ya viene dado
		mov x16, HEAD_RAD1
		mul x14, x8, x16
		mov x2, x14
		movz x3, HEAD_COLOR0, lsl #0
		movk x3, HEAD_COLOR1, lsl #16
		bl Circulo
		cmp x8, #1
		B.EQ dc1
		bl Detalles_c8
		b tronco
		dc1: bl Detalles_c1

	tronco:
		mov x16, HEAD_RAD1
		mul x14, x8, x16
		sub x0, x0, x14 //me aprovecho de que x0 está en el centro del círculo 
		//no necesito modficar x1
		mov x16, BODY_WIDTH
		mul x14, x8, x16
		mov x2, x14
		mov x16, BODY_HEIGH
		mul x14, x8, x16
		mov x3, x14
		movz x4, WHITE0, lsl #0
		movk x4, WHITE1, lsl #16
		bl Rectangulo
		cmp x8, #1
		B.EQ dt1
		bl Detalles_t8
		b brazos
		dt1: bl Detalles_t1

	brazos:
		mov x16, SHOULDER_SIZE1
		mul x14, x8, x16
        sub x0, x0, x14
		//no necesito modificar x1
		mov x2, x14
		movz x3, EXTREMITIES_COLOR0, lsl #0
		movk x3, EXTREMITIES_COLOR1, lsl #16
		bl Cuadrado
		add x0, x0, x2
		mov x16, BODY_WIDTH
		mul x14, x8, x16
		add x0, x0, x14
		bl Cuadrado 
		
		//no necesito modficar x0
		mov x16, SHOULDER_SIZE1
		mul x14, x8, x16
		add x1, x1, x14
		mov x16, ARM_WIDTH
		mul x14, x8, x16
		mov x2, x14
		mov x16, ARM_HEIGH
		mul x14, x8, x16
		mov x3, x14
		movz x4, EXTREMITIES_COLOR0, lsl #0
		movk x4, EXTREMITIES_COLOR1, lsl #16
		bl Rectangulo
		mov x16, BODY_WIDTH
		mul x14, x8, x16
		sub x0, x0, x14
		mov x16, ARM_WIDTH
		mul x14, x8, x16
		sub x0, x0, x14
		bl Rectangulo

	parte_baja:
		mov x16, ARM_WIDTH
		mul x14, x8, x16
		sub x0, x0, x14
		mov x16, ARM_HEIGH
		mul x14, x8, x16
		add x1, x1, x14
		mov x16, SHOULDER_SIZE1
		mul x14, x8, x16
		mov x2, x14
		movz x3, DIRTY_WHITE0, lsl #0
		movk x3, DIRTY_WHITE1, lsl #16
		bl Cuadrado
		add x0, x0, x14
		mov x16, BODY_WIDTH
		mul x14, x8, x16
		add x0, x0, x14
		bl Cuadrado

		//no necesito modficar x0
		mov x16, SHOULDER_SIZE1
		mul x14, x8, x16
		add x1, x1, x14
		mov x16, FOOT_WIDTH
		mul x14, x8, x16
		mov x2, x14
		mov x16, FOOT_HEIGH
		mul x14, x8, x16
		mov x3, x14
		movz x4, DIRTY_WHITE0, lsl #0
		movk x4, DIRTY_WHITE1, lsl #16
		bl Rectangulo
		mov x16, BODY_WIDTH
		mul x14, x8, x16
		sub x0, x0, x14
		mov x16, FOOT_WIDTH
		mul x14, x8, x16
		sub x0, x0, x14
		bl Rectangulo

		add x0, x0, x14
		mov x16, BASE_WIDTH_DISTANCE
		mul x14, x8, x16
		add x0, x0, x14
		mov x16, BASE_HEIGH_DISTANCE
		mul x14, x8, x16
		add x1, x1, x14
		mov x16, START_OF_WHEEL_WIDTH
		mul x14, x8, x16
		mov x2, x14
		mov x16, START_OF_WHEEL_HEIGH
		mul x14, x8, x16
		mov x3, x14
		//no necesito modficar x4
		bl Rectangulo
		mov x16, PARTS_OF_WHEEL_DISTANCE
		mul x14, x8, x16
		add x0, x0, x14
		mov x16, TOP_OF_WHEEL_HEIGH
		mul x14, x8, x16
		sub x1, x1, x14
		mov x16, TOP_OF_WHEEL_WIDTH
		mul x14, x8, x16
		mov x2, x14
		mov x16, TOP_OF_WHEEL_HEIGH
		mul x14, x8, x16
		mov x3, x14
		bl Rectangulo

		ldur x8, [sp, #0] //recupero el valor de x8
		ldur x3, [sp, #8] //recupero el valor de x3
		ldur x2, [sp, #16] //recupero el valor de x2
		ldur x1, [sp, #24] //recupero el valor de x1
		ldur x0, [sp, #32] //recupero el valor de x0
		ldur lr, [sp, #40] //recupero la dirección de retorno
		add sp, sp, #48 //devuelvo la memoria pedida
		br lr

/*
	Dibuja una placa para el robot
	Parámetros:
		x0 = posición de la esquina superior izquierda en x
		x1 = posición de la esquina superior izquierda en y
		x2 = ancho de la placa (→)
        x3 = largo de la placa (↓)
		x5 = grosor en píxeles del borde
 */

Placa:
		sub sp, sp, #48 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #40] //guardo la dirección de retorno en el stack
		stur x0, [sp, #32] //guardo el valor de x0 en el stack
		stur x1, [sp, #24] //guardo el valor de x1 en el stack
		stur x2, [sp, #16] //guardo el valor de x2 en el stack
		stur x3, [sp, #8] //guardo el valor de x3 en el stack
		stur x5, [sp, #0] //guardo el valor de x5 en el stack

		movz x4, METAL0, lsl #0
		movk x4, METAL1, lsl #16 //guardo en x4 el color metal

		bl Rectangulo //Parte metálica

		ldur x5, [sp, #0]
		add x0, x0, x5
		add x1, x1, x5
		lsl x5, x5, #1 //x5 = x5 * 2
		sub x2, x2, x5
		sub x3, x3, x5
		movz x4, WHITE0, lsl #0
		movk x4, WHITE1, lsl #16

		bl Rectangulo //Parte del centro

		ldur x5, [sp, #0] //recupero el valor de x5
		ldur x3, [sp, #8] //recupero el valor de x3
		ldur x2, [sp, #16] //recupero el valor de x2
		ldur x1, [sp, #24] //recupero el valor de x1
		ldur x0, [sp, #32] //recupero el valor de x0
		ldur lr, [sp, #40] //recupero la dirección de retorno
		add sp, sp, #48 //devuelvo la memoria pedida
		br lr

/*
	Muestra en pantalla los detalles de la cabeza para un arturito a distancia 1
	No sobreescribe registros que no sean auxiliares
*/

Detalles_c1:
		sub sp, sp, #48 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #40] //guardo la dirección de retorno en el stack
		stur x0, [sp, #32] //guardo el valor de x0 en el stack
		stur x1, [sp, #24] //guardo el valor de x1 en el stack
		stur x2, [sp, #16] //guardo el valor de x2 en el stack
		stur x3, [sp, #8] //guardo el valor de x3 en el stack
		stur x8, [sp, #0] //guardo el valor de x8 en el stacks
		
		sub x1, x1, #5
		mov x2, #3
		movz x3, PAINT, lsl #0
		bl Circulo
		mov x2, #1
		mov x3, xzr
		bl Circulo
		sub x0, x0, #8
		add x1, x1, #4
		mov x2, #3
		mov x3, #1
		movz x4, PAINT, lsl #0
		bl Rectangulo 
		add x0, x0, #5
		mov x2, #1
		mov x3, #2
		bl Rectangulo
		add x0, x0, #3
		add x1, x1, #1
		mov x2, #2 
		mov x3, x4
		bl Circulo
		add x0, x0, #6
		sub x1, x1, #1
		mov x2, #1
		mov x3, #2
		bl Rectangulo

		ldur x8, [sp, #0] //recupero el valor de x8
		ldur x3, [sp, #8] //recupero el valor de x3
		ldur x2, [sp, #16] //recupero el valor de x2
		ldur x1, [sp, #24] //recupero el valor de x1
		ldur x0, [sp, #32] //recupero el valor de x0
		ldur lr, [sp, #40] //recupero la dirección de retorno
		add sp, sp, #48 //devuelvo la memoria pedida
		br lr

/*
	Muestra en pantalla los detalles del tronco para un arturito a distancia 1
	No sobreescribe registros que no sean auxiliares
*/

Detalles_t1:
		sub sp, sp, #48 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #40] //guardo la dirección de retorno en el stack
		stur x0, [sp, #32] //guardo el valor de x0 en el stack
		stur x1, [sp, #24] //guardo el valor de x1 en el stack
		stur x2, [sp, #16] //guardo el valor de x2 en el stack
		stur x3, [sp, #8] //guardo el valor de x3 en el stack
		stur x8, [sp, #0] //guardo el valor de x8 en el stack

		add x1, x1, #2
		mov x2, #6
		mov x3, #17
		mov x5, #2
		bl Placa
		add x0, x0, #14
		bl Placa
		sub x0, x0, #6
		mov x2, #4
		mov x3, #2
		movz x4, PAINT, lsl #0
		bl Rectangulo
		add x1, x1, #4
		bl Rectangulo
		add x1, x1, #4
		mov x2, #1
		mov x3, #3
		bl Rectangulo
		add x0, x0, #3
		bl Rectangulo
		sub x0, x0, #2
		mov x2, x3
		movz x3, METAL0, lsl #0
		movk x3, METAL1, lsl #16
		bl Cuadrado
		sub x0, x0, #1
		add x1, x1, #9
		mov x2, #4
		movz x3, PAINT, lsl #0
		bl Cuadrado
		
		ldur x8, [sp, #0] //recupero el valor de x8
		ldur x3, [sp, #8] //recupero el valor de x3
		ldur x2, [sp, #16] //recupero el valor de x2
		ldur x1, [sp, #24] //recupero el valor de x1
		ldur x0, [sp, #32] //recupero el valor de x0
		ldur lr, [sp, #40] //recupero la dirección de retorno
		add sp, sp, #48 //devuelvo la memoria pedida
		br lr

/*
	Muestra en pantalla los detalles de la cabeza para un arturito a distancia 8
	No sobreescribe registros que no sean auxiliares
*/

Detalles_c8:
		sub sp, sp, #48 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #40] //guardo la dirección de retorno en el stack
		stur x0, [sp, #32] //guardo el valor de x0 en el stack
		stur x1, [sp, #24] //guardo el valor de x1 en el stack
		stur x2, [sp, #16] //guardo el valor de x2 en el stack
		stur x3, [sp, #8] //guardo el valor de x3 en el stack
		stur x8, [sp, #0] //guardo el valor de x8 en el stack

		sub x0, x0, #15
		sub x1, x1, #60
		mov x2, #30
		mov x5, #5
		mov x13, #30
		movz x4, PAINT, lsl #0
		bl Trapecio
		add x0, x0, #15
		add x1, x1, #15
		mov x2, #10
		mov x3, xzr
		bl Circulo
		sub x0, x0, #3
		sub x1, x1, #3
		mov x2, #2
		movz x3, WHITE0, lsl #0
		movk x3, WHITE1, lsl #16
		bl Circulo
		sub x0, x0, #48
		sub x1, x1, #14
		mov x2, #30
		mov x13, #14
		mov x5, #2
		movz x4, PAINT, lsl #0
		bl Paralelogramo_der
		add x0, x0, #30
		sub x1, x1, #14
		mov x2, #20
		mov x3, x13
		bl Rectangulo
		add x0, x0, #24
		bl Rectangulo
		add x0, x0, #20
		mov x2, #30
		mov x13, #14
		mov x5, #2
		movz x4, PAINT, lsl #0
		bl Paralelogramo_izq
		sub x0, x0, #101
		add x1, x1, #73
		mov x2, #158
		mov x3, #3
		bl Rectangulo
		add x0, x0, #4
		sub x1, x1, #24
		mov x2, #20
		movz x3, PAINT, lsl #0
		bl Cuadrado
		add x0, x0, #22
		mov x2, #6
		mov x3, #20
		movz x4, PAINT, lsl #0
		bl Rectangulo
		add x0, x0, #8
		mov x2, #17
		bl Rectangulo
		add x0, x0, #4
		add x1, x1, #2
		mov x2, #9
		mov x3, #7
		movz x4, HEAD_COLOR0, lsl #0
		movk x4, HEAD_COLOR1, lsl #16
		bl Rectangulo
		add x1, x1, #9
		bl Rectangulo
		add x0, x0, #1
		add x1, x1, #1
		sub x2, x2, #1
		sub x3, x3, #1
		movz x4, GRAY_BUTTON0, lsl #0
		movk x4, GRAY_BUTTON1, lsl #16
		bl Rectangulo
		sub x1, x1, #9
		bl Rectangulo
		add x0, x0, #18
		sub x1, x1, #3
		mov x2, #8
		mov x3, #20
		movz x4, PAINT, lsl #0
		bl Rectangulo
		add x0, x0, #10
		mov x2, #24
		bl Rectangulo
		add x0, x0, #14
		add x1, x1, #10
		mov x2, #5
		movz x3, RED_BUTTON, lsl #16
		bl Circulo
		add x0, x0, #22
		mov x2, #10
		movz x3, DARK_METAL0, lsl#0
		movk x3, DARK_METAL1, lsl#16
		bl Circulo
		sub x2, x2, #1
		movz x3, EXTREMITIES_COLOR0, lsl#0
		movk x3, EXTREMITIES_COLOR1, lsl#16
		bl Circulo
		sub x2, x2, #1
		movz x3, METAL0, lsl#0
		movk x3, METAL1, lsl#16
		bl Circulo
		add x0, x0, #13
		sub x1, x1, #10
		mov x2, #20
		movz x3, PAINT, lsl #0
		bl Cuadrado
		add x0, x0, #24
		mov x2, #14
		mov x3, #20
		movz x4, PAINT, lsl #0
		bl Rectangulo

		ldur x8, [sp, #0] //recupero el valor de x8
		ldur x3, [sp, #8] //recupero el valor de x3
		ldur x2, [sp, #16] //recupero el valor de x2
		ldur x1, [sp, #24] //recupero el valor de x1
		ldur x0, [sp, #32] //recupero el valor de x0
		ldur lr, [sp, #40] //recupero la dirección de retorno
		add sp, sp, #48 //devuelvo la memoria pedida
		br lr

/*
	Muestra en pantalla los detalles del tronco para un arturito a distancia 8
	No sobreescribe registros que no sean auxiliares
*/

Detalles_t8:
		sub sp, sp, #48 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #40] //guardo la dirección de retorno en el stack
		stur x0, [sp, #32] //guardo el valor de x0 en el stack
		stur x1, [sp, #24] //guardo el valor de x1 en el stack
		stur x2, [sp, #16] //guardo el valor de x2 en el stack
		stur x3, [sp, #8] //guardo el valor de x3 en el stack
		stur x8, [sp, #0] //guardo el valor de x8 en el stack

		add x0, x0, #2
		add x1, x1, #35
		mov x2, #24
		mov x3, #120
		mov x5, #3
		bl Placa
		add x0, x0, #132
		bl Placa
		sub x0, x0, #104
		sub x1, x1, #30
		mov x2, #100
		mov x3, #70
		bl Placa
		add x0, x0, #7
		add x1, x1, #7
		mov x2, #86
		mov x3, #16
		movz x4, PAINT_CONTRAST0, lsl #0
		movk x4, PAINT_CONTRAST1, lsl #16
		bl Rectangulo
		add x0, x0, #1
		add x1, x1, #1
		sub x2, x2, #1
		sub x3, x3, #1
		movz x4, PAINT, lsl #0
		bl Rectangulo
		sub x0, x0, #1
		add x1, x1, #23
		mov x2, #20
		mov x13, #8
		movz x4, PAINT, lsl #0
		mov x5, #5
		bl Trapecio_izq
		add x1, x1, #20
		bl Trapecio_izq
		add x0, x0, #20
		sub x1, x1, #20
		mov x2, #15
		mov x3, x13
		bl Rectangulo
		add x0, x0, #15
		sub x1, x1, #4
		mov x2, #31
		mov x3, #16
		bl Rectangulo
		add x0, x0, #31
		mov x2, #20
		mov x13, x3
		mov x5, #5
		bl Trapecio_der
		add x1, x1, #20
		bl Trapecio_der
		sub x0, x0, #15
		add x1, x1, #4
		mov x2, #15
		mov x3, #8
		bl Rectangulo
		sub x0, x0, #31
		sub x1, x1, #4
		mov x2, #31
		mov x3, #16
		bl Rectangulo
		sub x0, x0, #21
		add x1, x1, #28
		mov x2, #40
		mov x3, #30
		mov x5, #3
		bl Placa
		add x0, x0, #25
		add x1, x1, #40
		mov x2, #15
		mov x3, #35
		bl Placa
		sub x0, x0, #30
		sub x1, x1, #5
		add x2, x2, #10
		add x3, x3, #5
		movz x4, METAL0, lsl #0
		movk x4, METAL1, lsl #16
		bl Rectangulo
		mov x2, #25
		mov x3, #7
		movz x4, PAINT_CONTRAST0, lsl #0
		movk x4, PAINT_CONTRAST1, lsl #16
		mov x10, #4 //Utilizo este registro como contador
		mov x11, #8 //Utilizo este registro como un segundo contador
	print_botón:
		bl Rectangulo
		add x1, x1, #11
		sub x10, x10, #1
		sub x11, x11, #1
		cbnz x10, print_botón
		add x0, x0, #1
		sub x1, x1, #43
		sub x2, x2, #1
		sub x3, x3, #1
		movz x4, PAINT, lsl #0
		add x10, x10, #4
		cbnz x11, print_botón
		
		add x0, x0, #81
		sub x1, x1, #37
		mov x2, #16
		mov x3, #75
		mov x5, #3
		bl Placa
		sub x0, x0, #35
		mov x2, #32
		movz x4, PAINT, lsl #0
		bl Rectangulo
		add x0, x0, #16
		add x1, x1, #20
		mov x2, #13
		movz x3, WHITE0, lsl #0
		movk x3, WHITE1, lsl #16
		bl Circulo
		add x1, x1, #35
		bl Circulo
		mov x10, #3 //Uso este registro como contador
		mov x11, #6 //Uso este registro como un segundo contador
		sub x0, x0, #13
		add x1, x1, #6
		mov x2, #26
		mov x3, #5
		movz x4, PAINT, lsl #0
	ventilacion:
		bl Rectangulo
		sub x1, x1, #8
		sub x10, x10, #1
		sub x11, x11, #1
		cbnz x10, ventilacion
		sub x1, x1, #11
		add x10, x10, #3
		cbnz x11, ventilacion

		ldur x8, [sp, #0] //recupero el valor de x8
		ldur x3, [sp, #8] //recupero el valor de x3
		ldur x2, [sp, #16] //recupero el valor de x2
		ldur x1, [sp, #24] //recupero el valor de x1
		ldur x0, [sp, #32] //recupero el valor de x0
		ldur lr, [sp, #40] //recupero la dirección de retorno
		add sp, sp, #48 //devuelvo la memoria pedida
		br lr

/*
	Dibuja un cielo amaneciendo con un degrade en la pantalla
	Parametros: 
		x0 = posicion inicial en x
		x1 = posicion inicial en y
		x2 = ancho
		x3 = largo
		x4 = color base

*/

Cielo_amanecer: 
 		sub sp, sp, #48 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #40] //guardo la dirección de retorno en el stack
		stur x0, [sp, #32] //guardo el valor de x0 en el stack
		stur x1, [sp, #24] //guardo el valor de x1 en el stack
		stur x2, [sp, #16] //guardo el valor de x2 en el stack
		stur x3, [sp, #8] //guardo el valor de x3 en el stack
		stur x4, [sp, #0] //guardo el valor de x4 en el stack
	
		mov x0, xzr
		mov x1, xzr
		mov x2, x21
		mov x3, x24
		movz x4, YELLOW0, lsl #0
		movk x4, YELLOW1, lsl #16
		mov x5, #3
		mov x6, #2
		BL Rectangulo_degrades_amarillo //Dibuja el "cielo"

		mov x0, #100
		mov x1, #130
		movz x3, CONTORNO_SOL_1, lsl #16
		movk x3, CONTORNO_SOL_2, lsl #00
		movz x4, LITTLE_SUN_1, lsl #16
		movk x4, LITTLE_SUN_2, lsl #00
		mov x5, x3
		movz x6, BIG_SUN_1, lsl #16
		movk x6, BIG_SUN_2, lsl #00
		bl Sol //Dibuja los soles

		mov x0, #560
		mov x1, #40
		mov x13, #20
		BL nave_star_wars //Dibuja la nave

		ldur x4, [sp, #0] //recupero el valor de x4
		ldur x3, [sp, #8] //recupero el valor de x3
		ldur x2, [sp, #16] //recupero el valor de x2
		ldur x1, [sp, #24] //recupero el valor de x1
		ldur x0, [sp, #32] //recupero el valor de x0
		ldur lr, [sp, #40] //recupero la dirección de retorno
		add sp, sp, #48 //devuelvo la memoria pedida
		br lr

/*
	Dibuja una casa promedio de Tatooine
	Parametros:
		x0 = posicion en x del centro de su base
		x1 = posicion en y del centro de su base
		x2 = altura de la casa
		x3 = color   
		x4 = color
*/

Casa: 
		sub sp, sp, #48 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #40] //guardo la dirección de retorno en el stack
		stur x0, [sp, #32] //guardo el valor de x0 en el stack
		stur x1, [sp, #24] //guardo el valor de x1 en el stack
		stur x2, [sp, #16] //guardo el valor de x2 en el stack
		stur x3, [sp, #8] //guardo el valor de x3 en el stack
		stur x4, [sp, #0] //guardo el valor de x4 en el stack
	
		mov x0, #440
		mov x1, x24
		mov x2, #80
		movz x3, CASA_1, lsl #16 
		movk x3, CASA_2, lsl #00
		BL Circulo //Casita

		mov x0, #370
		mov x1, #210
		mov x2, #20
		movz x3, PASILLO_1, lsl 16
		movk x3, PASILLO_2, lsl 00
		BL Circulo

		mov x0, #360
		mov x1, #210
		mov x2, #30
		mov x3, #60
		movz x4, PASILLO_1, lsl 16
		movk x4, PASILLO_2, lsl 00
		BL Rectangulo

		mov x0, #340
		mov x1, #210
		mov x2, #40
		mov x3, #30
		movz x4, CASA_1, lsl #16 
		movk x4, CASA_2, lsl #00
		BL Rectangulo //Dibuja la base de la puerta

		mov x0, #360
		mov x1, #210
		mov x2, #20
		movz x3, CASA_1, lsl #16 
		movk x3, CASA_2, lsl #00
		BL Circulo //Dibuja la parte de arriba de la puerta

		mov x0, #350
		mov x1, #215
		mov x2, #20
		mov x3, #25
		mov x4, xzr
		BL Rectangulo //Dibuja la base del hueco de la puerta

		mov x0, #360
		mov x1, #215
		mov x2, #10
		mov x3, xzr
		BL Circulo //Dibuja la parte de arriba del hueco de la puerta

		ldur x4, [sp, #0] //recupero el valor de x4
		ldur x3, [sp, #8] //recupero el valor de x3
		ldur x2, [sp, #16] //recupero el valor de x2
		ldur x1, [sp, #24] //recupero el valor de x1
		ldur x0, [sp, #32] //recupero el valor de x0
		ldur lr, [sp, #40] //recupero la dirección de retorno
		add sp, sp, #48 //devuelvo la memoria pedida
		br lr

/*
Piso: 
		Dibuja la arena del suelo
		Parametros:
		x0 = posicion inicial del piso en x
		x1 = posicion inicial del piso en y
		x2 = ancho 
		x3 = largo
		x4 = color

*/

Piso: 
		sub sp, sp, #48 //pido memoria en el stack para la dirección de retorno y los parámetros
		stur lr, [sp, #40] //guardo la dirección de retorno en el stack
		stur x0, [sp, #32] //guardo el valor de x0 en el stack
		stur x1, [sp, #24] //guardo el valor de x1 en el stack
		stur x2, [sp, #16] //guardo el valor de x2 en el stack
		stur x3, [sp, #8] //guardo el valor de x3 en el stack
		stur x4, [sp, #0] //guardo el valor de x4 en el stack
	
 		mov x0, xzr
		mov x1, x24
		mov x2, x21
		mov x3, x24
		movz x4, DESIERTO_1, lsl #16 
		movk x4, DESIERTO_2, lsl #00
		BL Rectangulo //Dibuja el "suelo"

		ldur x4, [sp, #0] //recupero el valor de x4
		ldur x3, [sp, #8] //recupero el valor de x3
		ldur x2, [sp, #16] //recupero el valor de x2
		ldur x1, [sp, #24] //recupero el valor de x1
		ldur x0, [sp, #32] //recupero el valor de x0
		ldur lr, [sp, #40] //recupero la dirección de retorno
		add sp, sp, #48 //devuelvo la memoria pedida
		br lr

/*
	Pinta la casa y el piso (en ese orden)
*/

Terreno:
		sub sp, sp, 8
 		stur lr, [sp, #0]
	
		BL Casa
		BL Piso

		ldur lr, [sp, #0]
		add sp, sp, #8
		br lr
	
Background:
		sub sp, sp, #8
 		stur lr, [sp, #0]
	
		BL Cielo_amanecer
		BL Terreno

		ldur lr, [sp, #0]
		add sp, sp, #8
		br lr

.endif
