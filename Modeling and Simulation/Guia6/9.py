import numpy as np
import matplotlib.pyplot as plt
import random
from math import log

random.seed(42)

# Ejercicio 9: Considerar un sistema de un único servidor que recibe solicitudes de ejecución de acuerdo a
# un proceso de Poisson no homogéneo. La función de intensidad λ(t) es inicialmente de 4 requerimientos
# por hora, y luego crece de manera lineal durante 5 horas hasta llegar a 19 requerimientos por hora. Luego
# decrece linealmente durante 5 horas hasta alcanzar una tasa de 4 requerimientos por hora.
# Este comportamiento de la función de intensidad se repite de manera indefinida, esto es:
# λ(t + 10) = λ(t), t ≥ 0.
# Suponer que:

# ■ El tiempo de servicio del servidor se distribuye de manera exponencial, con una tasa de 25 servicios
# por hora.
# ■ Siempre que el servidor completa un trabajo y no encuentra trabajos para realizar, deja de funcionar
# por un tiempo uniformemente distribuido en el intervalo (0, 0,3).
# ■ Si al retomar no encuentra trabajos para realizar, vuelve a detenerse con la misma distribución.
# Se pide:

# a) Desarrollar un programa que simule el proceso durante un tiempo T .


def lambda_t(t):
    if 0 <= t <= 5:
        return 4 + 3*t
    return 19 - 3*(t-5)

def generar_llegadas(T):
    llegadas = []
    t = -log(1 - random.random()) / 19
    while t < T:
        V = random.random()
        if V < lambda_t(t%10) / 19:
            llegadas.append(t)
        t += -log(1 - random.random()) / 19

    return llegadas
    
class Cola:
    def __init__(self):
        self.items = []

    def esta_vacia(self):
        return len(self.items) == 0

    def encolar(self, item):
        self.items.append(item)

    def desencolar(self):
        if not self.esta_vacia():
            return self.items.pop(0)
        else:
            return None

    def tamano(self):
        return len(self.items)

def simular(T):
    cola = Cola()
    llegadas = generar_llegadas(T)
    t = 0
    index = 0
    n = len(llegadas)
    idle = 0
    while(t < T):
        if index < n:
            tiempo_llegada = llegadas[index]
            while (t < tiempo_llegada):
                if cola.esta_vacia():
                    e = min(random.uniform(0, 0.3), T-t)
                    idle += e
                    t += e
                else:
                    t += -log(1 - random.random()) / 25 # Tiempo de servicio exponencial(25)
                    cola.desencolar()
            cola.encolar(index) # Encolamos el evento iésimo
            index += 1
        else: 
            while (t < T):
                if cola.esta_vacia():
                    e = min(random.uniform(0, 0.3), T-t)
                    idle += e
                    t += e
                else:
                    t += -log(1 - random.random()) / 25 # Tiempo de servicio exponencial(25)
                    cola.desencolar()
    
    return idle


# b) Realizar 5000 simulaciones para estimar el tiempo esperado que el servidor está fuera de funcionamiento
# en las primeras 100 horas de operación.


# Estimaremos con la media mustral:

nsim = 5000
T = 100
tiempos_de_espera = []
for _ in range(nsim):
    tiempos_de_espera.append(simular(T))

print(f"Estimación del tiempo esperado que el servidor está fuera de funcionamiento en las primeras {T} horas de operación con {nsim} simulaciones: {np.mean(tiempos_de_espera)}")


# c) Representar en un histograma la distribución de los tiempos de parada.


plt.hist(tiempos_de_espera, bins=30, color='skyblue', edgecolor='black')
plt.title(f"Histograma del tiempo de inactividad del servidor\n(T = {T} horas, {nsim} simulaciones)")
plt.xlabel("Tiempo de inactividad (horas)")
plt.ylabel("Frecuencia")
plt.grid(True, linestyle='--', alpha=0.7)
plt.show()