from random import random
from time import perf_counter as pc
import numpy as np
import matplotlib.pyplot as plt


def metodo1(n):
    """
    Simula una variable aleatoria con distribución de probabilidad dada por:
        F(x) = x^n
    utilizando el método de la Transformada Inversa.
    """
    U = random()
    return U ** (1/n)

def metodo2(n):
    """
    Simula una variable aleatoria con distribución de probabilidad dada por:
        F(x) = x^n
    utilizando el método de la Aceptacion y Rechazo con una variable uniforme en el intervalo (0,1).
    """
    while True:
        Y = random()
        U = random()
        if U < Y ** (n-1):
            return Y
        
def metodo3(n):
    """
    Simula una variable aleatoria con distribución de probabilidad dada por:
        F(x) = ∏(i=1,n) Fi(x)
    donde cada Fi es la función de distribución de probabilidad de una variable aleatoria uniforme en el
    intervalo (0,1).
    """
    return max(random() for _ in range(n))

n = int(random()*100) + 1 # Elegimos n aleatoriamente entre 1 y 100
print(f"Parámetro n = {n}")

def get_time(m,nsim):
    """
    Devuelve el tiempo transcurrido durante nsim ejecuciones del método m  
    """
    inicio = pc()
    for _ in range(nsim):
        m(n)
    final = pc()
    return final-inicio

nsim = 100_000 # Iteramos 100 mil veces
print(f"Tiempo transcurrido al ejecutar {nsim} iteraciones del método1: {get_time(metodo1,nsim)}")
print(f"Tiempo transcurrido al ejecutar {nsim} iteraciones del método2: {get_time(metodo2,nsim)}")
print(f"Tiempo transcurrido al ejecutar {nsim} iteraciones del método3: {get_time(metodo3,nsim)}")

""" Conclusiones
Claramente el primer método es el más rápido de los 3 puesto que solamente consiste en generar una única variable
aleatoria.
El segundo es el más lento puesto que realice n comparaciones y por cada comparacion genera 2 uniformes, quedando
en un total de 2n variables aleatorias generadas.
Por último, el tercer método consume aproximadamente la mitad del tiempo del segundo método, puesto que siempre
genera n variables aleatorias (la mitada que el método 2) y luego las compara para quedarse con el valor máximo.
"""

# ------------------------ Ploteos ------------------------

# Generamos las muestrasv
samples1 = [metodo1(n) for _ in range(1000000)]
samples2 = [metodo2(n) for _ in range(1000000)]
samples3 = [metodo3(n) for _ in range(1000000)]

# Densidad teórica
x_vals = np.linspace(0, 1, 1000)
f_teorica = n * x_vals ** (n - 1)

# Graficamos

fig, axs = plt.subplots(1, 3, figsize=(18, 5), sharey=True)

def plot_hist(ax, samples, metodo_nombre, color_hist):
    hist, bins = np.histogram(samples, bins=50, range=(0, 1), density=True)
    centers = (bins[:-1] + bins[1:]) / 2
    ax.plot(x_vals, f_teorica, color='red', label='Densidad teórica', linewidth=2)
    ax.bar(centers, hist, width=0.018, alpha=0.6, label='Simulación', color=color_hist)
    ax.set_title(f"{metodo_nombre}")
    ax.set_xlabel("x")
    ax.grid(True)
    ax.legend()

plot_hist(axs[0], samples1, "Método 1 (Transformada Inversa)", "#001f3f")  # Azul marino
plot_hist(axs[1], samples2, "Método 2 (Aceptación y Rechazo)", "#aaaaaa")  # Plateado
plot_hist(axs[2], samples3, "Método 3 (Máximo de Uniformes)", "#FFD700")   # Dorado
axs[0].set_ylabel("Densidad")

plt.suptitle(f"Comparación de los 3 métodos para F(x) = x^{n}", fontsize=16)
plt.tight_layout(rect=[0, 0, 1, 0.95])
plt.show()