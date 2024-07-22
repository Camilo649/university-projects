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
	
	
	MOV X1, XZR             //s = 0
      MOV X2, XZR             //i = 0
loop1:CMP X2, X9              //Setea flags
      B.GE end                //Salta a <end> si i es mayor o igual a N (esto es para cubrir el caso en que N sea negativo)
      MOV X3, XZR             //j = 0
loop2:CMP X3, X9              //Setea flags
      B.EQ endl2              //Salta a <endl2> si j es igual a N
      MUL X10, X2, X9         //X10 = i*N
      ADD X10, X10, X3        //X10 = i*N+j
      LSL X10, X10, #3        //X10 = (i*N+j)*8
      ADD X10, X10, X0        //X10 = (i*N+j)*8 + A = &A[i][j]
      LDUR X11, [X10, #0]     //X11 = A[i][j]
      ADD X1, X1, X11         //s = s + A[i][j]
      ADD X3, X3, #1          //++j
      B loop2                 //Salta a <loop2>
endl2:ADD X2, X2, #1          //++i
      B loop1                 //Salta a <loop1>
 


end:
infloop: B infloop
