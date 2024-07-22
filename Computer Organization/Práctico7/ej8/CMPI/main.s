	.data
	example: .dword 0x3D
	.text
	LDR X0, example
    	

	CMP X0, #0x2D 	      //Setea flags
	B.LT end                //Salta a <end> sí el contenido de X0 es menor a 0x2D (no debería saltar)
      SUBS XZR, X0, #0x2D     //Setea flags 
      B.LT end                //Salta a <end> sí el contenido de X0 es menor a 0x2D (no debería saltar)

      CMP X0, #0x2D           //Setea flags
      B.GT next               //Salta a <next> sí el contenido de X0 es mayor a 0x2D (debería saltar)

      //En caso de que no salte
      MOV X0, #0xFFFFFFFFFFFFFFFF

next: SUBS XZR, X0, #0x2D     //Setea flags
      B.GT end                //Salta a <end> sí el contenido de X0 es mayor a 0x2D (debería saltar)

      //En caso de que no salte
      MOV X0, #0xFFFFFFFFFFFFFFFF


end:
infloop: B infloop
