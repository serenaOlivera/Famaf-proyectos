# INFORME

Integrantes del Lab 3: 
    -Diaz Deheza Francisco Alejandro
    -Gonzalez Valdez Emiliano
    -Irrazabal Luca Alfredo
    -Olivera Serena 

## Primera Parte: Estudiando el planificador de xv6-riscv

A la hora de analizar el planificador de xv6 logramos entender en gran medida su funcionamiento, al principio pensamos que seria bastante lineal y directo; pero nos encontramos con que tiene más niveles de indirección de los que pensamos. En que sentido? Bueno, pensábamos que el código estaría distribuido de forma concentrada; siendo esto no mas que una pobre especulación. Pero gracias al manual de xv6 y una lectura mas profunda logramos darle un cierre

### ¿Qué política de planificación utiliza `xv6-riscv` para elegir el próximo proceso a ejecutarse?

Nuestra primera idea con respecto a que política de planificación utilizaría xv6 era FIFO (first in first out). Por lo cual fue muy grato el ver como agrupa los procesos en un array por orden de llegada, lo cual nos hizo pensar que estábamos en lo correcto. **Sin embargo** fue grata la sorpresa al percatarnos de la existencia del famoso *quantum* por lo cual nuestra primera idea se fue a la basura al ver ver que el modelo de planificación que utiliza xv6 no es otro mas que **RR** *(Round Robin para los amigos)*, ya que xv6 maneja los procesos en orden de llegada metiéndoles un timer para que no logren monopolizar el cpu.

### ¿Cuáles son los estados en los que un proceso puede permanecer en xv6-riscv y qué los hace cambiar de estado?

Los estados en los que un proceso puede permanecer en xv6-riscv son:
- **UNUSED**
- **USED**
- **SLEEPING**
- **RUNNABLE**
- **RUNNING**
- **ZOMBIE**

El estado de *UNUSED* se utiliza cuando xv6 está inicializando la tabla de procesos (El array donde se alojan los procesos para su identificación)

El estado *USED* se utiliza para especificar que un proceso fue creado pero no ejecutado. Ocupando un lugar en el array de procesos.

El estado *SLEEPING* se utiliza cuando se llama a la función sleep dentro de un proceso. 

El estado *RUNNABLE* se utiliza para señalar cuando un proceso puede ser elegido por el scheduler para ser el siguiente en ejecución.

El estado *RUNNING* indica que el proceso se está ejecutando actualmente.

El estado *ZOMBIE* se le asigna a los procesos que deberían haber terminado, pero por alguna razón no lo hicieron, ocupando lugar en el espacio de procesos.

- Ejemplo de como seria la vida util de un proceso "**p**":
	Al crear un proceso, **p** ocupará el primer lugar dentro del array de procesos el cual tenga como estado "*UNUSED*". Luego dicho lugar donde fue alocado **p**, pasará a tener estado "*USED*". 
	Una vez alocado, **p** este espacio tendrá estado "*RUNNABLE*",  y esperará que el scheduler lo elija como siguiente proceso a ejecutar. 
	Cuando esto pasa el estado de **p** cambie a "*RUNNING*", mostrará que el proceso está siendo ejecutado actualmente. 
	En el hipotético caso en el que **p** necesite hacer un wait() o esperar la respuesta de algún otro proceso *(Normalmente el hijo)* el estado de **p** cambiará a "*SLEEPING*" y, si al terminar todo lo que tenía que hacer pero, por algún mal funcionamiento, el proceso hijo de **p** no es eliminado, entonces el hijo de **p** tendrá el estado de *ZOMBIE* ya que al haber terminado **p** no hay forma de volver a acceder a su hijo

### ¿Qué es un *quantum*? ¿Dónde se define en el código? ¿Cuánto dura un *quantum* en `xv6-riscv`?

Un quantum podría ser definido como el tiempo de CPU que le corresponde a cada proceso, al terminar el tiempo designado o *quantum* se produce una interrupción, o usualmente llamada timer interrupt o timer, para decidir si se cambiara a otro proceso o no. Esto se suele utilizar en las políticas de planificación de estilo interactivas para evitar que un proceso monopolice la CPU.

En el caso de xv6 el *quantum* es definido como un entero llamado **interval** con el valor de **100000**, que es aproximadamente 1/10 *(una décima)* de segundo de qemu, ubicado dentro de la carpeta *kernel/start.c* 

> ¿Como sabemos que **interval** es nuestro quantum?

Al principio no estábamos seguros si "**interval**" realmente hacía referencia a nuestro *quantum* ya que podría ser algún intervalo de algún otro proceso interno de xv6. Pero al ver que unas lineas debajo de la definición de **Interval** seria definido *scratch*, el cual es un array de *timer_scratch*, concluimos en que **interval** era nuestro quantum.

> ¿Qué hace entonces scratch para que nos diéramos cuenta?

Scratch guarda el tiempo entre timer interrupts *(Donde fue asignada la variable **Interval**)*  y también deja espacio para los registros que serán guardados por *timervec*; el cual es el código assembly en kernel para las machine-mode timer interrupts 

### ¿En qué parte del código ocurre el cambio de contexto en `xv6-riscv`? ¿En qué funciones un proceso deja de ser ejecutado? ¿En qué funciones se elige el nuevo proceso a ejecutar?

Cambiar de contexto de un proceso a otro, implica guardar los registros del proceso "viejo", y restaurar los registros previamente guardados del "nuevo" (o sea, el próximo proceso a ejecutar). El hecho de que el stack pointer y program counter sean guardados y restaurados, implican que el CPU va a cambiar de stacks y cambiar al nuevo código que necesite ejecutar.

**El cambio de contexto en `xv6-riscv` se realiza en *kernel/proc.c*, específicamente entre las funciones  sched y scheduler.**
#### Ida: cambiar de contexto de CPU a proceso
El context switch funciona fácilmente. Cada CPU llama a scheduler, *scheduler* corre un bucle: busca en la tabla de procesos alguno que tenga su p->state como RUNNABLE.
Una vez que lo encuentra, setea la variable anterior como "RUNNING", para indicar que está siendo ejecutado y llama a *swtch* para empezar a hacerlo realmente.
(**swtch** toma dos argumentos: "**struct context _old_**" y "**struct context _new_**". 
Guarda los registros actuales en *old*, carga los registros de *new* y regresa).
Una vez que el proceso haya terminado su quantum o necesite de alguna info I/O bound, "soltará" la CPU.

