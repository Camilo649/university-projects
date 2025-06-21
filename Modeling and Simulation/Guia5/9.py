from random import random, uniform
from math import log, pi, sqrt, cos, exp
import numpy as np
from time import perf_counter as pc
import matplotlib.pyplot as plt
from scipy.stats import norm


def AyR():
    """
    Simula Z, una variable aleatoria normal estándar en base a la simulación de |Z| utilizando para ello el método
    de Aceptación y Rechazo con una variable aleatoria exponencial con media 1 como lo indica el ejemplo 5f del
    libro Simulación S.M. Ross (https://eprints.uad.ac.id/13/1/Sheldon_M._Ross_-_Simulation.pdf).
    """
    while True:
        Y1 = -log(1 - random())
        Y2 = -log(1 - random())
        if Y2 - ((Y1 - 1) ** 2)/2 > 0:
            U = random()
            if U < 0.5:
                return Y1
            return -Y1

def MetodoPolar():
    """
    Simula Z, una variable aleatoria normal estándar mediante el Método Polar.
    """
    Rcuad = -2 * log(1-random())
    Theta = 2 * pi * random()
    Z = sqrt(Rcuad) * cos(Theta)
    return Z # Nos quedamos solo con Z pero podríamos devolver también Z' = sqrt(Rcuad) * sin(Theta)

def PolarBoxMuller():
    """
    Simula Z, una variable aleatoria normal estándar mediante el Método Polar pero optimizando las
    transformaciones de Box Muller como se indica en el apunte.
    """
    while True:
        V1 = 2*random() - 1
        V2 = 2*random() - 1
        S = V1*V1 + V2*V2
        if S <= 1:
            U = -2*log(S)/S
            Z = V1 * sqrt(U)
            return Z # Nos quedamos solo con Z pero podríamos devolver también Z' = V2 * sqrt(U)

C = 4 * exp(-0.5) / sqrt(2) # Constante para el método de Razón entre Uniformes
def RazonEntreUniformes():
    """
    Simula Z, una variable aleatoria normal estándar mediante el método de Razón entre Uniformes.
    """
    while True:
        U1 = random()
        U2 = 1 - random()
        Z = C * (U1 - 0.5) / U2
        if Z * Z / 4 < -log(U2):
            return Z


def EsperanzaYVarianza(n,f):
    """
    Devuelve la media muestral y la varianza de n valores generados por la función f
    """
    resultados = np.empty(n)
    for i in range(n):
        resultados[i] = f()
    return np.mean(resultados), np.var(resultados, ddof=1)


def eficiencia(n, f):
    """
    Devuelve el tiempo transcurrido durante n ejecuciones de la función f
    """
    inicio = pc()
    for _ in range(n):
        f()
    final = pc()
    return final-inicio

nsim = 1_000_000
M1, V1 = EsperanzaYVarianza(nsim, AyR)
M2, V2 = EsperanzaYVarianza(nsim, MetodoPolar)
M3, V3 = EsperanzaYVarianza(nsim, PolarBoxMuller)
M4, V4 = EsperanzaYVarianza(nsim, RazonEntreUniformes)
media_real = 0
varianza_real = 1
T1 = eficiencia(nsim, AyR)
T2 = eficiencia(nsim, MetodoPolar)
T3 = eficiencia(nsim, PolarBoxMuller)
T4 = eficiencia(nsim, RazonEntreUniformes)

print(f"Método                | Esperanza | Varianza | Tiempo")
print(f"--------------------------------------------------------------------")
print(f"Aceptación y Rechazo  | {abs(M1):7.7f} | {V1:6.6f} | {T1}")
print(f"Método Polar          | {abs(M2):7.7f} | {V2:6.6f} | {T2/2}")
print(f"Box Muller            | {abs(M3):7.7f} | {V3:6.6f} | {T3/2}")
print(f"Razón entre Uniformes | {abs(M4):7.7f} | {V4:6.6f} | {T4}")


# ------------------------ Ploteos ------------------------

# Generar muestras
samples_AyR = [AyR() for _ in range(nsim)]
samples_MP = [MetodoPolar() for _ in range(nsim)]
samples_PBM = [PolarBoxMuller() for _ in range(nsim)]
samples_REU = [RazonEntreUniformes() for _ in range(nsim)]

# Datos para la curva teórica
x = np.linspace(-5, 5, 500)
pdf = norm.pdf(x)

# Colores
colores = {
    "AyR": "red",
    "MetodoPolar": "blue",
    "PolarBoxMuller": "gold",
    "RazonEntreUniformes": "green"
}

# Subplots tipo logo de Windows
fig, axs = plt.subplots(2, 2, figsize=(12, 8))

# Datos a mostrar
metricas = {
    "AyR": (M1, V1, T1),
    "MetodoPolar": (M2, V2, T2/2),  # Se generan dos normales, pero usamos solo una
    "RazonEntreUniformes": (M4, V4, T4),
    "PolarBoxMuller": (M3, V3, T3/2),  # Igual que el Polar
}

# Función para agregar métricas como texto
def agregar_info(ax, metodo, color):
    mu, var, tiempo = metricas[metodo]
    texto = f"$\\mu$ = {mu:.5f}\n$\\sigma^2$ = {var:.5f}\nTiempo = {tiempo:.3f}s"
    ax.text(0.98, 0.95, texto, transform=ax.transAxes,
            fontsize=9, verticalalignment='top', horizontalalignment='right',
            bbox=dict(boxstyle="round,pad=0.3", facecolor=color, alpha=0.2))

# AyR - rojo - arriba izquierda
axs[0, 0].hist(samples_AyR, bins=100, density=True, color=colores["AyR"], alpha=0.6)
axs[0, 0].plot(x, pdf, 'k-', lw=1.5)
axs[0, 0].set_title("AyR")
axs[0, 0].grid(True)
agregar_info(axs[0, 0], "AyR", colores["AyR"])

# Razón entre Uniformes - verde - arriba derecha
axs[0, 1].hist(samples_REU, bins=100, density=True, color=colores["RazonEntreUniformes"], alpha=0.6)
axs[0, 1].plot(x, pdf, 'k-', lw=1.5)
axs[0, 1].set_title("Razón entre Uniformes")
axs[0, 1].grid(True)
agregar_info(axs[0, 1], "RazonEntreUniformes", colores["RazonEntreUniformes"])

# Método Polar - azul - abajo izquierda
axs[1, 0].hist(samples_MP, bins=100, density=True, color=colores["MetodoPolar"], alpha=0.6)
axs[1, 0].plot(x, pdf, 'k-', lw=1.5)
axs[1, 0].set_title("Método Polar")
axs[1, 0].grid(True)
agregar_info(axs[1, 0], "MetodoPolar", colores["MetodoPolar"])

# Box-Muller - amarillo - abajo derecha
axs[1, 1].hist(samples_PBM, bins=100, density=True, color=colores["PolarBoxMuller"], alpha=0.6)
axs[1, 1].plot(x, pdf, 'k-', lw=1.5)
axs[1, 1].set_title("Box-Muller")
axs[1, 1].grid(True)
agregar_info(axs[1, 1], "PolarBoxMuller", colores["PolarBoxMuller"])

# Layout general
plt.suptitle("Simulación de N(0,1) con 4 métodos — Estilo Windows con métricas", fontsize=14)
plt.tight_layout(rect=[0, 0, 1, 0.96])
plt.show()