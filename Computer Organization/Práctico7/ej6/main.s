	.data
	N: .dword 16
	str: .dword 0x754D30616C6F4830, 0x00000000306F646E
	.text
      LDR X0, =str
      LDR X9, N 
	
	
      ADD X1, XZR, XZR        //found = 0
      ADD X2, XZR, XZR        //i = 0
for:  CMP X2, X9              //Setea flags
      B.EQ end                //Salta a <end> si i es igual a N
      ADD X11, X0, X2         //X11 == &str[0] + i
      LDURB W12, [X11, #0]    //X12 = str[i]
      CMP W12, #48            //Verifico si el byte que traje es un 0 (el número 48 se corresponde con el carcater '0' en ASCII)
      B.NE skip               //Salta a <skip> si el contenido de W12 es distinto de 48 (0)
      ADD X1, X1, #1          //Si es era un cero, aumento en 1 a found
skip: ADD X2, X2, #1          //i = i + 1
      B for                   //Salta a <for>
 


end:
infloop: B infloop