Por esta razón, **el nuevo proceso a ejecutar siempre se elige en la función scheduler**
#### Vuelta: cambiar de contexto de un proceso a otro (o a la CPU)

Una vez que ocurre un interrupt el usertrap llama a *yield()*, si es que su quantum se acabó, que cambia el estado de RUNNING a RUNNABLE para determinar que el proceso deje de ser ejecutado, y llama a sched, que se encarga de volver al contexto de otro programa. Un dato no menor es que cuando se llama a swtch en sched, swtch, retorna a las instrucciones señaladas por el registro que contiene a la dirección de retorno, que sería la instrucción donde el proceso nuevo habría llamado a swtch anteriormente. 

Ahora si el quantum no se acabó, y el proceso, por alguna otra razón se puso a dormir, quien hace la llamada a sched es *sleep()*

**Esto nos lleva a la conclusión que las funciones en donde un proceso deja de ser ejecutado son en sched y scheduler.**
### ¿El cambio de contexto consume tiempo de un quantum?

La respuesta es **sí**. Tras analizar el código, confirmamos que el cambio de contexto consume tiempo del quantum. Al revisar el archivo swtch.s, se observa que el procesador ejecuta unas 28 instrucciones en cada cambio de contexto, lo que afecta el tiempo del quantum. Aunque 28 instrucciones puedan parecer pocas y el tiempo irrisorio, el consumo de tiempo es significativo, ya que el cambio de contexto actúa como una interrupción global y no solo de un proceso específico.

## Segunda Parte: Medir operaciones de cómputo y de entrada/salida

### Describa los parámetros de los programas cpubench e iobench para este experimento

Al terminar la implementación de las funciones cpubench e iobench, con las cuales realizaremos las mediciones de sus operaciones, de cómputo y de entrada y salida respectivamente; podemos diferenciar los parámentros que utiliza cada una para realizar estas "simulaciones". 

En primer lugar tenemos a cpubench, la cual cuenta la cantidad de operaciones al realizar operaciones del tipo *CPU bound*. Para ello, multiplica 2 matrices de igual tamaño, y su resultado lo divide por *1000*, para posteriormente multiplicar el resultado final por un parámetro el cual define el largo del experimento. 
- El primer parámetro de nuestra función llamado **CPU_MATRIX_SIZE** define el tamaño de las matrices a multiplicar. 
- Nuestro segundo parámetro de cpubench está definido como **CPU_EXPERIMENT_LEN** el cual es define cuantas veces se van a multiplicar estas matrices, siendo este el número por el cual se multiplica la cantidad de operaciones realizadas al multiplicar 2 matrices de tamaño **CPU_MATRIX_SIZE**.
- Un tercer parámetro vendría a ser **MEASURE_PERIOD**, el cual nos define el número por el cual dividimos las operaciones realizadas en la multiplicación de matrices; pero al no ser usado directamente, no estamos seguros si este parámetro realmente es importante o solamente sirve para saber a qué hace referencia la división por *1000* sobre la cantidad de operaciones realizadas.
- Por último tenemos los valores de entrada de esta función, llamados *N* y *pid*. El primero indica cuantas veces se va a ejecutar cpubench a través de un bucle for. Y el segundo da el process id asignado al proceso que se está ejecutando, es decir, el pid del cpubench que está corriendo actualmente.

Una vez terminada la presentación de cpubench, haremos lo mismo con iobench. Primero, la función iobench tiene el mismo fin que cpubench. La diferencia radica en que iobench va a calular las operaciones realizadas por procesos *I/O Bound*, es decir, procesos que casi no están corriendo en cpu y mayormente suelen estar esperando la respuesta de algún dispositivo que les brinde la entrada o complete el output requerido. Para esto crea un path único que utilizará temporalmente donde, utilizando file descriptors, hará varias operaciones de escritura y lectura de archivos para así calcular las operaciones totales realizadas. Para ello iobench también cuenta con un par de parámetros los cuales son:

- **IO_OPSIZE**: Indica el tamaño de la operación de I/O a ser realizada,  es decir, es utilizado para indicar la cantidad de bytes que se usarán en los *write* y *read*.

- **IO_EXPERIMENT_LEN**: Establece cuantas veces se realizarán estos *write* y *read* por cada vez que se llame a iobench.

- Por último se tienen los mismos parámetros que en cpubench, siendo estos últimos *N* y *pid*, los cuales tienen las mismas funcionalidades que en dicho archivo.  *N* indica la cantidad de veces que se ejecutara iobench mientras que pid será el process id asignado.

### ¿Los procesos se ejecutan en paralelo? ¿En promedio, qué proceso o procesos se ejecutan primero? Hacer una observación cualitativa.

Los procesos en si no se ejecutan en paralelo en el sentido de multiplexar los procesos ya que estamos forzando el uso de un solo CPU al ejecutar xv6 con:

```
make CPUS=1 qemu
```

Más bien se ejecutan en "paralelo" en sentido de que, gracias al *context switch* que proporciona xv6, su modelo de planificación se encarga de ir alternando entre procesos para simular este "paralelismo". Por lo cual, teóricamente, no estamos ejecutando ningún proceso en paralelo incluso cuando en la práctica puede llegar a parecer que sí debido a que se está forzando el uso de un único CPU. 

Luego de realizar varias pruebas de ejecución con procesos simultáneos, tenemos los siguientes resultados:

| iobench 4 &; iobench 4 &; iobench 4 & |           |                |                                     |            |               |
| :-----------------------------------: | :-------: | :------------: | :---------------------------------: | :--------: | :-----------: |
|                                       |           |                |                                     |            |               |
|                  pid                  |           |                | Metric(Operaciones per tick) * 1000 | Start tick | Elapsed Ticks |
|                  14                   | [iobench] | metric_name_io |                2942                 |    9172    |      348      |
|                  16                   | [iobench] | metric_name_io |                2255                 |    9173    |      454      |
|                  17                   | [iobench] | metric_name_io |                2265                 |    9176    |      452      |
|                  14                   | [iobench] | metric_name_io |                2572                 |    9521    |      398      |
|                  16                   | [iobench] | metric_name_io |                2612                 |    9629    |      392      |
|                  17                   | [iobench] | metric_name_io |                2605                 |    9629    |      393      |
|                  14                   | [iobench] | metric_name_io |                2652                 |    9919    |      386      |
|                  17                   | [iobench] | metric_name_io |                2652                 |   10023    |      386      |
|                  16                   | [iobench] | metric_name_io |                2485                 |   10023    |      412      |
|                  14                   | [iobench] | metric_name_io |                2860                 |   10305    |      358      |
|                  17                   | [iobench] | metric_name_io |                3056                 |   10411    |      335      |
|16|[iobench]|metric_name_io|2560|10437|400|

