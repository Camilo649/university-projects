SUB X9, X16, X1 // X9 = 15
ADD X10, XZR, X17 // X10 = 17

loop: 
	ADD X10, X10, X17
	SUB X9, X9, X1
	CBZ X9, breakLoop
	CBZ XZR, loop

breakLoop:
    STUR X10, [X0, #0] // guardamos la multiplicaion en la posicion

infLoop:  
	CBZ XZR, infLoop
