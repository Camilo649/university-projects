	.data
	A: .dword 0x5B, 0xC1, 0x58, 0x64, 0xC7
	f: .dword 0xB
	g: .dword 0x6
	.text
	LDR X6, =A
	LDR X0, f
	LDR X1, g
    	

	SUB X0, XZR, X1 		//f = -g
	LDUR X9, [X6, #32] 		//X9 = A[4]
	SUB X0, X0, X9 			//f = -g -A[4]


end:
infloop: B infloop
