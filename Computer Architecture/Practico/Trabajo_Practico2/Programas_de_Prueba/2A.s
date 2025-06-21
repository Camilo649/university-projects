ADD X9, X30, X30 // X9 = 60
ADD X10, XZR, XZR // X10 = 0

loop: 
	STUR X0, [X10, #0]
	ADD X0, X0, X1
	ADD X10, X10, X8
	SUB X9, X9, X1
	CBZ X9, infLoop
	CBZ XZR, loop

infLoop:  
	CBZ XZR, infLoop
