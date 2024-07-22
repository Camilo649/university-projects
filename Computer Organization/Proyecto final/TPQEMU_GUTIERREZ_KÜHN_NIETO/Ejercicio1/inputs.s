/* Camilo Gutiérrez, Matías Kühn, Lucas Nieto*/

/*Este archivo se encarga de modificar la pantalla en base al GPIO*/

.ifndef inputs_s
.equ inputs_s,0

	.global character_close


/*
	Dibuja al arturito en frente de la pantalla
*/

character_close:
	
		BL Background
		mov x8, #8
		sub x1, x22, #160
		BL arturito

Infiniteloop:
	b Infiniteloop
	
.endif
