	.data
	A: .dword 1, 7, 2, 44, 3, 21, 1, 2, 3
	N: .dword 3
	.text
      //A[3][3] =              |  A->
      //|  1|  7|  2|          |   
      //| 44|  3| 21|          |  |  1|  7|  2| 44|  3| 21|  1|  2|  3|
      //|  1|  2|  3|          |   
      LDR X0, =A
      LDR X9, N
	
	
      MUL X9, X9, X9          //N = N*N
	MOV X1, XZR             //s = 0
      MOV X2, XZR             //i = 0
loop: CMP X2, X9              //Setea flags
      B.GE end                //Salta a <end> si i es mayor o igual a N*N (esto es para cubrir el caso en que N sea negativo. Aunque no sé si cambia de signo despues de hacer MUL)
      LSL X10, X2, #3         //X10 = i*8
      ADD X10, X10, X0        //X10 = i*8 + &A[i]
      LDUR X11, [X10, #0]     //X11 = A[i]
      ADD X1, X1, X11         //s = s + A[i]
      ADD X2, X2, #1          //++i
      B loop                 //Salta a <loop>
 


end:
infloop: B infloop
