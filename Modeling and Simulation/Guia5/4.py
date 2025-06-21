from random import random
from math import log
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import quad


def simularX():
    Y = -log(1-random()) # Simulamos exponencial(1)
    U = random()
    return U ** (1/Y)


# Definimos la función de densidad real
def densidad_real(x):
    if x <= 0 or x >= 1:
        return 0
    integrando = lambda y: y * x**(y - 1) * np.exp(-y)
    valor, _ = quad(integrando, 0, np.inf)
    return valor


# ------------------------ Ploteos ------------------------

nsim = 1_000_000
muestras = [simularX() for _ in range(nsim)]

# Evaluamos la densidad real
x_vals = np.linspace(0.001, 0.999, 1000)
f_vals = np.vectorize(densidad_real)(x_vals)

# Histograma de simulación
bins = np.linspace(0, 1, 100)
hist, edges = np.histogram(muestras, bins=bins, density=True)
centers = (edges[:-1] + edges[1:]) / 2

# Graficamos la comparación
plt.figure(figsize=(10, 6))
plt.plot(x_vals, f_vals, label="Densidad teórica", color="red", linewidth=2)
width = bins[1] - bins[0]
plt.bar(centers, hist, width=width * 0.95, alpha=0.6, label="Histograma de simulación")
plt.title("Comparación: Simulación vs Densidad Teórica")
plt.xlabel("x")
plt.ylabel("Densidad")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
