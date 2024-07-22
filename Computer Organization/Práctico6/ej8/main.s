	.data
	ESR_example: .dword 0x0b100010
	.text
	LDR X9, ESR_example
    	

	LSR X10, X9, #26 		//X10 = X9 >> 26
    


end:
infloop: B infloop
