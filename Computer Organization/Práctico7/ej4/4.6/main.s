	.data
	X0_value: .dword 0x0
	X1_value: .dword 0xA
	.text
      LDR X0, X0_value
      LDR X1, X1_value
	
	
      ADD X1, X1, #1          //X1 = X1 + 1
loop: SUBS X1, X1, #1         //X1 = X1 - 1 (osea, x1 en su estado original) y setea flags
      B.LE done               //Salta a <done> si X1 es menor o igual a cero
      ADD X0, X0, #2          //X0 = X0 + 2
      B loop                  //Salta a <loop>
done: //{X0=0x14}


end:
infloop: B infloop
