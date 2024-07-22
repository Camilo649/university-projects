	.data
	example_positive: .dword 0x0000000000000006
	example_negative: .dword 0x8000000000000006
	.text
	
	//PRIMER PROGRAMA

	//CASO POSITIVO
	LDR X0, example_positive
    	

	SUBS X0, X0, #0 		//Setea flags
	B.LT else 			//Salta a <else> si x0 es negativo (menor a 0)
	B done			//Salta a <done>
else: SUB X0, XZR, X0 		//X0 = -X0
done: //Finalmente en X0 obtendríamos |X0|

//CASO NEGATIVO
	LDR X0, example_negative
    	

	SUBS X0, X0, #0 		//Setea flags
	B.LT e 			//Salta a <e> (else) si x0 es negativo (menor a 0)
	B d			      //Salta a <d> (done)
e:    SUB X0, XZR, X0 		//X0 = -X0
d:    //Finalmente en X0 obtendríamos |X0|

	//SEGUNDO PROGRAMA

	LDR X9, example_positive

	MOV X0, XZR 		//X0=0
loop: ADD X0, X0, X9 		//X0 = X0 + X9
	SUB X9, X9, #1 		//X9 - 1
	CBNZ X9, loop 		//salta a <loop> si x9 no es 0
end:  //Finalmente en X0 debería quedar la sumatoria desde i=0 hasta el valor original de X0 ((X0 * (X0+1)) / 2)
 


end:
infloop: B infloop