| cpubench 20 &; cpubench 20 &; cpubench 20 & |            |                 |                              |            |               |
| :-----------------------------------------: | :--------: | :-------------: | :--------------------------: | :--------: | :-----------: |
|                                             |            |                 |                              |            |               |
|                     pid                     |            |                 | Metric(Operaciones per tick) | Start Tick | Elapsed Ticks |
|                      5                      | [cpubench] | metric_name_cpu |             1825             |    466     |      294      |
|                      7                      | [cpubench] | metric_name_cpu |             1807             |    467     |      297      |
|                      8                      | [cpubench] | metric_name_cpu |             1789             |    468     |      300      |
|                      5                      | [cpubench] | metric_name_cpu |             1825             |    763     |      294      |
|                      7                      | [cpubench] | metric_name_cpu |             1825             |    767     |      294      |
|                      8                      | [cpubench] | metric_name_cpu |             1807             |    771     |      297      |
|                      8                      | [cpubench] | metric_name_cpu |             1789             |    1071    |      300      |
|                      5                      | [cpubench] | metric_name_cpu |             1807             |    1360    |      297      |
|                      7                      | [cpubench] | metric_name_cpu |             1789             |    1361    |      300      |
|                      8                      | [cpubench] | metric_name_cpu |             1789             |    1374    |      300      |
|                      5                      | [cpubench] | metric_name_cpu |             1807             |    1660    |      297      |
|                      7                      | [cpubench] | metric_name_cpu |             1771             |    1664    |      303      |
|                      8                      | [cpubench] | metric_name_cpu |             1771             |    1677    |      303      |
|                      5                      | [cpubench] | metric_name_cpu |             1807             |    1960    |      297      |
|                      7                      | [cpubench] | metric_name_cpu |             1807             |    1970    |      297      |
|                      8                      | [cpubench] | metric_name_cpu |             1789             |    1983    |      300      |
|                      5                      | [cpubench] | metric_name_cpu |             1825             |    2260    |      294      |
|                      7                      | [cpubench] | metric_name_cpu |             1807             |    2270    |      297      |
|                      8                      | [cpubench] | metric_name_cpu |             1807             |    2286    |      297      |
|                      5                      | [cpubench] | metric_name_cpu |             1825             |    2557    |      294      |
|                      7                      | [cpubench] | metric_name_cpu |             1844             |    2570    |      291      |
|                      8                      | [cpubench] | metric_name_cpu |             1807             |    2586    |      297      |
|                      5                      | [cpubench] | metric_name_cpu |             1807             |    2854    |      297      |
|                      7                      | [cpubench] | metric_name_cpu |             1807             |    2864    |      297      |
|                      8                      | [cpubench] | metric_name_cpu |             1754             |    2886    |      306      |
|                      5                      | [cpubench] | metric_name_cpu |             1807             |    3154    |      297      |
|                      7                      | [cpubench] | metric_name_cpu |             1789             |    3164    |      300      |
|                      8                      | [cpubench] | metric_name_cpu |             1807             |    3195    |      297      |
|                      5                      | [cpubench] | metric_name_cpu |             1825             |    3454    |      294      |
|                      7                      | [cpubench] | metric_name_cpu |             1825             |    3467    |      294      |
|                      8                      | [cpubench] | metric_name_cpu |             1807             |    3495    |      297      |
|                      5                      | [cpubench] | metric_name_cpu |             1807             |    3751    |      297      |
|                      7                      | [cpubench] | metric_name_cpu |             1807             |    3764    |      297      |
|                      8                      | [cpubench] | metric_name_cpu |             1807             |    3795    |      297      |
|                      5                      | [cpubench] | metric_name_cpu |             1825             |    4054    |      294      |
|                      7                      | [cpubench] | metric_name_cpu |             1789             |    4064    |      300      |
|                      8                      | [cpubench] | metric_name_cpu |             1789             |    4095    |      300      |
|                      5                      | [cpubench] | metric_name_cpu |             1771             |    4351    |      303      |
|                      7                      | [cpubench] | metric_name_cpu |             1789             |    4367    |      300      |
|                      8                      | [cpubench] | metric_name_cpu |             1789             |    4401    |      300      |
|                      5                      | [cpubench] | metric_name_cpu |             1754             |    4660    |      306      |
|                      7                      | [cpubench] | metric_name_cpu |             1771             |    4670    |      303      |
|                      8                      | [cpubench] | metric_name_cpu |             1754             |    4704    |      306      |
|                      5                      | [cpubench] | metric_name_cpu |             1789             |    4969    |      300      |
|                      7                      | [cpubench] | metric_name_cpu |             1807             |    4976    |      297      |
|                      8                      | [cpubench] | metric_name_cpu |             1771             |    5013    |      303      |
|                      5                      | [cpubench] | metric_name_cpu |             1789             |    5272    |      300      |
|                      7                      | [cpubench] | metric_name_cpu |             1754             |    5276    |      306      |
|                      8                      | [cpubench] | metric_name_cpu |             1771             |    5319    |      303      |
|                      5                      | [cpubench] | metric_name_cpu |             1789             |    5575    |      300      |
|                      7                      | [cpubench] | metric_name_cpu |             1771             |    5585    |      303      |
|                      8                      | [cpubench] | metric_name_cpu |             1771             |    5625    |      303      |
|                      5                      | [cpubench] | metric_name_cpu |             1771             |    5878    |      303      |
|                      7                      | [cpubench] | metric_name_cpu |             1795             |    5891    |      299      |
|                      8                      | [cpubench] | metric_name_cpu |             1924             |    5931    |      279      |
|                      8                      | [cpubench] | metric_name_cpu |             1807             |    168     |      297      |
|                      5                      | [cpubench] | metric_name_cpu |             1825             |    466     |      294      |
|                      7                      | [cpubench] | metric_name_cpu |             1807             |    467     |      297      |

Estos resultados muestran el orden de ejecución de los procesos al ejecutar las pruebas
`iobench 4 &; iobench 4 &; iobench &`
y
`cpubench 20 &; cpubench 4 &; cpubench &`
respectivamente.

Al analizarlos es claro ver que los primeros procesos ejecutados, son los primeros en llegar. Es decir, los procesos se van ejecutando en base al orden de llegada de estos a la *queue* del planificador.

