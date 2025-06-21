from random import random
from math import log, exp
from time import perf_counter as pc


# Ejercicio 13. Los autobuses que llevan los aficionados a un encuentro deportivo llegan a destino de acuerdo
# con un proceso de Poisson a razón de cinco por hora. La capacidad de los autobuses es una variable
# aleatoria que toma valores en el conjunto: {20, 21, . . . , 40} con igual probabilidad. A su vez, las capacidades
# de dos autobuses distintos son variables independientes. Escriba un algoritmo para simular la llegada de
# aficionados al encuentro en el instante t = 1 hora.

lamda = 5
T = 1

# Notar que U = "capacidad de los autobuses" ~ Unif{20,40}.

def eventosPoissonH(lamda, T):
    """
    Simula un Proceso de Poisson Homogéneo de razón lamda. Devuelve una lista con el tiempo en el que ocurrió
    cada evento hasta un timpo T y cuantos aficionados llegaron en cada arrivo.
    """
    t = -log(1 - random())/lamda
    Eventos = []
    while t <= T:
        Aficionados = int(21*random()) + 20
        Eventos.append((t,Aficionados))
        t += -log(1 - random())/lamda
    return Eventos


eventos = eventosPoissonH(lamda,T)
print("-------------------------------------------- Alogritmo Tradicional --------------------------------------------")
print(f"Cantidad total de aficionadas que llegaron en 1 hora: {sum([aficionados for _, aficionados in eventos])}")
print(eventos)
print()

def PoissonMejorada(lamda):
    """
    Simula X, una variable aleatoria con distribución de Poisson con parámetreo lamda por el método de la
    Transformada Inversa utilizando la versión optimizada vista en el apunte.
    """
    p = exp(-lamda)
    F = p
    for i in range(1, int(lamda)+1): # Acumulamos hasta el valor más probable
        p *= lamda/i
        F += p
    U = random()
    if U >= F:
        j = int(lamda)+1
        while U >= F:
            p *= lamda/j
            F += p
            j += 1
        return j-1
    else:
        j = int(lamda)
        while U < F:
            F -= p
            p *= j/lamda
            j -= 1
        return j+1

def eventosPoissonHAlternativo(lamda, T):
    """
    Simula un Proceso de Poisson Homogéneo de razón lamda utilizando el algoritmo alternativo visto en el apunte. 
    Devuelve una lista con el tiempo en el que ocurrió cada evento hasta un timpo T y cuantos aficionados
    llegaron en cada arrivo.
    """
    n = PoissonMejorada(lamda*T) # n = N(T)
    Uniformes = [random() for _ in range(n)]
    Aficionados = [int(21*random()) + 20 for _ in range(n)]
    Uniformes.sort()
    return [(T * Uniformes[i], Aficionados[i]) for i in range(n)]


eventos = eventosPoissonHAlternativo(lamda,T)
print("-------------------------------------------- Alogritmo Alternativo --------------------------------------------")
print(f"Cantidad total de aficionadas que llegaron en 1 hora: {sum([aficionados for _, aficionados in eventos])}")
print(eventos)
print()


# --- Extra: Verificación \Estadística de la Esperanza ---

def promedio_aficionados(metodo, nsim):
    return sum(
        sum(aficionados for _, aficionados in metodo(lamda, T))
        for _ in range(nsim)
    ) / nsim

# Medición de tiempo
nsim = 10_000
t0 = pc()
promedio_trad = promedio_aficionados(eventosPoissonH, nsim)
t1 = pc()
promedio_alt = promedio_aficionados(eventosPoissonHAlternativo, nsim)
t2 = pc()

print("================================ Verificación estadística ================================")
print(f"Esperanza teórica de aficionados por hora: 150")
print()
print(f"Promedio con método tradicional   : {promedio_trad:.4f} (en {t1 - t0:.2f} segundos)")
print(f"Promedio con método alternativo   : {promedio_alt:.4f} (en {t2 - t1:.2f} segundos)")
print()


# --- Extra: Comparación de Eficiencia ---


def eficiencia(n, f, lamda, T):
    """
    Devuelve el tiempo transcurrido durante n ejecuciones de la función f, donde f simula eventos de un proceso
    de Poisson Homogéneo de razón lamda hasta el tiempo T.
    """
    inicio = pc()
    for _ in range(n):
        f(lamda,T)
    final = pc()
    return final-inicio

# Valores para lamda y T
lambdas = [5, 20, 50]
T_values = [1, 5, 10]

# Número de simulaciones
nsim = 1_000_000

# Imprimir el encabezado del cuadro
print(f"{'Lambda':<10} {'T':<5} {'Método Tradicional':<25} {'Método Alternativo'}")

# Calcular y mostrar los tiempos
for lamda in lambdas:
    for T in T_values:
        tiempo_tradicional = eficiencia(nsim, eventosPoissonH, lamda, T)
        tiempo_alternativo = eficiencia(nsim, eventosPoissonHAlternativo, lamda, T)
        print(f"{lamda:<10} {T:<5} {tiempo_tradicional:<25.6f} {tiempo_alternativo:.6f}")