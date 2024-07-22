	.data
	contenido_X9: .dword 0x00000000AAAAAAAA
	contenido_X10: .dword 0x1234567812345678
	esto_es_solamente_porque_ARMv8_no_me_deja_usar_directamente_el_inmediato_0x555: .dword 0x555
	.text
	LDR X9, contenido_X9
	LDR X10, contenido_X10
	LDR X12, esto_es_solamente_porque_ARMv8_no_me_deja_usar_directamente_el_inmediato_0x555
    	

	LSR X11, X9, #3 			//X11 = X9 >> 3
	AND X11, X11, X12 		// X11 = (X9 >> 3) & 0x555


end:
infloop: B infloop