### ¿Cambia el rendimiento de los procesos iobound con respecto a la cantidad y tipo de procesos que se estén ejecutando en paralelo? ¿Por qué?

- Si ejecutamos misma cantidad de procesos iobound que cpubound:

    **tabla 1:**
        $ cpubench 25 &; iobench 5 &; iobench 5 &; iobench 5 & 
        5     [cpubench]      metric_name_cpu 3890    3050    138
        5       [cpubench]      metric_name_cpu 3862    3190    139
        5       [cpubench]      metric_name_cpu 4227    3330    127
        5       [cpubench]      metric_name_cpu 4097    3458    131
        5       [cpubench]      metric_name_cpu 4066    3591    132
        5       [cpubench]      metric_name_cpu 4066    3724    132
        5       [cpubench]      metric_name_cpu 4400    3857    122
        5       [cpubench]      metric_name_cpu 4294    3981    125
        5       [cpubench]      metric_name_cpu 4006    4107    134
        5       [cpubench]      metric_name_cpu 3862    4242    139
        5       [cpubench]      metric_name_cpu 4036    4382    133
        5       [cpubench]      metric_name_cpu 4227    4516    127
        10      [iobench]       metric_name_7   [iobench]       metric_name_io  579     3054    
        1 io     580     3057 1776863  (Acá hubo un timer interrupt)
        5       [cpubench]      metric_name_cpu 2473    4644    217
        9       [iobench]       metric_name_io  556     3056    1839
        5       [cpubench]      metric_name_cpu 4161    4862    129
        5       [cpubench]      metric_name_cpu 3976    4993    135
        5       [cpubench]      metric_name_cpu 4129    5129    130
        5       [cpubench]      metric_name_cpu 4194    5260    128
        5       [cpubench]      metric_name_cpu 3976    5389    135
        5       [cpubench]      metric_name_cpu 4227    5525    127
        5       [cpubench]      metric_name_cpu 4473    5653    120
        5       [cpubench]      metric_name_cpu 4436    5775    121
        5       [cpubench]      metric_name_cpu 3890    5897    138
        5       [cpubench]      metric_name_cpu 3754    6036    143
        5       [cpubench]      metric_name_cpu 3834    6180    140
        5       [cpubench]      metric_name_cpu 4194    6321    128
        7       [iobench]       metric_name_io  598     4825    1710
        9       [iobench]       metric_name_io  620     4898    1651
        10      [iobench]       metric_name_io  593     4826    1724
        10      [iobench]       metric_name_io  2968    6551    3457    [iobench]       metric_name_io  2844    6537 360

	    9       [iobench]       metric_name_io  2327    6551    440
        10      [iobench]       metric_name_io  3075    6898    333
        7       [iobench]       metric_name_io  2730    6898    375
        9       [iobench]       metric_name_io  2860    6992    358
        10      [iobench]       metric_name_io  2592    7232    395
        7       [iobench]       metric_name_io  2797    7274    366
        9       [iobench]       metric_name_io  2820    7350    363

**tabla 2:**

|   Pid    | Column 2   | Column 3        | Metric   |Start Tick|Elapsed Ticks|
| -------- | ---------- | --------------- | -------- | -------- | -------- |
| 9        | [cpubench] | metric_name_cpu | 1503     | 2439     | 357      |
| 10       | [cpubench] | metric_name_cpu | 1420     | 2440     | 378      |
| 7        | [cpubench] | metric_name_cpu | 1278     | 2441     | 420      |
| 9        | [cpubench] | metric_name_cpu | 1185     | 2802     | 453      |
| 10       | [cpubench] | metric_name_cpu | 1209     | 2824     | 444      |
| 7        | [cpubench] | metric_name_cpu | 1077     | 2867     | 498      |
| 9        | [cpubench] | metric_name_cpu | 1420     | 3258     | 378      |
| 10       | [cpubench] | metric_name_cpu | 1409     | 3271     | 381      |
| 7        | [cpubench] | metric_name_cpu | 1365     | 3371     | 393      |
| 9        | [cpubench] | metric_name_cpu | 1656     | 3639     | 324      |
| 10       | [cpubench] | metric_name_cpu | 1641     | 3655     | 327      |
| 7        | [cpubench] | metric_name_cpu | 1466     | 3767     | 366      |
| 9        | [cpubench] | metric_name_cpu | 1641     | 3966     | 327      |
| 10       | [cpubench] | metric_name_cpu | 1737     | 3985     | 309      |
| 7        | [cpubench] | metric_name_cpu | 2407     | 4136     | 223      |
| 5        | [iobench]  | metric_name_io  | 454      | 2437     | 2254     |
| 5        | [iobench]  | metric_name_io  | 2522     | 4692     | 406      |
| 5        | [iobench]  | metric_name_io  | 2455     | 5099     | 417      |
| 5        | [iobench]  | metric_name_io  | 2509     | 5517     | 408      |
| 5        | [iobench]  | metric_name_io  | 2485     | 5926     | 412      |
| 5        | [iobench]  | metric_name_io  | 2540     | 6339     | 403      |
| 5        | [iobench]  | metric_name_io  | 2473     | 6743     | 414      |
| 5        | [iobench]  | metric_name_io  | 2473     | 7158     | 414      |
| 5        | [iobench]  | metric_name_io  | 2497     | 7573     | 410      |
| 5        | [iobench]  | metric_name_io  | 2491     | 7985     | 411      |
| 5        | [iobench]  | metric_name_io  | 2509     | 8397     | 408      |
| 5        | [iobench]  | metric_name_io  | 2461     | 8806     | 416      |
| 5        | [iobench]  | metric_name_io  | 2370     | 9223     | 432      |
| 5        | [iobench]  | metric_name_io  | 2409     | 9656     | 425      |
| 5        | [iobench]  | metric_name_io  | 2409     | 10082    | 425      |
| 5        | [iobench]  | metric_name_io  | 2409     | 10508    | 425      |
| 5        | [iobench]  | metric_name_io  | 2392     | 10934    | 428      |
| 5        | [iobench]  | metric_name_io  | 2449     | 11363    | 418      |
| 5        | [iobench]  | metric_name_io  | 2392     | 11782    | 428      |
| 5        | [iobench]  | metric_name_io  | 2491     | 12210    | 411      |
| 5        | [iobench]  | metric_name_io  | 2443     | 12622    | 419      |
| 5        | [iobench]  | metric_name_io  | 2077     | 13042    | 493      |
| 5        | [iobench]  | metric_name_io  | 2386     | 13536    | 429      |
| 5        | [iobench]  | metric_name_io  | 2438     | 13966    | 420      |
| 5        | [iobench]  | metric_name_io  | 2432     | 14387    | 421      |

