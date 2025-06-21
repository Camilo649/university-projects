from random import random, uniform
import matplotlib.pyplot as plt
import numpy as np
from math import sqrt, pi, cos, sin


def Cauchy():
    """
    Simula X, una variable aleatoria con distribución de Cauchy con parámetreo lamda = 1 por el método de Razón
    entre Uniformes sabiendo que Cf es el semicírculo derecho centrado en (0,0) de radio sqrt(1/pi).
    """
    while True:
        U = 1 - random()
        V = random()
        if U**2 + V**2 < 1:
            return V/U

def Cauchy_lamda(lamda):
    """
    Simula Y = lamda*X, aprovechando que lamda*X tiene una distribución de Cauchy con parámetreo lamda.
    """
    return lamda * Cauchy()
        

def SimularProb(lamda, nsim):
    """
    Estima con nsim iteraciones la probabilidad de que X pertenezca al intervalo (-lamda, lamda), siendo X una 
    variable aleatoria con distribución de Cauchy de parámetro lamda.
    """
    count = 0
    for _ in range(nsim):
        X = Cauchy_lamda(lamda)
        if X > -lamda and X < lamda:
            count += 1
    return count/nsim

nsim = 10_000
estimaciones = [SimularProb(1, nsim), SimularProb(2.5, nsim), SimularProb(0.3, nsim)]
valor_real = 0.5

print(f"Lambda | Estimación | Error Absoluto")
print(f"----------------------------------")
print(f"1      | {estimaciones[0]:8.8f} | {abs(valor_real-estimaciones[0])}")
print(f"2.5    | {estimaciones[1]:8.8f} | {abs(valor_real-estimaciones[1])}")
print(f"0.3    | {estimaciones[2]:8.8f} | {abs(valor_real-estimaciones[2])}")


# ------------------------ Ploteos ------------------------

# Radio del semicírculo
r = sqrt(1/pi)

# Valores de lambda y colores asociados
lambdas = [1, 2.5, 0.3]
colores = ['green', 'blue', 'red']
labels = [r'$\lambda=1$', r'$\lambda=2.5$', r'$\lambda=0.3$']

# Crear figura con 3 subplots
fig, axes = plt.subplots(1, 3, figsize=(18, 6))

# Dibujar el contorno del semicírculo una vez
theta = np.linspace(0, pi, 500)
semicirc_x = r * np.cos(theta)
semicirc_y = r * np.sin(theta)

# Generar y graficar para cada lambda
for ax, lamda, color, label in zip(axes, lambdas, colores, labels):
    u_vals = []
    v_vals = []

    for _ in range(60000):
        U = 1 - random()
        V = random()
        if U**2 + V**2 < 1:
            u_vals.append(r * U)
            v_vals.append(r * V) 

    ax.scatter(u_vals, v_vals, s=2, color=color, alpha=0.5, label=label)
    ax.plot(semicirc_x, semicirc_y, color='black', linewidth=2, label='Contorno')

    ax.set_title(f'Puntos para {label}', fontsize=13)
    ax.set_xlim(0, r)
    ax.set_ylim(0, r)
    ax.set_aspect('equal')
    ax.set_xlabel("U * sqrt(1/π)")
    ax.set_ylabel("V * sqrt(1/π)")
    ax.grid(True)
    ax.legend()

plt.suptitle("Puntos (U, V) aceptados en el semicírculo para distintos valores de λ", fontsize=16)
plt.tight_layout(rect=[0, 0.03, 1, 0.95])
plt.show()