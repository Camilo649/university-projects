from random import random
from math import sqrt
import matplotlib.pyplot as plt
import numpy as np


def TI():
    U = random()
    if U < 1/6:
        return 6*U
    if U < 0.5:
        return (1 + sqrt(24*U - 3))/2
    return 2*U + 1

N = 1_000_000
muestras = [TI() for _ in range(N)]

# Crear puntos x para la función teórica

x1_vals = np.linspace(0, 3, 1000)
f1_vals = np.piecewise(
    x1_vals,
    [x1_vals < 1, (x1_vals >= 1) & (x1_vals < 2), x1_vals >= 2],
    [
        lambda x: 1/6,
        lambda x: (2*x - 1)/6,
        lambda x: 0.5
    ]
)

# Graficar histograma y función de densidad
plt.figure(num="A", figsize=(10, 5))
plt.hist(muestras, bins=100, density=True, color='skyblue', edgecolor='black', alpha=0.6, label='Simulaciones')
plt.plot(x1_vals, f1_vals, color='magenta', linewidth=2, label='Densidad teórica $f(x)$')
plt.title("Comparación entre simulaciones y densidad teórica")
plt.xlabel("Valor")
plt.ylabel("Densidad")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
