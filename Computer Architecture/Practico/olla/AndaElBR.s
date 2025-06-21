    ADD X16, X30, X30 // X16 = 60
    ADD X17, XZR, XZR // X17 = 0

// En teoria, el BR deberia saltar a la instruccion de abajo
tu_abuela:
    SUB X16, X16, X1
    ADD X17, X17, X1
    STUR X17, [X0, #136] // Guarda el valor de X17 en la posicion 17
    CBZ X16, wait
    CBZ X0, tu_abuela // Salto incondicional a la tercera instruccion

wait:
    CBZ X0, wait