- Si ejecutamos mas procesos iobound que cpubound:

| PID |            |                 | Metric(Ops/Ticks) | Start Tick | Elapsed ticks |
| :-: | :--------: | :-------------: | :---------------: | :--------: | :-----------: |
|  5  | [cpubench] | metric_name_cpu |       3651        |    3282    |      147      |
|  5  | [cpubench] | metric_name_cpu |       4294        |    3430    |      125      |
|  5  | [cpubench] | metric_name_cpu |       4294        |    3556    |      125      |
|  5  | [cpubench] | metric_name_cpu |       4294        |    3682    |      125      |
|  5  | [cpubench] | metric_name_cpu |       4129        |    3808    |      130      |
|  5  | [cpubench] | metric_name_cpu |       4227        |    3940    |      127      |
|  5  | [cpubench] | metric_name_cpu |       4473        |    4068    |      120      |
|  5  | [cpubench] | metric_name_cpu |       4294        |    4190    |      125      |
|  5  | [cpubench] | metric_name_cpu |       4129        |    4316    |      130      |
|  5  | [cpubench] | metric_name_cpu |       4006        |    4447    |      134      |
|  9  | [iobench]  | metric_name_io  |        717        |    3286    |     1428      |
| 10  | [iobench]  | metric_name_io  |        701        |    3289    |     1460      |
|  7  | [iobench]  | metric_name_io  |        665        |    3285    |     1538      |
|  9  | [iobench]  | metric_name_io  |       3230        |    4716    |      317      |
| 10  | [iobench]  | metric_name_io  |       2386        |    4752    |      429      |
|  7  | [iobench]  | metric_name_io  |       2760        |    4826    |      371      |
|  9  | [iobench]  | metric_name_io  |       3075        |    5033    |      333      |
| 10  | [iobench]  | metric_name_io  |       3494        |    5184    |      293      |
|  7  | [iobench]  | metric_name_io  |       2813        |    5197    |      364      |
|  9  | [iobench]  | metric_name_io  |       2876        |    5367    |      356      |
| 10  | [iobench]  | metric_name_io  |       3230        |    5479    |      317      |
|  7  | [iobench]  | metric_name_io  |       3567        |    5563    |      287      |
|  9  | [iobench]  | metric_name_io  |       3011        |    5725    |      340      |
|  7  | [iobench]  | metric_name_io  |       3567        |    5851    |      287      |
| 10  | [iobench]  | metric_name_io  |       2673        |    5798    |      383      |
|  9  | [iobench]  | metric_name_io  |       3065        |    6065    |      334      |
|  7  | [iobench]  | metric_name_io  |       2836        |    6138    |      361      |
| 10  | [iobench]  | metric_name_io  |       2566        |    6183    |      399      |
|  7  | [iobench]  | metric_name_io  |       3131        |    6501    |      327      |
|  9  | [iobench]  | metric_name_io  |       2381        |    6401    |      430      |
| 10  | [iobench]  | metric_name_io  |       2844        |    6584    |      360      |
|  9  | [iobench]  | metric_name_io  |       2868        |    6833    |      357      |
|  7  | [iobench]  | metric_name_io  |       2381        |    6828    |      430      |
| 10  | [iobench]  | metric_name_io  |       3180        |    6945    |      322      |
|  7  | [iobench]  | metric_name_io  |       3230        |    7261    |      317      |
|  9  | [iobench]  | metric_name_io  |       2354        |    7191    |      435      |
| 10  | [iobench]  | metric_name_io  |       2420        |    7268    |      423      |
|  7  | [iobench]  | metric_name_io  |       3210        |    7578    |      319      |
|  9  | [iobench]  | metric_name_io  |       3020        |    7628    |      339      |
| 10  | [iobench]  | metric_name_io  |       2381        |    7693    |      430      |

Si ejecutamos más procesos cpubound que iobound  

 `iobench 10 &; cpubench 10 &; cpubench 10 &; cpubench 10 &`

| PID |          |                 | Metric(Ops/Ticks) | Start Tick | Elapsed Ticks |
| :-: | :------: | :-------------: | :---------------: | :--------: | :-----------: |
| 10  | cpubench | metric_name_cpu |        972        |    3267    |      552      |
|  9  | cpubench | metric_name_cpu |        972        |    3287    |      552      |
|  7  | cpubench | metric_name_cpu |        917        |    3451    |      585      |
| 10  | cpubench | metric_name_cpu |       1077        |    3822    |      498      |
|  9  | cpubench | metric_name_cpu |       1052        |    3842    |      510      |
|  7  | cpubench | metric_name_cpu |        817        |    4039    |      657      |
| 10  | cpubench | metric_name_cpu |       1058        |    4326    |      507      |
|  9  | cpubench | metric_name_cpu |       1058        |    4355    |      507      |
|  7  | cpubench | metric_name_cpu |        941        |    4699    |      570      |
| 10  | cpubench | metric_name_cpu |       1065        |    4839    |      504      |
|  9  | cpubench | metric_name_cpu |       1016        |    4868    |      528      |
| 10  | cpubench | metric_name_cpu |       1010        |    5349    |      531      |
|  7  | cpubench | metric_name_cpu |        824        |    5275    |      651      |
|  9  | cpubench | metric_name_cpu |        994        |    5402    |      540      |
| 10  | cpubench | metric_name_cpu |       1040        |    5883    |      516      |
|  9  | cpubench | metric_name_cpu |        983        |    5945    |      546      |
|  7  | cpubench | metric_name_cpu |        813        |    5932    |      660      |
| 10  | cpubench | metric_name_cpu |        994        |    6405    |      540      |
|  9  | cpubench | metric_name_cpu |       1016        |    6500    |      528      |
|  7  | cpubench | metric_name_cpu |        856        |    6595    |      627      |
| 10  | cpubench | metric_name_cpu |       1022        |    6951    |      525      |
|  9  | cpubench | metric_name_cpu |       1010        |    7034    |      531      |
|  7  | cpubench | metric_name_cpu |        840        |    7228    |      639      |
| 10  | cpubench | metric_name_cpu |       1005        |    7485    |      534      |
|  9  | cpubench | metric_name_cpu |        995        |    7571    |      539      |
|  7  | cpubench | metric_name_cpu |       1431        |    7876    |      375      |
|  7  | cpubench | metric_name_cpu |       2796        |    8252    |      192      |
|  5  | iobench  | metric_name_io  |        170        |    2711    |     6002      |
|  5  | iobench  | metric_name_io  |       1654        |    8714    |      619      |


