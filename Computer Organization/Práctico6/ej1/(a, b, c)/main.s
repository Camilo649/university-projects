	.data
	f: .dword 1
	g: .dword 2
	h: .dword 3
	i: .dword 4
	j: .dword 5
	.text

	//a)

	LDR X0, f
	LDR X1, g
	LDR X2, h
	LDR X3, i
	LDR X4, j
    	

	ADD X0, X1, X2 		//f = g+h
	ADD X9, X3, X4 		//X9 = i+j
	ADD X0, X0, X9 		//f = (g+h) + (i+j)

	//Otras formas de hacerlo
	//1:
  //ADD X9, X1, X2 		//X9 = g+h
  //ADD X10, X3, X4 	//X10 = i+j
  //ADD X0, X9, X10 	//f = (g+h) + (i+j)

    //2:
  //ADD X0, X1, X2 		//f = g+h
  //ADD X0, X0, X3 	    //X10 = g+h+i
  //ADD X0, X0, X4 	    //f = g+h+i+j

    //b)

	LDR X0, f
	LDR X1, g
	LDR X2, h

	ADD X0, X2, #5 		//f = h+5
	ADD X0, X1, X0 		//f = g+(h+5)

	//c)

	LDR X0, f
	LDR X1, g
	LDR X2, h

	ADD X0, X1, X2 		//f = g+h
	ADD X0, X0, X0 		//f = (g+h) + (g+h)


end:
infloop: B infloop
