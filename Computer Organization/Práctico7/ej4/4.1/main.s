	.data
	X0_value: .dword 0x0
	X1_value: .dword 0xA
	.text

      //PRIMER PROGRAMA

      LDR X0, X0_value
      LDR X1, X1_value
	
	
loop: ADD X0, X0, #2         //X0 = X0 + 2
      SUB X1, X1, #1         //X1 = X1 - 1
      CBNZ X1, loop          //Salta a <loop> si X1 es distinto de cero
done://{X0=0x14}

      //SEGUNDO PROGRAMA

      LDR X0, X0_value
      LDR X1, X1_value
	
	
l:    SUBS X1, X1, #0         //Setea flags
      B.LE d                  //Salta a <d> (done) si X1 es menor o igual a cero
      SUB X1, X1, #1          //X1 = X1 - 1
      ADD X0, X0, #2          //X0 = X0 + 2
      B l                     //Salta a <l> (loop)
d:    //{X0=0x14}
 


end:
infloop: B infloop
