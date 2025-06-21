# Ejercicio 4. Un supermercado posee 3 cajas. Por una cuestión de ubicación, el 40 % de los
# clientes eligen la caja 1 para pagar, el 32 % la caja 2, y el 28 % la caja 3. El tiempo que
# espera una persona para ser atendida en cada caja distribuye exponencial con medias de 3, 4
# y 5 minutos respectivamente.
# a) ¿Cuál es la probabilidad de que un cliente espere menos de 4 minutos para ser atendido?

# Rta: Aproximadamente 0,6510. 
# El calculo esta en la carpeta

# b) Si el cliente tuvo que esperar más de 4 minutos. ¿Cuál es la probabilidad de que el 
# cliente haya elegido cada una de las cajas?

# Rta: Aproximadamente 0,3021; 0,3373; 0,3605 para las cajas 1, 2 y 3 respectivamente. 
# El calculo esta en la carpeta

# c) Simule el problema y estime las probabilidades anteriores con 1000 iteraciones.

import numpy as np

prob_cajas = [0.40, 0.32, 0.28]
lambdas = [1/3, 1/4, 1/5]
n = 1000

def a():
    tiempos_espera = []
    for _ in range(n):
        caja = np.random.choice([0, 1, 2], p=prob_cajas)
        tiempo = np.random.exponential(1/lambdas[caja])
        tiempos_espera.append(tiempo)
    return np.mean(np.array(tiempos_espera) < 4)

print("Probabilidad de esperar menos de 4 minutos:", a())

def b():
    tiempos_espera = []
    for i in range(n):
        caja = np.random.choice([0, 1, 2], p=prob_cajas)
        tiempo = np.random.exponential(1/lambdas[caja])
        tiempos_espera.append((caja, tiempo))
    
    # Filtramos los tiempos mayores a 4 minutos
    tiempos_filtrados = [(caja, tiempo) for caja, tiempo in tiempos_espera if tiempo > 4]
    
    # Contamos cuántos clientes eligieron cada caja
    counts = [0, 0, 0]
    for caja, _ in tiempos_filtrados:
        counts[caja] += 1
    
    # Calculamos las probabilidades
    total = sum(counts)
    return [count / total for count in counts]

print("Probabilidades de elegir cada caja dado que el cliente esperó más de 4 minutos:", b())