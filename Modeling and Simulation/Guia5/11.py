from random import random
from math import pi, tan
from time import perf_counter as pc
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import cauchy

def TI(lamda):
    """
    Simula X, una variable aleatoria con distribución de Cauchy con parámetreo lamda por el método de la
    Transformada Inversa.
    """
    U = random() - 0.5
    return lamda * tan(pi*U)


def SimularProb(lamda, nsim):
    """
    Estima con nsim iteraciones la probabilidad de que X pertenezca al intervalo (-lamda, lamda), siendo X una 
    variable aleatoria con distribución de Cauchy de parámetro lamda.
    """
    count = 0
    for _ in range(nsim):
        X = TI(lamda)
        if X > -lamda and X < lamda:
            count += 1
    return count/nsim

def RU(lamda):
    """
    Simula X, una variable aleatoria con distribución de Cauchy con parámetreo lamda por el método de Razón
    entre Uniformes sabiendo que Cf es el semicírculo derecho centrado en (0,0) de radio sqrt(1/pi).
    """
    while True:
        U = 1 - random()
        V = random()
        if U**2 + V**2 < 1:
            return lamda * V/U

def eficiencia(n, f, lamda):
    """
    Devuelve el tiempo transcurrido durante n ejecuciones de la función f(lamda), donde f simula a una variable
    aleatoria de distribución Cauchy de parámetro lamda.
    """
    inicio = pc()
    for _ in range(n):
        f(lamda)
    final = pc()
    return final-inicio

nsim = 10_000
lambdas = [0.3, 1, 2.5]
estimaciones = [SimularProb(lambdas[0], nsim), SimularProb(lambdas[1], nsim), SimularProb(lambdas[2], nsim)]
tiempos_TI = [eficiencia(nsim, TI, lambdas[0]), eficiencia(nsim, TI, lambdas[1]), eficiencia(nsim, TI, lambdas[2])]
tiempos_RU = [eficiencia(nsim, RU, lambdas[0]), eficiencia(nsim, RU, lambdas[1]), eficiencia(nsim, RU, lambdas[2])]
valor_real = 0.5

print(f"Lambda | Estimación | Error Absoluto | Tiempo TI | Tiempo RU")
print(f"------------------------------------------------------------")
print(f"1      | {estimaciones[0]:8.8f} | {abs(valor_real-estimaciones[0]):12.12f} | {tiempos_TI[0]:7.7f} | {tiempos_RU[0]:7.7f}")
print(f"2.5    | {estimaciones[1]:8.8f} | {abs(valor_real-estimaciones[1]):12.12f} | {tiempos_TI[1]:7.7f} | {tiempos_RU[1]:7.7f}")
print(f"0.3    | {estimaciones[2]:8.8f} | {abs(valor_real-estimaciones[2]):12.12f} | {tiempos_TI[2]:7.7f} | {tiempos_RU[2]:7.7f}")


# ------------------------ Ploteos ------------------------

nsim = 1_000_000
samples_TI = {l: [TI(l) for _ in range(nsim)] for l in lambdas}

# Filtrar las muestras que caen en el intervalo [-10, 10]
samples_TI_filtered = {l: [x_val for x_val in samples_TI[l] if -10 <= x_val <= 10] for l in lambdas}

x = np.linspace(-10, 10, 1000)

fig, axs = plt.subplots(1, 3, figsize=(16, 8))

for i, l in enumerate(lambdas):
    # Transformada Inversa (filtrada)
    axs[i].hist(samples_TI_filtered[l], bins=100, density=True, alpha=0.6, color='skyblue', label="TI")
    
    # Curva de Cauchy
    y = cauchy(scale=l).pdf(x)
    axs[i].plot(x, y, 'k-', lw=1.5, label="Cauchy(λ)")
    
    axs[i].set_title(f"λ = {l}")
    axs[i].legend()
    axs[i].grid(True)
    
    # Limitar el eje x a [-10, 10]
    axs[i].set_xlim([-10, 10])

plt.suptitle("Transformada Inversa para simular Cauchy(λ)", fontsize=16)
plt.tight_layout(rect=[0, 0, 1, 0.96])
plt.show()

