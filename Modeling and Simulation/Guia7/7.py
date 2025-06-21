from math import log, exp
from random import random, seed
seed(42)
import numpy as np
from scipy.stats import kstest


# Ejercicio 7: Generar los valores correspondientes a 30 variables aleatorias exponenciales independien-
# tes, cada una con media 1. Luego, en base al estadístico de prueba de Kolmogorov-Smirnov, aproxime el
# p−valor de la prueba de que los datos realmente provienen de una distribución exponencial con media 1.


n = 30

# Generamos la muestra

x = []
for _ in range(n):
    x.append(-log(1-random()))
x.sort()

def F(x):
    return 1 - exp(-x)

def calcular_estadistico():
    d_KS = 0
    uniformes = np.random.uniform(0,1,n)       # Aprovechamos la independencia de la distribución
    uniformes.sort()
    for j in range(n):
        u = uniformes[j]
        d_KS = max(d_KS, (j+1)/n - u, u - j/n)

    return d_KS

d = 0
for j in range(n):
    yj = F(x[j])
    d = max(d, (j+1)/n - yj, yj - j/n)
p_valor = 0
Nsim = 100_000
for _ in range(Nsim):
    d_j = calcular_estadistico()
    if d_j >= d:
        p_valor += 1

p_valor /= Nsim
    
print(f"p-valor con Test de Kolmogorov-Smirnov para {Nsim} simulaciones: {p_valor}")

res = kstest(x, 'expon', args=(0, 1))

print(f"p-valor con Test de Kolmogorov-Smirnov (utilizando scipy.stats): {res.pvalue}")
