	.data
	Array: .dword 0x64, 0xc8, 0x12c
	contenido_X0: .dword 0xA
	.text
	LDR X6, =Array
	LDR X0, contenido_X0
    	

	ADD X9, X6, #8			//X9 = &Array[0] + 8 = &Array[1]
    ADD  X10, X6, XZR		//X10 = &Array[0]
    STUR X10, [X9, #0]		//Array[1] = &Array[0]
    LDUR X9, [X9, #0] 		//x9 = Array[1] = &Array[0]
    ADD  X0, X9, X10		//contenido_X0 = &Array[0] + &Array[0] = 2 * &Array[0]


end:
infloop: B infloop
