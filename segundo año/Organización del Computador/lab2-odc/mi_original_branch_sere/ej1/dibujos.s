.ifndef dibujos_s
.equ dibujos_s, 0

.include "helpers.s"



fondo:
    // x0 contiene la direccion base del framebuffer
    mov x20, x0 // Guarda la dirección base del framebuffer en x20
    //---------------- CODE HERE ------------------------------------
    sub sp, sp, #8 // Guardo el puntero de retorno en el stack
    stur lr, [sp]
    movz x10, 0x56, lsl #16
    movk x10, 0xC248, lsl #00

    mov x2, SCREEN_HEIGH // Y Size
loop1:
    mov x1, SCREEN_WIDTH // X Size
loop0:
    stur w10, [x0]     // Colorear el pixel N
    add x0, x0, 4      // Siguiente pixel
    sub x1, x1, 1      // Decrementar contador X
    cbnz x1, loop0     // Si no terminó la fila, salto
    sub x2, x2, 1      // Decrementar contador Y
    cbnz x2, loop1     // Si no es la última fila, salto
    
    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr

pintar_ruta:
    sub sp, sp, #8 // Guardo el puntero de retorno en el stack
    stur lr, [sp]
    movz x10, 0x3d, lsl #16
    movk x10, 0x353d, lsl #00
    mov x0, x20

    mov x1, #155
    mov x2, #0

    mov x6, #515
    mov x7, #480

    bl rectangulo


    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr


pintar_borde_ruta:
    sub sp, sp, #8 // Guardo el puntero de retorno en el stack
    stur lr, [sp]

    movz x10, 0x34, lsl #16
    movk x10, 0x4252, lsl #00
    mov x0, x20

    mov x1, #175
    mov x2, #0

    mov x6, #495
    mov x7, #480

    bl rectangulo

    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr


pintar_lineas_rutas:
    sub sp, sp, #8 // Guardo el puntero de retorno en el stack
    stur lr, [sp]
    movz x10, 0xff, lsl #16
    movk x10, 0xffff, lsl #00
    mov x0, x20

    mov x1, #320        //direcciones de inicio del rectangulo
    mov x2, #0

    mov x6, #340        //direcciones de llegada del rectangulo
    mov x7, #9  

    mov x12, #320

    add x13, x7, #60     //dejo espacio para volver a pintar
    add x14, x2, #20

    bl rectangulo


pintar_lineas_ruta_bucle:

    add x13, x7, #60
    add x14, x2, #20

    mov x1, #320
    mov x2, x14

    mov x6, #340
    mov x7, x13

    mov x12, #480
	
	bl rectangulo

    cmp x1, x12
    b.le pintar_lineas_ruta_bucle

    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr


pino:
    sub sp, sp, #8 // Guardo el puntero de retorno en el stack
    stur lr, [sp]

    movz x10, 0x20, lsl #16         //pintamos las hojas del arbol
    movk x10, 0x8a41, lsl #00

    mov x8, x1          //guardo los valores originales del triangulo en distintos registros
    mov x11, x7

    bl triangulo

    movz x10, 0x85, lsl #16         //pintamos el tronco
    movk x10, 0x1509, lsl #00

    sub x8,x8,#7
    mov x2, x7              //mi rectangulo empieza un pixel mas abajo de donde termino el triangulo
    add x11,x11,#20

    mov x1, x8          
    mov x7, x11

    bl rectangulo

    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr

arboleda:
    sub sp, sp, #8 // Guardo el puntero de retorno en el stack
    stur lr, [sp]

    left_side:
        fst_left:
            mov x1, #37
            mov x2, #12
            mov x7, #42   

            mov x6, #41  
            bl pino
        
        snd_left:
            mov x1, #116
            mov x2, #43
            mov x7, #71   

            mov x6, #119  
            bl pino

        trd_left:
            mov x1, #35
            mov x2, #140
            mov x7, #171   

            mov x6, #41
            bl pino
        
        fourth_left:
            mov x1, #96
            mov x2, #227
            mov x7, #261  

            mov x6, #104  
            bl pino
        
        fifth_left:
            mov x1, #48
            mov x2, #292
            mov x7, #322   

            mov x6, #51
            bl pino
        
        sixth_left:
            mov x1, #57
            mov x2, #393
            mov x7, #421   

            mov x6, #60
            bl pino

        seventh_left:
            mov x1, #126
            mov x2, #441
            mov x7, #470   

            mov x6, #129
            bl pino
    
    right_side:
        fst_right:
            mov x1, #595 
            mov x2, #12
            mov x7, #42   

            mov x6, #599
            bl pino
        
        snd_right:
            mov x1, #595 
            mov x2, #102
            mov x7, #131   

            mov x6, #599
            bl pino
        
        trd_right:
            mov x1, #555 
            mov x2, #163
            mov x7, #191   

            mov x6, #561
            bl pino
        
        fourth_right:
            mov x1, #577 
            mov x2, #233
            mov x7, #260   

            mov x6, #579
            bl pino
        
        fifth_right:
            mov x1, #587 
            mov x2, #353
            mov x7, #383  

            mov x6, #592
            bl pino

        sixth_right:
            mov x1, #604 
            mov x2, #442
            mov x7, #470   

            mov x6, #610
            bl pino


    ldur lr, [sp] // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr

.endif