Analizando las 4 tablas, podemos decir que el rendimiento de los procesos
iobound disminuye a medida que hay más cantidad de procesos, lo cual se ve
reflejado en los resultados de nuestra métrica, es decir, la cantidad
de interrupciones promedio que ocurren a lo largo de la ejecución
del proceso.

---

Cambiando algunos valores se pueden obtener los siguientes resultados:

IO_EXPERIMENT_LEN: 20
interval: 10 000

| PID | type | Start Tick | Elapsed Ticks |
| --- | ---- | ---------- | ------------- |
| 5   | io   | 766        | 142           |
| 3   | cpu  | 767        | 155           |
| 3   | cpu  | 923        | 133           |

---

IO_EXPERIMENT_LEN: 20
		interval: 100 000

| PID | type | Start tick | Elapsed Ticks |
| --- | ---- | ---------- | ------------- |
| 3   | cpu  | 55         | 13            |
| 3   | cpu  | 69         | 13            |
| 5   | io   | 55         | 28            |

Para que sea más notorio, se redujo el largo del testeo de i/o drásticamente.

Se observa que, a medida que el intervalo decrementa, también lo hace el tiempo que necesitan los procesos de i/o para terminar.
Esto se debe a que los procesos de cpu en la mayoría de casos son terminados por un timer interrupt.
Debido a esto, se los obliga a liberar el cpu ocupado, permitiendo a los procesos de i/o finalizar antes.

### ¿Cambia el rendimiento de los procesos cpubound con respecto a la cantidad y tipo de procesos que se estén ejecutando en paralelo? ¿Por qué?

Si,nos encontramos en un sistema operativo con un planificador Round Robin y con la limitación de hardware de un solo core, los procesos cpubound deben compartir el tiempo de CPU en porciones fijas, el famosísimo quantum, para garantizar que todos los procesos en ejecución puedan avanzar.
Esto puede generar cierto grado de latencia y disminuir el rendimiento percibido de cada proceso. 


Si lo abstraemos a una situación hipotética, sería como hacer fila en un kiosco, siendo los clientes los procesos y el señor kiosquero el procesador.
En el kiosco de xv6, todos los clientes (procesos) tienen el mismo tiempo para ser atendidos (quantum). 
Si bien este sistema asegura que todos vamos a ser atendidos, si la fila es larga y hay muchos clientes, 
cada uno va a tener que  esperar su turno, lo que puede generar cola y retraso.

/*Sere te robo la prueba realizada arriba, gracias totale*/
| cpubench 20 &; cpubench 20 &; cpubench 20 & |            |                 |                              |            |               | 
| :-----------------------------------------: | :--------: | :-------------: | :--------------------------: | :--------: | :-----------: |
|                                             |            |                 |                              |            |               |
|                     pid                     |            |                 | Metric(Operaciones per tick) | Start Tick | Elapsed Ticks |
|                      5                      | [cpubench] | metric_name_cpu |             1825             |    466     |      294      |
|                      7                      | [cpubench] | metric_name_cpu |             1807             |    467     |      297      |
|                      8                      | [cpubench] | metric_name_cpu |             1789             |    468     |      300      |
|                      5                      | [cpubench] | metric_name_cpu |             1825             |    763     |      294      |
|                      7                      | [cpubench] | metric_name_cpu |             1825             |    767     |      294      |
|                      8                      | [cpubench] | metric_name_cpu |             1807             |    771     |      297      |
|                      8                      | [cpubench] | metric_name_cpu |             1789             |    1071    |      300      |
|                      5                      | [cpubench] | metric_name_cpu |             1807             |    1360    |      297      |
|                      7                      | [cpubench] | metric_name_cpu |             1789             |    1361    |      300      |
|                      8                      | [cpubench] | metric_name_cpu |             1789             |    1374    |      300      |
|                      5                      | [cpubench] | metric_name_cpu |             1807             |    1660    |      297      |
|                      7                      | [cpubench] | metric_name_cpu |             1771             |    1664    |      303      |
|                      8                      | [cpubench] | metric_name_cpu |             1771             |    1677    |      303      |
|                      5                      | [cpubench] | metric_name_cpu |             1807             |    1960    |      297      |
|                      7                      | [cpubench] | metric_name_cpu |             1807             |    1970    |      297      |
|                      8                      | [cpubench] | metric_name_cpu |             1789             |    1983    |      300      |
|                      5                      | [cpubench] | metric_name_cpu |             1825             |    2260    |      294      |
|                      7                      | [cpubench] | metric_name_cpu |             1807             |    2270    |      297      |
|                      8                      | [cpubench] | metric_name_cpu |             1807             |    2286    |      297      |
|                      5                      | [cpubench] | metric_name_cpu |             1825             |    2557    |      294      |
|                      7                      | [cpubench] | metric_name_cpu |             1844             |    2570    |      291      |
|                      8                      | [cpubench] | metric_name_cpu |             1807             |    2586    |      297      |
|                      5                      | [cpubench] | metric_name_cpu |             1807             |    2854    |      297      |
|                      7                      | [cpubench] | metric_name_cpu |             1807             |    2864    |      297      |
|                      8                      | [cpubench] | metric_name_cpu |             1754             |    2886    |      306      |
|                      5                      | [cpubench] | metric_name_cpu |             1807             |    3154    |      297      |
|                      7                      | [cpubench] | metric_name_cpu |             1789             |    3164    |      300      |
|                      8                      | [cpubench] | metric_name_cpu |             1807             |    3195    |      297      |
|                      5                      | [cpubench] | metric_name_cpu |             1825             |    3454    |      294      |
|                      7                      | [cpubench] | metric_name_cpu |             1825             |    3467    |      294      |
|                      8                      | [cpubench] | metric_name_cpu |             1807             |    3495    |      297      |
|                      5                      | [cpubench] | metric_name_cpu |             1807             |    3751    |      297      |
|                      7                      | [cpubench] | metric_name_cpu |             1807             |    3764    |      297      |
|                      8                      | [cpubench] | metric_name_cpu |             1807             |    3795    |      297      |
|                      5                      | [cpubench] | metric_name_cpu |             1825             |    4054    |      294      |
|                      7                      | [cpubench] | metric_name_cpu |             1789             |    4064    |      300      |
|                      8                      | [cpubench] | metric_name_cpu |             1789             |    4095    |      300      |
|                      5                      | [cpubench] | metric_name_cpu |             1771             |    4351    |      303      |
|                      7                      | [cpubench] | metric_name_cpu |             1789             |    4367    |      300      |
|                      8                      | [cpubench] | metric_name_cpu |             1789             |    4401    |      300      |
|                      5                      | [cpubench] | metric_name_cpu |             1754             |    4660    |      306      |
|                      7                      | [cpubench] | metric_name_cpu |             1771             |    4670    |      303      |
|                      8                      | [cpubench] | metric_name_cpu |             1754             |    4704    |      306      |
|                      5                      | [cpubench] | metric_name_cpu |             1789             |    4969    |      300      |
|                      7                      | [cpubench] | metric_name_cpu |             1807             |    4976    |      297      |
|                      8                      | [cpubench] | metric_name_cpu |             1771             |    5013    |      303      |
|                      5                      | [cpubench] | metric_name_cpu |             1789             |    5272    |      300      |
|                      7                      | [cpubench] | metric_name_cpu |             1754             |    5276    |      306      |
|                      8                      | [cpubench] | metric_name_cpu |             1771             |    5319    |      303      |
|                      5                      | [cpubench] | metric_name_cpu |             1789             |    5575    |      300      |
|                      7                      | [cpubench] | metric_name_cpu |             1771             |    5585    |      303      |
|                      8                      | [cpubench] | metric_name_cpu |             1771             |    5625    |      303      |
|                      5                      | [cpubench] | metric_name_cpu |             1771             |    5878    |      303      |
|                      7                      | [cpubench] | metric_name_cpu |             1795             |    5891    |      299      |
|                      8                      | [cpubench] | metric_name_cpu |             1924             |    5931    |      279      |
|                      8                      | [cpubench] | metric_name_cpu |             1807             |    168     |      297      |
|                      5                      | [cpubench] | metric_name_cpu |             1825             |    466     |      294      |
|                      7                      | [cpubench] | metric_name_cpu |             1807             |    467     |      297      |


