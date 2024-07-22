	.data
	contenido_X9: .dword 0x55555555
	contenido_X10: .dword 0x12345678
	.text
	LDR X9, contenido_X9
	LDR X10, contenido_X10
    	

	LSL X11, X10, #4 			//X11 = X10 << 4
	AND X11, X11, #0xFFF 		// X11 = (X10 << 4) & 0xFFF


end:
infloop: B infloop
