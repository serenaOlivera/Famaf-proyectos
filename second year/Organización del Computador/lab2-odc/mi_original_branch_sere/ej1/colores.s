.ifndef colors_s
    .equ colors_s, 0 

.equ SCREEN_WIDTH,   640
.equ SCREEN_HEIGH,   480
.equ BITS_PER_PIXEL, 32

//colores del fondo :
pasto: .word 0x56C248
ruta: .word 0x344252 
bordes_ruta: .word 0x3d353d
lineas_ruta: .word 0xffffff

//arboles:
hojas: .word 0x208a41
tronco:.word 0x851509

//auto:
llantas: .word 0x000000
auto_rojo:  .word 0xfA0043
ventana_rojo: .word 0xff2b63 
auto_naranja: .word 0xff5722 
auto_blanco: .word 0xf7fcfc
auto_azul: .word 0x0905f7
ventana_azul: .word 0x4d6df3   
 
.endif
