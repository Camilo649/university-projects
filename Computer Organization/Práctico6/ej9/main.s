	.data
	random: .dword 0x23507AF684DA67A4
	.text
	LDR X9, random
    	

	LSR X10, X9, #63 		//X10 = X9 << 63
    


end:
infloop: B infloop
