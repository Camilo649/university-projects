	.data
	A: .dword 0x5B, 0xC1, 0x58, 0x64, 0xC7, 0xC8, 0x2E, 0x40, 0x4C, 0xFE
	B: .dword 0x5B, 0xC1, 0x58, 0x64, 0x94, 0xAA, 0x6D, 0x9C, 0x21
	i: .dword 0xD
	j: .dword 0x4
	.text
	LDR X6, =A
	LDR X7, =B
	LDR X2, i
	LDR X3, j
    	

	SUB X9, X2, X3 			//X9 = i-j
	LSL X10, X9, #3 		//X10 = (i-j)*8
	ADD X11, X6, X10 		//X11 = &A[0] + (i-j)*8 = &A[i-j]
	LDUR X12, [X11, #0] 	//X12 = A[i-j]
	STUR X12, [X7, #64]		//B[8] = A[i-j]


end:
infloop: B infloop
