from random import random
from math import sqrt, log
import matplotlib.pyplot as plt
import numpy as np


def a():
    U = random()
    if U < 0.25:
        return 2+2*sqrt(U)
    return 6 - 6*sqrt((1-U)/3)
    
def b():
    U = random()
    if U < 0.6:
        return sqrt(9+((U*35)/3)) - 3
    return ((U*35-19)/2) ** (1/3)

def c():
    U = 1 - random() # Para no calcular log(0)
    if U < 0.0625:
        return log(16*U)/4
    return 4*U - 0.25
    
# ------------------------ Ploteos ------------------------

N = 1_000_000
muestras_a = [a() for _ in range(N)]
muestras_b = [b() for _ in range(N)]
muestras_c = [c() for _ in range(N)]

# /////////////////////////// A ///////////////////////////


# Crear puntos x para la función teórica
x1_vals = np.linspace(2, 6, 1000)
f1_vals = np.piecewise(
    x1_vals,
    [x1_vals <= 3, x1_vals > 3],
    [
        lambda x: (x - 2) / 2,
        lambda x: (2 - x / 3) / 2
    ]
)

# Graficar histograma y función de densidad
plt.figure(num="A", figsize=(10, 5))
plt.hist(muestras_a, bins=100, density=True, color='skyblue', edgecolor='black', alpha=0.6, label='Simulaciones')
plt.plot(x1_vals, f1_vals, color='magenta', linewidth=2, label='Densidad teórica $f(x)$')
plt.title("Comparación entre simulaciones y densidad teórica")
plt.xlabel("Valor")
plt.ylabel("Densidad")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# /////////////////////////// B ///////////////////////////

# Crear puntos x para la función teórica
x2_vals = np.linspace(0, 2, 1000)
f2_vals = np.piecewise(
    x2_vals,
    [x2_vals < 1, x2_vals >= 1],
    [
        lambda x: (6 * (x + 3)) / 35,
        lambda x: (6 * x**2) / 35
    ]
)

# Graficar histograma y función de densidad
plt.figure(num="B", figsize=(10, 5))
plt.hist(muestras_b, bins=100, density=True, color='darkgreen', edgecolor='black', alpha=0.6, label='Simulaciones')
plt.plot(x2_vals, f2_vals, color='darkorange', linewidth=2, label='Densidad teórica $f(x)$')
plt.title("Comparación entre simulaciones y densidad teórica")
plt.xlabel("Valor")
plt.ylabel("Densidad")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# /////////////////////////// C ///////////////////////////

# Crear puntos x para la función teórica
x3_vals = np.linspace(-5, 15/4, 1000)
f3_vals = np.piecewise(
    x3_vals,
    [x3_vals <= 0, (x3_vals > 0) & (x3_vals <= 15/4)],
    [
        lambda x: np.exp(4 * x) / 4,
        lambda x: 0.25
    ]
)

# Graficar histograma y función de densidad
plt.figure(num="C", figsize=(10, 5))
plt.hist(muestras_c, bins=100, density=True, color='gold', edgecolor='black', alpha=0.6, label='Simulaciones')
plt.plot(x3_vals, f3_vals, color='mediumvioletred', linewidth=2, label='Densidad teórica $f(x)$')
plt.title("Comparación entre simulaciones y densidad teórica")
plt.xlabel("Valor")
plt.ylabel("Densidad")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()