| cpubench 20 |            |                 |                               |            |               |
| --------------- | ---------- | --------------- | ----------------------------- | ---------- | ------------- |
|                 |            |                 |                               |            |               |
|      pid        | [cpubench] | metric_name_cpu | Metric (Operaciones per tick) | Start Tick | Elapsed Ticks |
| 3               | [cpubench] | metric_name_cpu | 4836                          | 454        | 111           |
| 3               | [cpubench] | metric_name_cpu | 4627                          | 567        | 116           |
| 3               | [cpubench] | metric_name_cpu | 4329                          | 684        | 124           |
| 3               | [cpubench] | metric_name_cpu | 4227                          | 810        | 127           |
| 3               | [cpubench] | metric_name_cpu | 4227                          | 939        | 127           |
| 3               | [cpubench] | metric_name_cpu | 4006                          | 1068       | 134           |
| 3               | [cpubench] | metric_name_cpu | 3834                          | 1204       | 140           |
| 3               | [cpubench] | metric_name_cpu | 4006                          | 1345       | 134           |
| 3               | [cpubench] | metric_name_cpu | 4161                          | 1481       | 129           |
| 3               | [cpubench] | metric_name_cpu | 4161                          | 1611       | 129           |
| 3               | [cpubench] | metric_name_cpu | 4097                          | 1741       | 131           |
| 3               | [cpubench] | metric_name_cpu | 4036                          | 1875       | 133           |
| 3               | [cpubench] | metric_name_cpu | 4161                          | 2009       | 129           |
| 3               | [cpubench] | metric_name_cpu | 3947                          | 2139       | 136           |
| 3               | [cpubench] | metric_name_cpu | 4260                          | 2276       | 126           |
| 3               | [cpubench] | metric_name_cpu | 4329                          | 2404       | 124           |
| 3               | [cpubench] | metric_name_cpu | 4329                          | 2530       | 124           |
| 3               | [cpubench] | metric_name_cpu | 4097                          | 2656       | 131           |
| 3               | [cpubench] | metric_name_cpu | 4194                          | 2789       | 128           |
| 3               | [cpubench] | metric_name_cpu | 4194                          | 2919       | 128           |


Al comparar la primera ejecución con la segunda, se observa una disminución en el rendimiento de cada proceso. 
Esto es evidente en los valores de las métricas: la latencia aumenta y el número de operaciones por tick es menor para cada proceso individual,
ya que la CPU debe alternar constantemente entre ellos.
La cantidad de ticks transcurridos (Elapsed Ticks) también aumenta debido al tiempo de espera y los cambios de contexto, 
lo que reduce la eficiencia general de cada proceso de cpubench.




### ¿Es adecuado comparar la cantidad de operaciones de cpu con la cantidad de operaciones iobound?

En un principio no, porque las operaciones no están directamente relacionadas 
con el tiempo que tarda un proceso en terminar (por ejemplo: un proceso 
cpubound podría haber efectuado 100 operaciones pero cada operación tardó
milésimas de segundo en efectuarse, y otro pudo haber tenido la misma cantidad
de operaciones pero cada operación tardando 2 segundos. Es una diferencia muy
grande que a simple vista no se nota).

En el caso de nuestra métrica implementada si sirve, ya que nos indican cuántas
operaciones son efectuadas por interrupciones cada flanco de timer, por lo que
las operaciones efectuadas nos indican que tánto están usando la CPU y afecta 
en qué tan rápido terminan. 



## Segunda Parte: Medir operaciones de cómputo y de entrada/salida pt2

¿Fue necesario modificar las métricas para que los resultados fueran comparables? ¿Por qué?
Sí, fue necesario modificar las métricas para hacer los resultados comparables. Esto se debe a que la métrica original no tenía en cuenta el tiempo de ejecución de las operaciones. Para obtener una comparación justa entre los diferentes valores de quantum, se necesitaba una métrica que normalizara las operaciones en función del tiempo.

Así lo hicimos:

Primero, creamos una fórmula para medir la eficiencia en la ejecución de operaciones, con el objetivo de evaluar cuántas operaciones de CPU se realizan en relación con el tiempo de ejecución. La fórmula que utilizamos es:

Metrica de eficiencia = total_ops × 1000 / ticks

