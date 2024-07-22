/* Camilo Gutiérrez, Matías Kühn, Lucas Nieto*/

/*Este archivo se encarga de modificar la pantalla en base al estado de los GPIOS*/

.ifndef inputs_s
.equ inputs_s,0

	.include "constantes.s"
	
	.equ GPIO_BASE,    0x3f200000
	.equ GPIO_GPFSEL0, 0x00
	.equ GPIO_GPLEV0,  0x34

	.global character_far
	.globl character_left
	.global character_close
	.global character_right
	.global Background_mood

//Bucle de retardo
retardo: 
	sub sp, sp, 8
 	stur lr, [sp, #0]

ret:
	sub x27, x27, #1 
	cbnz x27, ret

	ldur lr, [sp, #0]
	add sp, sp, #8
	br lr

/* 
	Mueve el arturito 2 píxeles a la izquierda
*/

character_left:
		sub sp, sp, 8
 		stur lr, [sp, #0]

		cmp x8, #8
		b.eq borde8
		cmp x0, MIN1
		b.le stop
		b proceed
	borde8:
		cmp x0, MIN8
		b.le stop
	proceed:
		bl Background
		sub x0, x0, #2
		bl arturito
		movz x27, STANDARD_DELAY1, lsl #16
		bl retardo

	stop:
		ldur lr, [sp, #0]
		add sp, sp, #8
		br lr

/* 
	Mueve el arturito 2 píxeles a la derecha
*/

character_right:
		sub sp, sp, 8
 		stur lr, [sp, #0]

		cmp x8, #8
		b.eq BORDE8
		cmp x0, MAX1
		b.ge stop
		b PROCCED
	BORDE8:
		cmp x0, MAX8
		b.ge STOP
	PROCCED:
		bl Background
		add x0, x0, #2
		bl arturito
		movz x27, STANDARD_DELAY1, lsl #16
		bl retardo
		
	STOP:
		ldur lr, [sp, #0]
		add sp, sp, #8
		br lr

/*
	Dibuja al arturito en frente de la pantalla
*/

character_close:
		sub sp, sp, 8
 		stur lr, [sp, #0]
	
		cmp x0, MIN8
		b.lt correccion_izq
		cmp x0, MAX8
		b.gt correcion_der
		b its_OK
	correccion_izq:
		mov x0, MIN8 
		b its_OK
	correcion_der:
		mov x0, MAX8
	its_OK:
		BL Background
		mov x8, #8
		sub x1, x22, #160
		BL arturito
		movz x27, STANDARD_DELAY1, lsl #16
		bl retardo

		ldur lr, [sp, #0]
		add sp, sp, #8
		br lr

/*
	Dibuja al arturito al fondo de la pantalla
*/
	
character_far:
		sub sp, sp, 8
 		stur lr, [sp, #0]
	
		BL Background
		mov x8, #1
		sub x1, x22, #265
		BL arturito 
		movz x27, STANDARD_DELAY1, lsl #16
		bl retardo

		ldur lr, [sp, #0]
		add sp, sp, #8
		br lr

/*
	ALterna entre día y noche
*/

Background_mood:
		sub sp, sp, 8
 		stur lr, [sp, #0]
	
		cbnz x25, hacer_de_noche
		add x25, x25, #1
		b se_hizo_de_dia
	hacer_de_noche:
		sub x25, x25, #1
	se_hizo_de_dia:
		BL Background
		BL arturito
		movz x27, STANDARD_DELAY4, lsl #16
		bl retardo

	mov x9, GPIO_BASE
	read_space:
		ldr w10, [x9, GPIO_GPLEV0] // Lee el estado de los GPIO 0 - 31
		and w11, w10, 0b00000000000000000000000000100000
		cbnz w11, read_space //Solo sale del ciclo cuando se halla dejado de pulsar la barra espaciadora.

	done:
		ldur lr, [sp, #0]
		add sp, sp, #8
		br lr
	
.endif
