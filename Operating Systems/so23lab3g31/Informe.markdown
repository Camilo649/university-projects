#**Primera Parte**
##PREGUNTAS
1. ¿Qué política de planificación utiliza xv6-riscv para elegir el próximo proceso a ejecutarse? Pista: xv6-riscv nunca sale de la función scheduler por medios “normales”.
2. ¿Cuánto dura un quantum en xv6-riscv?
3. ¿Cuánto dura un cambio de contexto en xv6-riscv?
4. ¿El cambio de contexto consume tiempo de un quantum?
5. Hay alguna forma de que a un proceso se le asigne menos tiempo? Pista: Se puede empezar a buscar desde la system call uptime.
6. ¿Cúales son los estados en los que un proceso pueden permanecer en xv6-riscv y que los hace cambiar de estado?

###RESPUESTAS
1. Xv6 utiliza la politica de planificacion round-robin, esto se puede ver en el archivo proc.c en la funcion scheduler(), ya que la se encarga de elegir qué proceso ejecutar a continuación.
2. Esto se puede ver en star.c dentro de la funcion timerinit() en la variable interval la cual vale 1000000. Esta constante aproximadamente equivale a 100 milisegundos de tiempo real en qemu. 
3. Para medir el tiempo que demora un context switch, la idea empleada fue crea un programa que solamente ceda el control al sistema operativo, es decir que llame a yield(), una cantidad arbitraria de veces, en este caso 1 millón. El programa llamado context_switch_meter.c se encuentra en una rama aparte denominada context-switch.
El experimento se realizó un total de 4 veces, una por integrante, donde el resultado se consigue de restarle el tiempo aproximado que consume cualquier otra operación involucrada que no sea swtch() al tiempo total de ejecución del programa que se mide con un cronómetro. Para la medición asumimos que cada instrucción en ensamblador dura 4 ciclos de reloj (esto fue lo mejor que encontré según https://www.unioviedo.es/ate/alberto/TEMA3-Ensamblador.pdf, pág 8) y para ver la cantidad de instrucciones que genera cada porción de código en C hice uso de la página https://godbolt.org/.
_____________________________________________________________________________________________________________________________
|          Programa/Función          |Lamadas totales en una iteración|Cantidad total de Instrucciones ejeutadas por llamada|
|------------------------------------|:------------------------------:|:---------------------------------------------------:|
|context_swicht__meter.c             |               1                |                        5000007                      |
|Usys.S - intr_get()                 |               8                |                        3000000                      |
|sysproc.c                           |               1                |                        6000000                      |
|scheduler()                         |               1                |                       22000015                      |
|yield() - myproc()                  |               2                |                       16000000                      |
|push_off()                          |               3                |                       15000000                      |
|intr_on() - intr_off() - r_tp()     |               32               |                        1000000                      |
|mycpu()                             |               26               |                       10000000                      |
|cpuid()                             |               26               |                        9000000                      |
|sched - pop_off()                   |               4                |                       30000000                      |
|acquire()                           |               2                |                       19000000                      |
|holding()                           |               4                |                       20000000                      |
|release()                           |               2                |                       22000000                      |
|_sync_synchronize                   |               4                |                        5000000                      |
|_sync_lock_release                  |               2                |                        7000000                      |

Cabe aclarar que también se consideró el tiempo de reacción promedio al estímulo visual del ser humano sano, el cual es una resta adicional de 0,322 segundos según https://www.redalyc.org/pdf/2742/274222159010.pdf.
Finalmente y luego de sacar el promedio de los experimentos, concluimos que un cambio de contexto en XV6-RISCV durá aproximadamente 71,5 nanosegundos.
4. Si consume tiempo, ya que la ISA de RISCV incorpora un real-time counter (RTC), que se incrementa indefinidamente. El RTC se configura mediante CSR (Control and Status Registers) que se setean en timerinit (start.c) mediante el quantum.
5. Si se le puede asignar menos tiempo a un proceso modificando directamente el quantum.
6. Los estados en los que puede permanecer un proceso son UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE. El cambio de los estados se produce por el uso de las funciones sleep, wakeup, kill, fork, exit.

____________________________________________________________________________

#**Segunda Parte**
##EXPERIMENTO 
Medimos los datos de los procesos iobound y los procesos cpubench planificados segun politica de Round Robin (RR), ejecutando 5 casos en distintos escenarios. 
Los 5 casos son:
1. iobench &
2. cpubench &
3. iobench &; cpubench &
4. cpubench &; iobench &
5. cpubench &; cpubench &; iobench &

Ademas, en cada **escenario** se divide el quantum en 10, es decir:
- Esc. 1, Quantum = 1.000.000
- Esc. 2, Quantum = 100.000
- Esc. 3, Quantum = 10.000
- Esc. 4, Quantum = 1.000

Todas las mediciones se realizaron en un misma computadora con las siguientes especificaciones: 
- Harware: IntelCore i3-1005G1 CPU @1.20GHz / 8GiB RAM
- Software: Version de Qemu 6.2.0

###MEDICIONES

1. 
| Escenario             |        1     |       2     |     3       |         4     |
|-----------------------|:------------:|:-----------:|:-----------:|:-------------:|
| Promedio OPW/100T     | 7956,210526  | 5298,210526 | 7814,736842 | 2857,473684   |
| Promedio OPR/100T     | 7956,210526  | 5298,210526 | 7814,736842 | 2857,473684   |
| Cant. select. IO      | 498809       |  354034     |   625457    | 934022        |

2. 
| Escenario                      |        1     |       2     |     3     |    4     |
|--------------------------------|:------------:|:-----------:|:-----------:|:------:|
| Promedio MFLOPS /100T cpubench | 870,2941176  | 860,8235294 | 755,8888889 | 60,2   |
| Cant. select. CPU              | 2115         |  21090      |   212132    | 979016 |

3. 
| Escenario                      |        1     |       2     |     3       |         4     |
|--------------------------------|:------------:|:-----------:|:-----------:|:-------------:|
| Promedio MFLOPS /100T cpubench | 866,1764706  | 826,875     | 469,6       | 62,16666667   |
| Promedio OPW/100T     | 35,9         | 338,1176471 | 3132,631579 | 1684,315789   |
| Promedio OPR/100T     | 35,9         | 338,1176471 | 3132,631579 | 1684,315789   |
| Cant. select. IO      | 2225         |  20986      |   202582    | 624886        |
| Cant. select. CPU     | 2121         |  21175      |   203523    | 742869        |

4. 
| Escenario                      |        1     |       2     |     3       |         4     |
|--------------------------------|:------------:|:-----------:|:-----------:|:-------------:|
| Promedio MFLOPS /100T cpubench | 864,9411765  | 777,8823529 | 467,2       | 89,625        |
| Promedio OPW/100T     | 35,7         | 337,2941176 | 3107,368421 | 1572,368421   |
| Promedio OPR/100T     | 35,7         | 337,2941176 | 3107,368421 | 1572,368421   |
| Cant. select. IO      | 2225         |  21031      |   201733    | 503701        |
| Cant. select. CPU     | 2098         |  21189      |   203583    | 512417        |

5. 
| Escenario                       |        1     |       2     |     3       |         4     |
|---------------------------------|:------------:|:-----------:|:-----------:|:-------------:|
| Promedio MFLOPS /100T cpubench 1| 974,4210526  | 977,8421053 | 386,1052632 | 68            |
| Promedio MFLOPS /100T cpubench 2| 971,7894737  | 933,9444444 | 235,6363636 | 0             |
| Promedio OPW/100T               | 18,6         | 131,2272727 | 1591,526316 | 1086,263158   |
| Promedio OPR/100T               | 18,6         | 131,2272727 | 1591,526316 | 1086,263158   |
| Cant. select. IO                | 1233         |  10637      |   103049    | 428929        |
| Cant. select. CPU 1             | 1061         |  10569      |   104252    | 479950        |
| Cant. select. CPU 2             | 1059         |  10506      |   104203    | 484145        |

**CONCLUSIÓN** 
■ Genealmente se respeta en todos los casos que conforme se va disminuyendo el quantum los procesos tienden a ser seleccionados una mayor cantidad de veces, pues las interrupciones se vuelven más frecuentes.
■ En todos los casos se logra ver que un quantum lo suficintemenente pequeño como el del escenario 4 resulta ser ineficiente independientemente de la proporción y la naturaleza de los procesos.
■ En los casos 1 y 2 se observa un comportamiento similar, mostrando que el planificador selecciona a cada tipo de proceso por igual.
■ Los casos 3 y 4 son bastante idénticos. En ellos podemos notar que el número de selecciones por parte del planificador no difiere mucho en ambos procesos, lo que refuerza el punto anterior. Pareciera ocurrir que para los escenarios 3 y 4 el quantum se vuelve menor que lo que tarda un proceso iobench en completar efectivamente una escitura o lectura, generando así más selecciones para el proceso cpubench.
■ Análogamente, el caso 5 reparte equitativamente la cantidad de selecciones.
■ Una tendencia es observada en los últimos 3 casos: para quantums cada vez más chicos, los promedios de las operaciones de cómputo tienden a ser menores que los promedios de las operaciones de entrada y salida.
____________________________________________________________________________
 
#**Tercera Parte**
-ACLARACIÓN: Todos los fragmentos de código acontinuación corresponden a la rama mlfq del Lab3.-
Para implementar un planificador Multi-Level Feedback Queue en xv6 primero tuvimos que agregar en la estructura _proc_ ya definida en el archivo proc.h los siguientes campos:
```c
110      int counter;                 //chosen process time 
111      int lastime_exec;            //last time executed
112      int priority;                //pocess priority
```
y también agregar una nueva constante en el archivo param.h que contenga la máxima prioridad aceptada:
```c
2    #define PRIO          3  // maximum number of priority
```
En un principio, tanto el primer programa de usuario que se establece llamando a la función userinit() declarada en proc.c, como cualquier otro proceso que se encuentre en la proc table la cual se inicializa llamando a procinit() que también se declara en proc.c, y todo nuevo proceso que se vaya a ejecutar mediante una llamada a allocproc() declarada en proc.c, comienza con la máxima prioridad (PRIO - 1) y en el caso de allocproc(), también se inicializa el campo _counter_. Cumpliendo así la regla 3.
```c
241    void userinit(void)
242    {
         ፧
260      p->priority = PRIO - 1;
         ፧
264    }
```
```c
47    void procinit(void)
48    {
        ፧
56      p->priority = PRIO - 1;
        ፧
60    }
```
```c
108    static struct proc *
109    allocproc(void)
110    {
       ፧
127    found:
         ፧
130      p->priority = PRIO - 1;
131      p->counter = 0;
         ፧
158    }
```
Las prioridades se van actualizando de acuerdo a la causa de la desplanificación del proceso actual. Si un proceso se bloquea mediante alguna solicitud de E/S terminando así antes de que se acabe un quantum, se pondrá a dormir (y dejará de ejecutar) mediante una llamada a sleep() declarada en proc.c. Por otro lado, cuando un proceso gasta todo un quantum surgue una interrupción por tiempo que desemboca en una llamada a la función yield(), que también se declara en proc.c, cediendo así el control al sistema operativo. Es por esto que para llevar a cabo lo que solicita la regla 4, modifcamos las funciones sleep() y yield() de manera tal de que se aumente (o no) y se disminuya (o no) la prioridad del proceso que está por ser desplanificado respectivamente. 
```c
574    void sleep(void *chan, struct spinlock *lk)
575    {
         ፧
591      if (p->priority < PRIO - 1)
592        p->priority++;
         ፧
602    }
```
```c
540    void yield(void)
541    {
         ፧
545      if (p->priority != 0)
546        p->priority--;
         ፧
549    }
```
También, modificamos ligeramente la función procdump(), ya declarada en proc.c, para que además brinde información acerca de la prioridad de todos los procesos enlistados:
```c
704    void procdump(void)
705    {
         ፧
717     printf("\npid state name cantselect prio\n");
         ፧
726        printf("%d %s %s %d %d", p->pid, state, p->name, p->counter, p->priority);
         ፧
729    }
```
____________________________________________________________________________

#**Cuarta Parte**
##EXPERIMENTO
Al igual que en la *tercera parte*, medimos los datos de los procesos iobound y los procesos cpubench, pero esta vez planificados segun política Multi-level Feedback Queue (MLFQ), ejecutando los mismos 5 casos en los distintos escenarios.

###MEDICIONES

1. 
| Escenario             |        1     |       2     |     3       |         4     |
|-----------------------|:------------:|:-----------:|:-----------:|:-------------:|
| Promedio OPW/100T     | 8397,473684  | 8875,789474 | 8313,263158 | 4114,368421   |
| Promedio OPR/100T     | 8397,473684  | 8875,789474 | 8313,263158 | 4114,368421   |
| Cant. select. IO      | 526180       |  569314     |   668893    | 1179347       |

2. 
| Escenario                      |       1      |      2      |      3      |    4   |
|--------------------------------|:------------:|:-----------:|:-----------:|:------:|
| Promedio MFLOPS /100T cpubench | 870,2941176  | 860,4117647 | 773,9473684 | 42,5   |
| Cant. select. CPU              | 2118         |  21101      |   209967    |2432470 |

3. 
| Escenario                      |       1      |      2      |      3      |       4       |
|--------------------------------|:------------:|:-----------:|:-----------:|:-------------:|
| Promedio MFLOPS /100T cpubench | 866,1764706  | 829,125     | 486,75      | 65,4375       |
| Promedio OPW/100T              | 35,9         | 337,4705882 | 3136        | 1874,684211   |
| Promedio OPR/100T              | 35,9         | 337,4705882 | 3136        | 1874,684211   |
| Cant. select. IO               | 2224         |  21023      |   202769    | 698772        |
| Cant. select. CPU              | 2125         |  21109      |   204457    | 916457        |

4. 
| Escenario                      |       1      |      2      |      3      |       4       |
|--------------------------------|:------------:|:-----------:|:-----------:|:-------------:|
| Promedio MFLOPS /100T cpubench | 864,9411765  | 826,875     | 486,25      | 102,9         |
| Promedio OPW/100T              | 35,7         | 337,4705882 | 3134,315789 | 1859,421053   |
| Promedio OPR/100T              | 35,7         | 337,4705882 | 3134,315789 | 1859,421053   |
| Cant. select. IO               | 2225         |  21026      |   202813    | 698373        |
| Cant. select. CPU              | 2098         |  21178      |   204616    | 1000291       |

5. 
| Escenario                       |       1      |      2      |      3      |       4       |
|---------------------------------|:------------:|:-----------:|:-----------:|:-------------:|
| Promedio MFLOPS /100T cpubench 1| 974,4210526  | 946,5789474 | 722,8421053 | 73,42857143   |
| Promedio MFLOPS /100T cpubench 2| 971,7894737  | 933,1111111 | 697,2941176 | 12            |    
| Promedio OPW/100T               | 18,6         | 337,2941176 | 1589,842105 | 1386,578947   |
| Promedio OPR/100T               | 18,6         | 337,2941176 | 1589,842105 | 1386,578947   |
| Cant. select. IO                | 2227         |  21030      |   102996    | 521511        |
| Cant. select. CPU 1             | 1059         |  10512      |   103055    | 764170        |
| Cant. select. CPU 2             | 1060         |  10585      |   103706    | 807500        |

**CONCLUSIÓN**
■ En líneas generales, la cantidad de veces que se selecciona un proceso en inversamente proporcional a la magnitud del quantum.
■ Aquí también podemos llegar a notar como un quantum tan chico como el del escenario 4 malgasta el procesador, poque efectivamente un cambio de contexto consume parte del quantum y mientras más chico sea este, no solo habran más interrupciones sino que también los procesos perderán relativamente más tiempo del que tienen para operar antes de ser desplanificados.
■ Cuando estamos parados en los casos 1 y 2 donde el proceso que se ejecuta no compite con ningún otro para adquirir la CPU, observamos resultados bastante parecidos entre las políticas Round-Robin y Multi-Level Feedback Queue.  
■ Los casos 3 y 4 mustran dierencias mínimas entre ellos. Podemos destacar que a menudo que se acorta el quantum el crecimiento, en cuanto a cantidad de selecciones se refiere, parece ser mayor para procesos cpubench. Estimamos que esto sucede porque el quantum llega a ser menor que el tiempo que un proceso iobench pasa en estado SLEEPING.
■ Los escenarios 1 y 2 del caso 5 son claves para comprender las diferencias entre RR y MLFQ. Como el planificador prioriza a los procesos que ceden la CPU antes de agotar su quantum, se da que la cantidad de las veces que fue seleccionado un proceso iobench es masomenos igual a la suma entre las selecciones de los 2 procesos cpubench. Para los escenarios 3 y 4 no se cumple esta relación probablemente por lo que se estima en el punto anterior.
■ De los casos en lo que tenemos procesos de distinta índole dentro de la tabla de procesos, vemos como se torna favorecido el tiempo de respuesta, ya que cuando se achica el quantum, se ejecutan más operaciones de escritura/lectura que de cómputo puro. 

#PREGUNTA
¿Se puede producir _starvation_ en el nuevo planificador? Justifique su respuesta.

#RESPUESTA
Sí. En un momento dado, puede ocurrir que tengamos unos cuantos procesos cpubench ya con prioridad 0 y por los menos dos procesos iobench (esto dependerá del número de procesadores) con prioridad 2 tal que alternan constantemente mediante cambios de contexto. Lamentablemente, está situación provocará que los procesos cpubench no se ejecuten hasta que terminen los iobench porque estos tienen mayor prioridad; pudiendo incluso no volver a ejecutar nunca a los procesos con prioridad baja debido a la posible llegada de nuevos procesos.