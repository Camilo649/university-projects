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
      LSL X9, X9, #3          //N = (N*N)*8
      ADD X9, X9, X0          //N = (N*N)*8 + &A[0] = &A[N]
	MOV X1, XZR             //s = 0
loop: CMP X0, X9              //Setea flags
      B.EQ end                //Salta a <end> si &A[(posición actual)] es mayor o igual a &A[N]
      LDUR X10, [X0, #0]      //X10 = A[(posición actual)]
      ADD X1, X1, X10         //s = s + A[(posición actual)]
      ADD X0, X0, #8          //X0 = &A[(posición siguiente)]
      B loop                  //Salta a <loop>
 


end:
infloop: B infloop
