.section .text
.org 0x0
    ADD X29, XZR, XZR // X29 = 0
    ADD X30, XZR, XZR // X30 = 0
    ADD X16, X30, X30 // X16 = 60
    ADD X17, XZR, XZR // X17 = 0
    ADD X18, XZR, XZR // X18 = 0

    ADD X9, XZR, X20 // X9 = 20
    SUB X10, X21, X1 // X10 = 20
    AND X11, X20, X20 // X11 = 20
    ORR X12, X20, X20 // X12 = 20
    SUB X16, X16, X1
    ADD X17, X17, X1
    STUR X9, [X18, #8] // Guarda el valor de X9 en la posicion 1
    STUR X10, [X18, #16] // Guarda el valor de X10 en la posicion 2
    STUR X11, [X18, #24] // Guarda el valor de X11 en la posicion 3
    STUR X12, [X18, #32] // Guarda el valor de X12 en la posicion 4
    STUR X17, [X18, #136] // Guarda el valor de X17 en la posicion 17
    CBZ X16, wait
    BR X20 // Salto incondicional a la sexta instruccion

wait:
    CBZ X18, wait

.org 0xD8                    // Coloca el vector de excepciones en la posición 0xD8

exception_handler:

    MRS X15, S2_0_C2_C0_0 // Guarda el valor de EStatus en X15
    SUB X15, X15, X1
    CBZ X15, External_IRQ
    ADD X29, X1, X0
    STUR X29, [X0, #232] // Guarda el valor de X29 en la posicion 29
    MRS X15, S2_0_C1_C0_0
    ADD X15, X15, X4
    BR X15
External_IRQ:
    ADD X30, X1, X0
    STUR X30, [X0, #240] // Guarda el valor de X30 en la posicion 30
    ERET


