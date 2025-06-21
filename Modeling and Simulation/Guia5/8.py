from random import random
from math import sqrt
from time import perf_counter as pc
import matplotlib.pyplot as plt
import numpy as np


def sumUnif():
    """
    Simula una variable aleatoria con densidad triangular viendola como la suma de dos uniformes en el intervalo
    (0,1).
    """
    U = random()
    V = random()
    return U + V

def TI():
    """
    Simula una variable aleatoria con densidad triangular utilizando el método de la Transformada Inversa.
    """
    U = random()
    if U < 0.5:
        return sqrt(2*U)
    return 2 - sqrt(2-(2*U))

def AyR():
    """
    Simula una variable aleatoria con densidad triangular utilizando el método de Aceptación y Rechazo con una
    variable aleatoria uniforme en el intervalo (0,2) y la constante c = 2.
    """
    while True:
        Y = random()*2
        U = random()
        if Y >= 0 and Y < 1:
            if U < Y:
                return Y
        elif Y >= 1 and Y < 2:
            if U < 2-Y:
                return Y


def eficiencia(n, f):
    """
    Devuelve el tiempo transcurrido durante n ejecuciones de la función f
    """
    inicio = pc()
    for _ in range(n):
        f()
    final = pc()
    return final-inicio

def promedio(n, f):
    """
    Devuelve el promedio de n valores generados por la función f
    """
    suma = 0
    for _ in range(n):
        suma += f()
    return suma/n

nsim = 10_000
E1, E2, E3 = eficiencia(nsim,sumUnif), eficiencia(nsim, TI), eficiencia(nsim, AyR)
P1, P2, P3 = promedio(nsim, sumUnif), promedio(nsim, TI), promedio(nsim, AyR)
Promedio_real = 1 # Prueba en la carpeta

print(f"Eficiencia Suma de Uniformes para {nsim} simulaciones: {E1}")
print(f"Eficiencia Transofrmada Inversa para {nsim} simulaciones: {E2}")
print(f"Eficiencia Aceptación y Rechazo para {nsim} simulaciones: {E3}")
print(f"Promedio Suma de Uniformes para {nsim} simulaciones: {P1}, con error absoluto: {abs(Promedio_real-P1)}")
print(f"Promedio Transofrmada Inversa para {nsim} simulaciones: {P2}, con error absoluto: {abs(Promedio_real-P2)}")
print(f"Promedio Aceptación y Rechazo para {nsim} simulaciones: {P3}, con error absoluto: {abs(Promedio_real-P3)}")

def probMayorEstrictoATresMedios(n, f):
    """
    Estima la probabilidad de que la variable aleatoria X sea > 1.5 con n simulaciones.
    La función f debe simular a la variable X.
    """
    contador = 0
    for _ in range(n):
        if f() > 1.5:
            contador += 1
    return contador/n

Prob1, Prob2, Prob3 = probMayorEstrictoATresMedios(nsim, sumUnif), probMayorEstrictoATresMedios(nsim, TI), probMayorEstrictoATresMedios(nsim, AyR)
Probabilidad_real = 0.125
print(f"P(X > 1.5) Suma de Uniformes para {nsim} simulaciones: {Prob1}, con error absoluto: {abs(Probabilidad_real-Prob1)}")
print(f"P(X > 1.5) Transofrmada Inversa para {nsim} simulaciones: {Prob2}, con error absoluto: {abs(Probabilidad_real-Prob2)}")
print(f"P(X > 1.5) Aceptación y Rechazo para {nsim} simulaciones: {Prob3}, con error absoluto: {abs(Probabilidad_real-Prob3)}")

# ------------------------ Ploteos ------------------------

# Simulaciones para graficar
datos1 = [sumUnif() for _ in range(nsim)]
datos2 = [TI() for _ in range(nsim)]
datos3 = [AyR() for _ in range(nsim)]

# Densidad teórica triangular
x = np.linspace(0, 2, 1000)
f_teo = np.where(x < 1, x, 2 - x)

fig, axs = plt.subplots(1, 3, figsize=(18, 5), sharey=True)

# Lista de datos, nombres y colores
datos = [datos1, datos2, datos3]
nombres = ["Suma de Uniformes", "Transformada Inversa", "Aceptación y Rechazo"]
colores = ["green", "purple", "orange"]

# Graficar cada histograma
for i in range(3):
    axs[i].hist(datos[i], bins=50, density=True, alpha=0.6, color=colores[i], label="Simulado")
    axs[i].plot(x, f_teo, 'r--', label="Densidad Teórica")
    axs[i].set_title(nombres[i])
    axs[i].set_xlabel("x")
    axs[i].grid(True)
    axs[i].legend()

axs[0].set_ylabel("Densidad")
plt.suptitle("Comparación de Métodos para Simular la Densidad Triangular", fontsize=16)
plt.tight_layout(rect=[0, 0, 1, 0.95])
plt.show()