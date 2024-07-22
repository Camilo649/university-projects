/* Camilo Gutiérrez, Matías Kühn, Lucas Nieto*/

/*Este archivo se encarga de leer el GPIO*/

	.equ SCREEN_WIDTH,   640
	.equ SCREEN_HEIGH,   480
	.equ BITS_PER_PIXEL, 32

	.equ GPIO_BASE,    0x3f200000
	.equ GPIO_GPFSEL0, 0x00
	.equ GPIO_GPLEV0,  0x34

	.equ SCREEN_MIDDLE_WIDTH, 320
	.equ SCREEN_MIDDLE_HEIGH, 240

	.include "constantes.s"

	.globl main 

main:
	// x0 contiene la direccion base del framebuffer
	mov x20, x0 // Guarda la dirección base del framebuffer en x20
	mov x21, SCREEN_WIDTH // Guardo el largo de la pantalla en x21
	mov x22, SCREEN_HEIGH // Guardo el ancho de la pantalla en x22
	mov x23, SCREEN_MIDDLE_WIDTH // Guardo la mitad del largo de la pantalla en x23
	mov x24, SCREEN_MIDDLE_HEIGH // Guardo la mitad del ancho de la pantalla en x24	
	//---------------- CODE HERE ------------------------------------
	
//---------------------------------------------------
	BL Background
	
	mov x8, #1
	mov x0, x23 //Inicializo la posición en X en el centro de la pantalla
	sub x1, x22, #265 //Inicializo la posición en Y
	BL arturito //Dibuja al arturito grande

	// Ejemplo de uso de gpios
	mov x9, GPIO_BASE

	// Atención: se utilizan registros w porque la documentación de broadcom
	// indica que los registros que estamos leyendo y escribiendo son de 32 bits

	// Setea gpios 0 - 9 como lectura
	str wzr, [x9, GPIO_GPFSEL0]
 
lectura:

	ldr w10, [x9, GPIO_GPLEV0] // Lee el estado de los GPIO 0 - 31

	and w11, w10, 0b00000000000000000000000000001000
	cbnz w11, character_close // Si el GPIO3 (s) está activado, entonces imprime al arturito de cerca

	b lectura

Infloop:
	b Infloop
