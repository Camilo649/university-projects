// Inicializacion de la memoria
ADD X9, XZR, X11 // X9 = 11
ADD X10, XZR, XZR // X10 = 0

loop: 
	STUR X0, [X10, #0]
	ADD X0, X0, X1
	ADD X10, X10, X8
	SUB X9, X9, X1
	CBZ X9, breakLoop
	CBZ XZR, loop

// Sumatoria desde 0 hasta 10

breakLoop:
    ADD X0, XZR, XZR // Reseteo 0
    ADD X9, XZR, X11 // X9 = 11
    ADD X10, XZR, XZR // X10 = 0

sumLoop:
    LDUR X11, [X10, #0]
    ADD X0, X0, X11
    ADD X10, X10, X8
    SUB X9, X9, X1
    CBZ X9, breakSumLoop 
    CBZ XZR, sumLoop

breakSumLoop:
    STUR X0, [X9, #0] // Guardo el resultado en la direccion 0

infLoop:  
	CBZ XZR, infLoop
