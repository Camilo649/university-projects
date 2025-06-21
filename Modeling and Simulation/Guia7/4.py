import numpy as np
np.random.seed(42)
from scipy.stats import kstest
from math import exp


# Ejercicio 4: Calcular una aproximación del p−valor de la hipótesis: “Los siguientes 13 valores provienen
# de una distribución exponencial con media 50,0”:
#   86.0, 133.0, 75.0, 22.0, 11.0, 144.0, 78.0, 122.0, 8.0, 146.0, 33.0, 41.0, 99.0

x = [86.0, 133.0, 75.0, 22.0, 11.0, 144.0, 78.0, 122.0, 8.0, 146.0, 33.0, 41.0, 99.0]
x.sort()

# Para calcular el p-valor, utilizaremos el Test de Kolmogorov-Smirnov:

lamda = 1/50.0

def F(x):
    return 1 - exp(-x*lamda)

def calcular_estadistico():
    d_KS = 0
    uniformes = np.random.uniform(0,1,n)       # Aprovechamos la independencia de la distribución
    uniformes.sort()
    for j in range(n):
        u = uniformes[j]
        d_KS = max(d_KS, (j+1)/n - u, u - j/n)

    return d_KS

n = 13
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

res = kstest(x, 'expon', args=(0, 50))

print(f"p-valor con Test de Kolmogorov-Smirnov (utilizando scipy.stats): {res.pvalue}")