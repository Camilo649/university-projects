from random import random
from math import log
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import ks_2samp


def generarM():
    X1 = -log(1-random())/1
    X2 = -log(1-random())/2
    X3 = -log(1-random())/3
    return max(X1,X2,X3)

def generarm():
    X1 = -log(1-random())/1
    X2 = -log(1-random())/2
    X3 = -log(1-random())/3
    return min(X1,X2,X3)

M_vals = [generarM() for _ in range(10)]
m_vals = [generarm() for _ in range(10)]

print(f"Valores de M: {M_vals}")
print(f"Valores de m: {m_vals}")


# ------------------------ Ploteos ------------------------

# Generamos las muestras
M_vals = [generarM() for _ in range(1000000)]
m_vals = [generarm() for _ in range(1000000)]

# Configuramos la figura para dos gráficos
plt.figure(figsize=(12, 6))

# Histograma de M (máximo)
plt.subplot(1, 2, 1)
count, bins, ignored = plt.hist(M_vals, bins=50, density=True, alpha=0.6, color='g', edgecolor='black', label="Histograma de M (máximo)")

# Curva teórica de f_M(x)
x_vals = np.linspace(0, max(M_vals), 1000)
f_M_theoretical = np.exp(-6*x_vals) * (np.exp(x_vals) - 1)**2 * (7*np.exp(x_vals) + 4*np.exp(2*x_vals) + np.exp(3*x_vals) + 6)
plt.plot(x_vals, f_M_theoretical, color='r', label="Curva teórica de f_M(x)", linewidth=2)

plt.title("Comparación de la PDF de M (máximo)")
plt.xlabel("Valor de M")
plt.ylabel("Densidad de probabilidad")
plt.legend()

# Histograma de m (mínimo)
plt.subplot(1, 2, 2)
count, bins, ignored = plt.hist(m_vals, bins=50, density=True, alpha=0.6, color='b', edgecolor='black', label="Histograma de m (mínimo)")

# Generamos la curva teórica de f_m(x)
x_vals = np.linspace(0, max(m_vals), 1000)
f_m_theoretical = 6 * np.exp(-6 * x_vals)
plt.plot(x_vals, f_m_theoretical, color='r', label="Curva teórica de f_m(x)", linewidth=2)

plt.title("Comparación de la PDF de m (mínimo)")
plt.xlabel("Valor de m")
plt.ylabel("Densidad de probabilidad")
plt.legend()

# Mostrar ambos gráficos
plt.tight_layout()
plt.show()