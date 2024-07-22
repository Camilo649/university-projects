	.data
	contenido_X9: .dword 0x00000000AAAAAAAA
	contenido_X10: .dword 0x1234567812345678
	.text
	LDR X9, contenido_X9
	LDR X10, contenido_X10
    	

	LSL X11, X9, #4 		//X11 = X9 << 4
	ORR X11, X11, X10 		//X11 = (X9 << 4) | X10


end:
infloop: B infloop
