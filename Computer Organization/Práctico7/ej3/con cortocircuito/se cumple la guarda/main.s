	.data
	i: .dword 0x6
	j: .dword 0x7
      k: .dword 0x7
      N: .dword 0x6
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
done://{k==0x8}
 


end:
infloop: B infloop
