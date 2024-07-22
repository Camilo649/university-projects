/* Camilo Gutiérrez, Matías Kühn, Lucas Nieto*/

/*Este archivo almacena las constantes que se utilizan a lo largo del programa
(medidas, colores, etc.)*/

.ifndef constantes_s
.equ constantes_s,0

//DELAY
.equ STANDARD_DELAY1, 0x0FF//0000 llamar con movz lsl #16
.equ STANDARD_DELAY2, 0x8FF//0000 llamar con movz lsl #16
.equ STANDARD_DELAY3, 0x9FF//0000 llamar con movz lsl #16
.equ STANDARD_DELAY4, 0x1FFF//0000 llamar con movz lsl #16

//arturito
.equ PAINT, 0x48BA
.equ PAINT_CONTRAST0, 0x6DE1
.equ PAINT_CONTRAST1, 0x2A
.equ HEAD_COLOR0, 0xABAB
.equ HEAD_COLOR1, 0xAB
.equ GRAY_BUTTON0, 0x7676
.equ GRAY_BUTTON1, 0x76
.equ RED_BUTTON, 0xDF//0000 llamar con movz lsl #16
.equ WHITE0, 0xFFFF
.equ WHITE1, 0xFF
.equ METAL0, 0x5754
.equ METAL1, 0x4E
.equ DARK_METAL0, 0x3333
.equ DARK_METAL1, 0x33
.equ EXTREMITIES_COLOR0, 0xD3D3
.equ EXTREMITIES_COLOR1, 0xD4
.equ DIRTY_WHITE0, 0xF4F4
.equ DIRTY_WHITE1, 0xF4
.equ HEAD_RAD1, 10
.equ BODY_WIDTH, 20
.equ BODY_HEIGH, 25
.equ SHOULDER_SIZE1, 6
.equ ARM_WIDTH, 3
.equ ARM_HEIGH, 13
.equ FOOT_WIDTH, 8
.equ FOOT_HEIGH, 5
.equ BASE_WIDTH_DISTANCE, 5
.equ BASE_HEIGH_DISTANCE, 3
.equ START_OF_WHEEL_WIDTH, 10
.equ TOP_OF_WHEEL_WIDTH, 8
.equ START_OF_WHEEL_HEIGH, 2
.equ TOP_OF_WHEEL_HEIGH, 3
.equ PARTS_OF_WHEEL_DISTANCE, 1

//nave
.equ DARK_GREY_1, 0x5c
.equ DARK_GREY_2, 0x5a5a
.equ LIGHT_GREY_1, 0x6f
.equ LIGHT_GREY_2, 0x6e6e
.equ LIGHTER_GREY_1, 0x83
.equ LIGHTER_GREY_2, 0x8181

//background
.equ YELLOW0, 0xFF64
.equ YELLOW1, 0xFF 
.equ CONTORNO_SOL_1, 0xe9
.equ CONTORNO_SOL_2, 0xab00
.equ LITTLE_SUN_1, 0xFF
.equ LITTLE_SUN_2, 0xFFA2
.equ BIG_SUN_1, 0xFF
.equ BIG_SUN_2, 0xB262
.equ CASA_1, 0xF2
.equ CASA_2, 0xC467
.equ PASILLO_1, 0xd5
.equ PASILLO_2, 0xae60
.equ DESIERTO_1, 0xDE
.equ DESIERTO_2, 0xA51F
.equ N_SKY_INIT1, 0xCC
.equ N_SKY_INIT2, 0x99FF
.equ BIG_SUN_SUNSET_1, 0xFF
.equ BIG_SUN_SUNSET_2, 0x4D0B
.equ CONTORNO_BIG_SOL_SUNSET_1, 0xFF
.equ CONTORNO_BIG_SOL_SUNSET_2, 0x339A

//Bordes de Pantalla
.equ MIN1, 18
.equ MAX1, 622
.equ MIN8, 128
.equ MAX8, 512

.endif
