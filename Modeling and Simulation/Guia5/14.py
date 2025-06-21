from random import random
from math import log
from time import perf_counter as pc


def eventosPoissonNH(lamda,lambda_t,T):
    """
    Simula un Proceso de Poisson No Homogéneo mediante el método de adelgazamiento cuya función de intensidad es 
    lambda_t. Devuelve una lista con el tiempo en el que ocurrió cada evento hasta un timpo T y el número total
    de eventos.
    """
    Eventos = []
    t = -log(1 - random()) / lamda
    while t <= T:
        V = random()
        if V < lambda_t(t) / lamda:
            Eventos.append(t)
        t += -log(1 - random()) / lamda
    return Eventos, len(Eventos)

def lambda_t1(t):
    if t >= 0 and t <= 3:
        return 3 + 4/(t+1)
    return 0
    
def lambda_t2(t):
    if t >= 0 and t <= 5:
        return (t-2) ** 2 -5*t + 17
    return 0

def lambda_t3(t):
    if t >= 2 and t < 3:
        return t/2 -1
    elif t >= 3 and t <= 6:
        return 1 - t/6
    return 0

intensidades = [lambda_t1, lambda_t2, lambda_t3]
lambdas = [7, 21, 0.5] # Justificación en la carpeta
T = 3 # Valor de prueba

for i in range(3):
    eventos, nt = eventosPoissonNH(lambdas[i], intensidades[i], T)
    print(f"----------------------------------------- Proceso {i+1} Estándar -----------------------------------------")
    print(f"Cantidad Total de eventos: {nt}")
    print(eventos)
    print()


def eventosPoissonNHMejorado(lamda,interv,lambda_t,T):
    """
    Simula un Proceso de Poisson No Homogéneo cuya función de intensidad es lambda_t mediante el método de 
    adelgazamiento con subintervalos y reutilizando la ultima exponencial generada en cada subintervalo. Devuelve
    una lista con el tiempo en el que ocurrió cada evento hasta un timpo T y el número total de eventos.
    """
    Eventos = []
    j = 0
    t = -log(1 - random()) / lamda[j]
    while t <= T:
        if t <= interv[j]:
            V = random()
            if V < lambda_t(t) / lamda[j]:
                Eventos.append(t)
            t += -log(1 - random()) / lamda[j]
        else:
            t = interv[j] + (t - interv[j]) * lamda[j] / lamda[j+1] # Reutilizamos la exponencial que se "pasa" del subintervalo
            j += 1
    return Eventos, len(Eventos)    

# Partimos las intensidades en intervalos y buscamos el maximo lambda ahi

# I1 = [0,1]; I2 = (1,2]; I3 = (2,3]
interv1 = [1, 2, 3]
lambda1 = [7, 5, 4/3]
# I1 = [0,1]; I2 = (1,2]; I3 = (2,3]; I4 = (3,4]; I5 = (4,5]
interv2 = [1, 2, 3, 4, 5]
lambda2 = [21, 13, 7, 3, 1] # Nota: El vértice de lambda_t se encuentra en 4.5
# I1 = [2,2.5]; I2 = (2.5,4.5]; I3 = (4.5,6]
interv3 = [2.5, 4.5, 6]
lambda3 = [0.25, 0.5, 0.25]

intervs = [interv1, interv2, interv3]
lambdas = [lambda1, lambda2, lambda3]
T = 3

for i in range(3):
    eventos, nt = eventosPoissonNHMejorado(lambdas[i], intervs[i], intensidades[i], T)
    print(f"----------------------------------------- Proceso {i+1} Mejorado -----------------------------------------")
    print(f"Cantidad Total de eventos: {nt}")
    print(eventos)
    print()

def eficiencia1(n, f, lamda, lambda_t, T):
    """
    Devuelve el tiempo transcurrido durante n ejecuciones de la función f, donde f simula eventos de un proceso
    de Poisson No Homogéneo de intensidad lamda_t hasta el tiempo T implementado con el algoritmo de
    adelgazamiento estándar.
    """
    inicio = pc()
    for _ in range(n):
        f(lamda,lambda_t,T)
    final = pc()
    return final-inicio

def eficiencia2(n, f, lamda, interv, lambda_t, T):
    """
    Devuelve el tiempo transcurrido durante n ejecuciones de la función f, donde f simula eventos de un proceso
    de Poisson No Homogéneo de intensidad lamda_t hasta el tiempo T implementado con el algoritmo de
    adelgazamiento mejorado.
    """
    inicio = pc()
    for _ in range(n):
        f(lamda,interv,lambda_t,T)
    final = pc()
    return final-inicio

# Valores para lamda y T
lambdasE = [7, 21, 0.5]
lambdasM = [lambda1, lambda2, lambda3]
T_values = [3, 5, 6]  # Máximos T para cada proceso

# Número de simulaciones
nsim = 1_000_000

# Imprimir el encabezado del cuadro
print(f"{'T':<5} {'Método Estándar':<25} {'Método Mejorado'}")

# Calcular y mostrar los tiempos
for i in range(3):
    tiempo_estandar = eficiencia1(nsim, eventosPoissonNH, lambdasE[i], intensidades[i], T_values[i])
    tiempo_mejorado = eficiencia2(nsim, eventosPoissonNHMejorado, lambdasM[i], intervs[i], intensidades[i], T_values[i])
    print(f"{T_values[i]:<5} {tiempo_estandar:<25.6f} {tiempo_mejorado:.6f}")
