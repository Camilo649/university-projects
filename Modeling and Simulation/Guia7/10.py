import numpy as np
from scipy.stats import kstest
from math import erf, sqrt, log, pi, cos, sin
from random import random, seed
seed(42)


# Ejercicio 10: Decidir si los siguientes datos corresponden a una distribución Normal:
#   91.9, 97.8, 111.4, 122.3, 105.4, 95.0, 103.8, 99.6, 96.6, 119.3, 104.8, 101.7
# Calcular una aproximación del p−valor.


x = [91.9, 97.8, 111.4, 122.3, 105.4, 95.0, 103.8, 99.6, 96.6, 119.3, 104.8, 101.7]
x.sort()
n = len(x)

# Estimamos los parámetros
mu_sombrero = np.mean(x)
sigma_sombrero = np.std(x, ddof=1)

def F_normal(x, mu, sigma):
    z = (x - mu) / (sigma * sqrt(2))
    return 0.5 * (1 + erf(z))

def MetodoPolar():
    """
    Simula Z1 y Z2, dos variables aleatorias normales de parámetros (mu,sigma) mediante el Método Polar.
    """
    Rcuad = -2 * log(1-random())
    Theta = 2 * pi * random()
    X = sqrt(Rcuad) * cos(Theta)
    Y = sqrt(Rcuad) * sin(Theta)
    return X*sigma_sombrero + mu_sombrero, Y*sigma_sombrero + mu_sombrero

def generar_muestra():
    muestra = []
    for _ in range((n+1)//2):
        Z1,Z2 = MetodoPolar()
        muestra.append(Z1)
        muestra.append(Z2)
    
    return muestra

def calcular_estadistico():
    d_KS = 0
    muestra = generar_muestra()
    muestra.sort()
    theta1 = np.mean(muestra)
    theta2 = np.std(muestra, ddof=1)
    for j in range(n):
        y = F_normal(muestra[j], theta1, theta2)
        d_KS = max(d_KS, (j+1)/n - y, y - j/n)

    return d_KS

d = 0
for j in range(n):
    y = F_normal(x[j], mu_sombrero, sigma_sombrero)
    d = max(d, (j+1)/n - y, y - j/n)
p_valor = 0
Nsim = 100_000
for _ in range(Nsim):
    d_j = calcular_estadistico()
    if d_j >= d:
        p_valor += 1

p_valor /= Nsim

print(f"p-valor con Test de Kolmogorov-Smirnov para {Nsim} simulaciones: {p_valor}")

res = kstest(x, 'norm', args=(mu_sombrero, sigma_sombrero))

print(f"p-valor con Test de Kolmogorov-Smirnov (utilizando scipy.stats): {res.pvalue}")

# Como kstets trata a los estimadores como si fueran parámetros, nos quedamos con el p-valor obtenido en la
# simulación

print(f"Conclusión:")
print(f"No hay evidencia suficiente para rechazar H0, por lo que asumimos que los datos siguen una distribución Normal de parámetros ({mu_sombrero},{sigma_sombrero})")