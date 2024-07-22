	.data
	X10_value: .dword 0x1
	X9_value: .dword 0x0000000000101000
	.text
      LDR X10, X10_value
      LDR X9, X9_value
	
	
	SUBS XZR, X9, #0 		//Setea flags
      B.GE else               //Salta a <else> si X9 es mayor o igual a 0
      B done                  //Salta a <done>
else: ORR X10, XZR, #2        //X10 = XZR | #2
done: //{X10 = 0x0000000000000002}
 


end:
infloop: B infloop
