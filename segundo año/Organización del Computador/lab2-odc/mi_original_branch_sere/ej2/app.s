    .equ SCREEN_WIDTH, 640
    .equ SCREEN_HEIGH, 480
    .equ BITS_PER_PIXEL, 32

    .equ GPIO_BASE, 0x3f200000
    .equ GPIO_GPFSEL0, 0x00
    .equ GPIO_GPLEV0, 0x34


.include "dibujos.s"
.global main

//fondo
main:
    bl fondo 

	bl pintar_ruta

	bl pintar_borde_ruta
    
	bl pintar_lineas_rutas



    // Ejemplo de uso de gpios
    mov x9, GPIO_BASE

    //New comment!!!!

    // Atención: se utilizan registros w porque la documentación de broadcom
    // indica que los registros que estamos leyendo y escribiendo son de 32 bits

    // Setea gpios 0 - 9 como lectura
    str wzr, [x9, GPIO_GPFSEL0]

    // Lee el estado de los GPIO 0 - 31
    ldr w10, [x9, GPIO_GPLEV0]

    // And bit a bit mantiene el resultado del bit 2 en w10 (notar 0b... es binario)
    // al inmediato se lo refiere como "máscara" en este caso:
    // - Al hacer AND revela el estado del bit 2
    // - Al hacer OR "setea" el bit 2 en 1
    // - Al hacer AND con el complemento "limpia" el bit 2 (setea el bit 2 en 0)
    and w11, w10, 0b00000010

    // si w11 es 0 entonces el GPIO 1 estaba liberado
    // de lo contrario será distinto de 0, (en este caso particular 2)
    // significando que el GPIO 1 fue presionado

    //---------------------------------------------------------------
    // Infinite Loop
    mov x28, #0
    InfLoop:
        //slow down animation
        movz x18,0x99,lsl 16
        slow:
            sub x18,x18,#1
            cbnz x18,slow
        
        bl despintar_arbol
        bl arboleda
        add x28,x28,#1       //registro que contiene la punta del arbol y tronco
        cmp x28, #490
        b.eq reset
        b InfLoop
        reset: 
            mov x28,#0
            sub x28,x28,#480
            ret

