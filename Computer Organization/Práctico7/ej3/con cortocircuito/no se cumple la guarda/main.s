	.data
	i: .dword 5
	j: .dword 4
      k: .dword 7
      N: .dword 8
	.text
      LDR X0, i
      LDR X1, j
      LDR X2, k
      LDR X9, N
	
	
	SUBS XZR, X0, X9        //Setea flags
      B.EQ true               //Salta a <true> si i es igual a N
      SUBS XZR, X1, X9        //Setea flags
      B.EQ true               //Salta a <true> si j es igual a N
      ADD X0, X0, #1          //++i
      ADD X1, X1, #1          //++j
      B done                  //Salta a <done>
true: ADD X2, X2, #1          //++k
done://{i==0x6, j==0x5}
 


end:
infloop: B infloop
