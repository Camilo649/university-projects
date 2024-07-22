	.data
	i: .dWord 8
	j: .dWord 3
      k: .dWord 9
      N: .dWord 8
	.teXt
      LDR X0, i
      LDR X1, j
      LDR X2, k
      LDR X9, N
	
	
      SUB SP, SP, #32         //Solicito 32 bytes de espacio en el stack
      STR X0, [SP, 24]        //Alojo i en el stack
      STR X1, [SP, 16]        //Alojo j en el stack
      STR X2, [SP, 8]         //Alojo k en el stack
      STR X9, [SP]            //Alojo N en el stack
      LDR X1, [SP, 24]        //X1 = i y restaura i del stack
      LDR X0, [SP]            //X0 = N
      CMP X1, X0              //if(i==N){
      CSET W0, eq             // W0 = 1}
      AND W1, W0, 255         //W1 = W0 & 0Xff
      LDR X2, [SP, 16]        //X2 = j y restaura j del stack
      LDR X0, [SP]            //X0 = N y restaura N del stack
      CMP X2, X0              //if(j==N){
      CSET W0, eq             // W0 = 1}
      AND W0, W0, 255         //W0 = W0 AND 0Xff
      ORR W0, W1, W0          //W0 = W0 | W1
      AND W0, W0, 255         //W0 = W0 & 0Xff
      CMP W0, 0               //if(W0 == 0) {
      B.EQ L2                 // goto L2}
      MOV X0, 2               //X0 = 2
      STR X0, [SP, 8]         //X0 = K 
      B L3                    //Salta a L3
L2:   LDR X0, [SP, 8]         //X0 = k
      ADD X0, X0, 1           //++k
      STR X0, [SP, 8]         //Aloja el nuevo valor de k
L3:   LDR X0, [SP, 8]         //X0 = k y restaura k del stack
      ADD SP, SP, 32          //Devuelve los 32 bytes solicitados


end:
infloop: B infloop
