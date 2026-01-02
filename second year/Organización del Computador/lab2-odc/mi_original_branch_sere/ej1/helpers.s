.ifndef helpers_s
.equ helpers_s, 0
.equ SCREEN_WIDTH,   640
.include "colores.s"

/*
*----------------------------------------------------------------------------------------------------
* x10 = registro que tiene el color;
* x1 y x2 tienen las direcciones x e y, entonces para poder operar con ellas y no olvidarlas tenemos
* que hacer antes de llamar a cada funcion:
*               mov x2, el valor y que querramos         // Y Size
*               mov x1, el valor x que querramos       // X Size
* en x3 guardamos la direccion a la cual nos queremos mover, es decir:
*                       Dirección = Dirección de inicio + 4 * [x + (y * 640)]
*               x3= direccion
*               x0 = direccion de inicio
*               recordar que existe madd : Rd = Ra + Rn * Rm, where R is either W or X
*               recordar que multiplicar por 4 es == lsl #2
*----------------------------------------------------------------------------------------------------
*/

pinto_pixel:
    MOV X9,SCREEN_WIDTH
    madd x26, x2, X9, x1    // x26 = x1 + (x2 * 640)
    str w10, [x0, x26, lsl #2] // Guardo w10 en x0 + x26*2^2

    br lr            

/*
--------------------------------------------------------------------------------------------------------------------
*                                              RECTANGULO
* para pintar un rectangulo necesitamos:
* Cordenada (x,y) de inicio del rectangulo
* coordenada X (x1), coordenada Y(x2)
* El ultimo pixel a pintar tiene cordenadas (x,y) tal que x := X6 y y:=X7
* los pasos serian:
*       1. poner en x0 la direccion base del rectangulo
*       2. tener contadores (x6 y x7) que sean la direccion final del rectangulo, x6 el largo y x7 el alto
*        si x1 == x6 => que pare de pintar y salte abajo
*        si x2 == x7 => pare de pintar
--------------------------------------------------------------------------------------------------------------------
*/

rectangulo:
	SUB sp,sp,#8        //Reservamos lugar en memoria para el lr
    stur lr, [sp]       //Guardamos el Lr en memoria
    MOV x3,x1           //Guardar el valor incial del indice x
    pintar_columna_rectangulo:	
        MOV x1,x3       //Resetear el valor del indice x
    pintar_fila_rectangulo:

        bl pinto_pixel
        add x1,x1,#1
        CMP x1,x6
        b.ne pintar_fila_rectangulo
    //bl pinto_fila       // Pintamos una fila
    ADD x2,x2,#1	    // Avanzamos a la siguiente fila
    CMP x2,x7           // Comparamos el valor actual de y con el valor destino de y
    b.eq done           // SI son iguales es porque ya pintamos todo el rectangulo
    B pintar_columna_rectangulo //SIno, volvemos al loop 
done:
	ldur lr, [sp]       // Recupero el puntero de retorno del stack
    add sp, sp, #8 
    br lr               // nos vamos

/*----------------------------------------------------------------------------------------------
*                                        TRIANGULO
* la idea es esta:
*   dibujar un rectangulo con:
*        registro finales x = x1 y=x2;
*           x1 representa la coordenada x en el primer pixel de la punta
*           x2 representa la altura en la que estoy 'y'
*       registro, x7=y
*           x7 representa la altura a donde quiero llegar (altura de base)
*se empezara a pintar el rectangulo desde la punta, y antes de que se pinte la fila de abajo,
* se le suma a el registro x1 el nro 2 y al registro x6 se le resta el numero 2
* el bucle va a parar cuando la altura x7 == x2
*------------------------------------------------------------------------------------------------
*/


triangulo:
    SUB sp,sp,#8        //Reservamos lugar en memoria para el lr
    stur lr, [sp]       //Guardamos el Lr en memoria
    mov x3, x1
    mov x5, x1


    isoceles:           //pinto el resto hasta llegar x2==x7
        cmp x2,x7   
        b.eq done_tr
        sub x5,x5,#1
        mov x1,x5           //pongo el valor anterior de x1
        add x2,x2,#1        //bajo a la fila siguiente
        sub x1,x1,#1        //empiezo un pixel antes
        add x3,x3,#1      //termino un pixel despues
        pinto_tr:
            bl pinto_pixel      //pinto el pixel x1
            add x1,x1,#1
            cmp x1, x3          //si x1 == x3, paro de pintar en mi fila, sino, sigo
            b.ne pinto_tr  
            b isoceles
        

    done_tr:
        ldur lr, [sp]       // Recupero el puntero de retorno del stack
        add sp, sp, #8 
        br lr               // nos vamos

/*
------------------------------------------------------------------------------------------
                                *FUNCION PINTAR LINEA*
*Para pintar fila empezamos desde la posicion x0 y vamos a pintar x7 pixeles en adelante(SOlo modificamos la pos en x)
*Entonces Sabemos que x0 := Posicion inicial de la linea
*                                          x1 := indice inicial de la linea
*                                          x6 := Indice final de la linea
------------------------------------------------------------------------------------------
 */

/*pinto_fila:

    SUB sp,sp,#8        //Reservamos lugar en memoria para el lr
    stur lr, [sp] 

    pintando_fila:
        bl pinto_pixel

        add x1, x1,#1                   //x1++
        cmp x1, x6                      //if(x1!=x6)
        b.ne pintando_fila   
    
    ldur lr, [sp]       // Recupero el puntero de retorno del stack
    add sp, sp, #8           //branch to pinto_fila(Vuelve al loop)
    br lr                           //Ya pinto la fila
*/
/*
----------------------------------------------------------------------------------------------------------------------
                                                        *FUNCION PINTAR COLUMNA*
*Para pintar una columna debemos empezar desde una posicion inicial y desde ahi pintar hacia abajo la columna
*Entonces Vamos a necesitar:
*                                                       x0 := Posicion inicial de la columna
*                                                       x2 := Posicion final de la columna
-----------------------------------------------------------------------------------------------------------------------
 */

pinto_columna:
    //cargar antes en x10 el colorque se quiera y mover el x0 cuanto se necesite
    stur w10, [x0]
    add x0, x0, #2560
    sub x2, x2, #1
	CBNZ x2,pinto_columna

.endif
