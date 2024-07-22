	.data
	example1: .dword 0x72
      example2: .dword 0x89
	.text
	LDR X0, example1
      LDR X1, example2
    	

	MOV X0, X1        //X0 = X1

      LDR X0, example1  //Restablece el contenido de X0

      ADD X0, X1, XZR   //X0 = X1 + 0 = X1


end:
infloop: B infloop
