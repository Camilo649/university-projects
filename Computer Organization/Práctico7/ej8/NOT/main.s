	.data
	example: .dword 5
	.text
	LDR X0, example
    	

	NEG X0, X0        //X0 = -X0
      SUB X0, XZR, X0   //X0 = -X0 (debería volver a su estado original)               



end:
infloop: B infloop
