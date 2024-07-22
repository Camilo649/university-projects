	.data
	example1: .dword 0xEB
	example2: .dword 0xA3
	.text
	LDR X0, example1
	LDR X1, example2
    	

	CMP X0, X1 		//Setea flags
	B.LT end          //Salta a <end> sí el contenido de X0 es menor al contenido de X1 (no debería saltar)
      SUBS XZR, X0, X1  //Setea flags 
      B.LT end          //Salta a <end> sí el contenido de X0 es menor al contenido de X1 (no debería saltar)

      CMP X0, X1        //Setea flags
      B.GT next         //Salta a <next> sí el contenido de X0 es mayor al contenido de X1 (debería saltar)

      //En caso de que no salte
      MOV X0, #0xFFFFFFFFFFFFFFFF
      MOV X1, #0xFFFFFFFFFFFFFFFF

next: SUBS XZR, X0, X1  //Setea flags
      B.GT end          //Salta a <end> sí el contenido de X0 es mayor al contenido de X1 (debería saltar)

      //En caso de que no salte
      MOV X0, #0xFFFFFFFFFFFFFFFF
      MOV X1, #0xFFFFFFFFFFFFFFFF 


end:
infloop: B infloop
