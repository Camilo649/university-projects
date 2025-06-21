from random import random
from math import log, exp, factorial as fact, pi, sqrt
import matplotlib.pyplot as plt
import numpy as np

def Pareto(alpha):
    """
    Simula una variable aleatoria con distribución de Pareto de parámetro alpha mediante el método de la
    Transformada Inversa.
    """
    U = 1-random()
    return (1/U) ** (1/alpha)

def Erlang1(mu, k):
    """
    Simula una variable aleatoria con distribución de Erlang de parámetro alpha mediante el método de Aceptación
    y Rechazo utilizando una variable aleatoria Exponencial de párametro 1/(mu*k).
    """
    while True:
        U = 1-random()
        Y = -log(U)*mu*k
        c = (k**k) / (fact(k-1) * exp(k-1))
        V = random()
        if V < (Y**(k-1) * exp(Y/(mu*k) - Y/mu)) / (fact(k-1) * mu**k * 1/(mu*k) * c):
            return Y 

def Erlang2(mu, k):
    """
    Simula una variable aleatoria con distribución de Erlang de parámetro alpha mediante el método de la
    Transformada Inversa viendo a la variable como una suma de k exponenciales.
    """ 
    U = 1
    for _ in range(k):
        U *= 1-random()
    return -log(U)*mu

def Weibull(lamda, betha):
    """
    Simula una variable aleatoria con distribución de Weibull de parámetros lambda y betha mediante el método de
    la Transformada Inversa.
    """
    U = 1-random()
    return ((-log(U)) ** (1/betha))/lamda

nsim = 1_000_000
valor_real = [2, 4, sqrt(pi/4)]
media = [0] * 4
for _ in range(nsim):
    media[0] += Pareto(2)
    media[1] += Erlang1(2,2)
    media[2] += Erlang2(2,2)
    media[3] += Weibull(1,2)
for i in range(4):
    media[i] /= nsim

print(f"Estimación de la media Pareto(2) con {nsim} simulaciones: {media[0]}, con error absoluto de {abs(media[0]-valor_real[0])}")
print(f"Estimación de la media Erlang(2,2) (AyR) con {nsim} simulaciones: {media[1]}, con error absoluto de {abs(media[1]-valor_real[1])}")
print(f"Estimación de la media Erlang(2,2) (Suma de exps) con {nsim} simulaciones: {media[2]}, con error absoluto de {abs(media[2]-valor_real[1])}")
print(f"Estimación de la media Weibull(1,2) con {nsim} simulaciones: {media[3]}, con error absoluto de {abs(media[3]-valor_real[2])}")


# ------------------------ Ploteos ------------------------

# Simulaciones para graficar
datos_pareto = [Pareto(2) for _ in range(nsim)]
datos_erlang1 = [Erlang1(2, 2) for _ in range(nsim)]
datos_erlang2 = [Erlang2(2, 2) for _ in range(nsim)]
datos_weibull = [Weibull(1, 2) for _ in range(nsim)]

# Densidades Teóricas
x_pareto = np.linspace(1, 10, 1000)
f_pareto = 2 / (x_pareto**3)  # f(x) = 2 / x^3 para x >= 1

x_erlang = np.linspace(0, 20, 1000)
f_erlang = f_erlang = (x_erlang / 4) * np.exp(-x_erlang / 2)  # Erlang(k=2, mu=2)

x_weibull = np.linspace(0, 5, 1000)
f_weibull = 2 * x_weibull * np.exp(-x_weibull**2)  # lambda=1, beta=2

# Pareto
datos_pareto_filtrados = [x for x in datos_pareto if x <= 10]
plt.figure(figsize=(6, 4))
plt.hist(datos_pareto_filtrados, bins=50, density=True, alpha=0.6, color='black', label="Simulado")
plt.plot(x_pareto, f_pareto, 'r--', label="Densidad Teórica")
plt.title("Pareto(2)")
plt.xlabel("x")
plt.ylabel("Densidad")
plt.legend()
plt.grid(True)
plt.xlim(1, 10)
plt.show()

#Erlangs
fig, axs = plt.subplots(1, 2, figsize=(12, 4), sharey=True)

# Erlang (AyR)
axs[0].hist(datos_erlang1, bins=50, density=True, alpha=0.5, color='gray', label="Simulado (AyR)")
axs[0].plot(x_erlang, f_erlang, 'r--', label="Densidad Teórica")
axs[0].set_title("Erlang(2,2) - Aceptación y Rechazo")
axs[0].set_xlabel("x")
axs[0].set_ylabel("Densidad")
axs[0].legend()
axs[0].grid(True)
axs[0].set_xlim(0, 20)

# Erlang (Suma de Exponenciales)
axs[1].hist(datos_erlang2, bins=50, density=True, alpha=0.5, color='gray', label="Simulado (Suma de Exps)")
axs[1].plot(x_erlang, f_erlang, 'r--', label="Densidad Teórica")
axs[1].set_title("Erlang(2,2) - Suma de Exponenciales")
axs[1].set_xlabel("x")
axs[1].legend()
axs[1].grid(True)
axs[1].set_xlim(0, 20)

plt.tight_layout()
plt.show()

# Weibull
plt.figure(figsize=(6, 4))
plt.hist(datos_weibull, bins=50, density=True, alpha=0.6, color='black', label="Simulado")
plt.plot(x_weibull, f_weibull, 'r--', label="Densidad Teórica")
plt.title("Weibull(1,2)")
plt.xlabel("x")
plt.ylabel("Densidad")
plt.legend()
plt.grid(True)
plt.show()