Esta expresión nos permite calcular la cantidad de operaciones realizadas por cada mil ticks (unidades de tiempo). Luego, calculamos el promedio de los resultados obtenidos para obtener un valor representativo que indique cuántas operaciones de CPU, en promedio, se ejecutan por cada mil ticks. Este promedio nos ayuda a comparar el rendimiento y la eficiencia de las operaciones de CPU en diferentes experimentos y condiciones.

Aqui unos ejemplos de uso: 
En todos los ejemplos se corrio cpubench 5 &; iobench 5 &
En orden descendiente de quantum (100000,10000,1000)

| PID |          | Métrica (Ops/Ticks) | Start Tick | Elapsed Ticks | Resultado de Métrica |
| --- | -------- | ------------------- | ---------- | ------------- | -------------------- |
| 6   | cpubench | 4129                | 243        | 130           | 31761.54             |
| 6   | cpubench | 4006                | 374        | 134           | 29895.52             |
| 6   | cpubench | 3947                | 510        | 136           | 29096.32             |
| 6   | cpubench | 3947                | 647        | 136           | 29096.32             |
| 6   | cpubench | 3947                | 784        | 136           | 29096.32             |
| 5   | iobench  | 1117                | 240        | 916           | 1219.65              |
| 5   | iobench  | 3580                | 1158       | 286           | 12517.48             |
| 5   | iobench  | 3555                | 1445       | 288           | 12343.75             |
| 5   | iobench  | 3531                | 1734       | 290           | 12182.76             |
| 5   | iobench  | 3390                | 2025       | 302           | 11225.83             |

| Promedio Cpubench | Promedio IoBench |
| ----------------- | ---------------- |
| 29789.20          | 9937.89          |

| PID |          | Métrica (Ops/Ticks) | Start Tick | Elapsed Ticks | Resultado de Métrica |
| --- | -------- | ------------------- | ---------- | ------------- | -------------------- |
| 6   | cpubench | 104                 | 10172      | 5130          | 20.27                |
| 5   | iobench  | 127                 | 10162      | 8021          | 15.84                |
| 6   | cpubench | 101                 | 15340      | 5315          | 19.01                |
| 5   | iobench  | 148                 | 18220      | 6893          | 21.47                |
| 6   | cpubench | 111                 | 20706      | 4819          | 23.04                |
| 6   | cpubench | 110                 | 25575      | 4854          | 22.68                |
| 5   | iobench  | 154                 | 25148      | 6646          | 23.17                |
| 6   | cpubench | 105                 | 30480      | 5090          | 20.63                |
| 5   | iobench  | 181                 | 31827      | 5632          | 32.14                |
| 5   | iobench  | 227                 | 37478      | 4510          | 50.33                |

| Promedio Cpubench | Promedio IoBench |
| ----------------- | ---------------- |
| 21.13             | 28.19            |

| PID |          | Métrica (Ops/Ticks) | Start Tick | Elapsed Ticks | Resultado de Métrica |
| --- | -------- | ------------------- | ---------- | ------------- | -------------------- |
| 5   | cpubench | 9                   | 95824      | 56903         | 0.16                 |
| 5   | cpubench | 9                   | 152948     | 57135         | 0.16                 |
| 5   | cpubench | 9                   | 210196     | 56430         | 0.16                 |
| 5   | cpubench | 9                   | 266833     | 56286         | 0.16                 |
| 5   | cpubench | 11                  | 323346     | 45179         | 0.24                 |
| 6   | iobench  | 21                  | 95847      | 48175         | 0.44                 |
| 6   | iobench  | 22                  | 144248     | 46423         | 0.47                 |
| 6   | iobench  | 22                  | 190908     | 45625         | 0.48                 |
| 6   | iobench  | 22                  | 236744     | 46204         | 0.48                 |
| 6   | iobench  | 22                  | 283138     | 46177         | 0.48                 |

| Promedio Cpubench | Promedio IoBench |
| ----------------- | ---------------- |
| 0.18              | 0.47             |

¿Qué cambios se observan con respecto al experimento anterior? ¿Qué comportamientos se mantienen iguales?

Primero que todo el hecho de contar con una métrica modificada nos permite realizar una experimentación más precisa en cuanto a las diferencias de tiempo entre los procesos. Observamos que los valores calculados para la métrica de cpubench son considerablemente menores, lo cual indica una menor eficiencia en el procesamiento de operaciones en relación con el tiempo (ticks) en este experimento. Además, pudimos notar que la cantidad de ticks utilizados es mucho mayor que en experimentos anteriores, lo que sugiere una disminución en la eficiencia.

En cambio, iobench muestra un comportamiento distinto. Sus valores de métrica son más estables en este segundo experimento, lo que sugiere que el rendimiento en operaciones de entrada/salida es más consistente.

Los comportamientos que se mantienen igual incluyen que las métricas de iobench tienden a ser relativamente estables, con valores cercanos entre sí, al igual que en el primer experimento. Además, observamos que cuando aumenta la cantidad de ticks, el valor de la métrica tiende a disminuir.


¿Con un quantum más pequeño, se ven beneficiados los procesos iobound o los procesos cpubound?

Los procesos iobound son los más beneficiados cuando se reduce el tamaño del quantum, ya que suelen pasar una gran parte de su tiempo esperando a que se completen operaciones de entrada/salida, como la lectura y escritura en el disco (lo cual, según Wolo, lleva una eternidad de tiempo). Con un quantum pequeño, el sistema operativo cambia de un proceso a otro con mayor frecuencia, lo que permite que los procesos iobound vuelvan a ejecutarse rápidamente después de completar sus operaciones, reduciendo así su tiempo de espera y mejorando su rendimiento.

Podemos observar esto claramente en la tabla N2, donde se muestra explícitamente cómo se beneficia a los procesos iobound. Sin embargo, también podemos ver en la tabla N3 que, si el quantum es demasiado pequeño, ni los procesos iobound ni los cpubound se ven beneficiados. Además, la reducción del quantum perjudica a los procesos cpubound, ya que estos necesitan períodos largos de ejecución en la CPU para poder completar sus cálculos.


## Cuarta Parte: Implementar MLFQ

### ¿Se puede producir starvation en el nuevo planificador? Justifique su respuesta.

Si porque aunque tenemos un sistema de colas implementado, que ejecutan primero los procesos con más prioridad, no tenemos implementado ningún priority boost, lo que hace que los procesos en la cola con menos prioridad puedan quedarse allí sin tener posibilidad de tener el control de la cpu, y por ende generando starvation.

