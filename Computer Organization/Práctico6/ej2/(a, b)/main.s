	.data
	f: .dword 4
	g: .dword 5
	.text

	//a)

	LDR X0, f
	LDR X1, g
    	

	SUB X9, XZR, X1 	//X9 = -g
	SUB X0, X9, X0 		//f = -g -f

	//Otra forma de hacerlo
  //ADD X0, X1, X0 		//f = (g+f)
  //SUB X0, XZR, X0 	//f = -(g+f)

    //b)

	LDR X0, f
	LDR X1, g

	SUB X0, XZR, X0 	//f = -f
	SUB X0, X0, #5 		//f = -f-5
	ADD X0, X1, X0 		//f = g + (-f-5)

	//Otra forma de hacerlo
  //ADD X0, X0, #5 		//f = f+5
  //SUB X0, X1, X0 	    //f = g -(f+5)


end:
infloop: B infloop
