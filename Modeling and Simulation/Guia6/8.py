from random import random


# Ejercicio 8: Sean X1, . . . , Xn variables aleatorias independientes e idénticamente distribuidas con varian-
# za σ2 desconocida. Se planea estimar σ2 mediante la varianza muestral
#   S2 = ∑ (i=1, n): (Xi − Media_muestral)^2 / (n − 1)


# a) Si n = 2, X1 = 1 y X2 = 3, ¿cuál es la estimación “bootstrap” de Var(S2)?

# Estimamos σ2 con S2:

Media_muestral = (1 + 3)/2
Scuad = ((1-Media_muestral)**2 + (3-Media_muestral)**2) / 1

# Como n = 2, hay 2^2 = 4 muestras Bootstrap las cuales son:

muestras_bootstrap = [[1,3], [1,1], [3,3], [3,1]]

# Finalmente, estimamos σ2 como sigue

estimadores = []
for i in range(4):
    B1 = muestras_bootstrap[i][0]
    B2 = muestras_bootstrap[i][1]
    media = (B1 + B2) / 2
    estimadores.append(((B1 - media)**2 + (B2 - media)**2) / 1)
media_estimadores = sum(estimadores)/4
var = sum((theta - media_estimadores) ** 2 for theta in estimadores) / 3

print(f"Estimación Bootstrap de σ2: {var}")


# b) Si n = 15, los datos son:
#   5, 4, 9, 6, 21, 17, 11, 20, 7, 10, 21, 15, 13, 16, 8
# ¿Cómo se calcula la estimación bootstrap en este caso? Dé un valor posible de la estimación.

n = 15
x = [5, 4, 9, 6, 21, 17, 11, 20, 7, 10, 21, 15, 13, 16, 8]

# En este caso, si hicieramos una estimación bootstrap tal como lo indica el método, deberiamos calcular las 15^15
# muestras bootstrap diferentes. Como hacer esto es inviable, tomaremos solamente con M = 10^3 muestras bootstrap
# diferentes y estimaremos σ2 de la misma forma que lo incimos en el inciso a.

M = 10**3

def Media_muestral(n, x):
    Media = 0 
    for i in range(n):
        Media += x[i]

    return Media / n

def Varianza_muestral(n, x, media):
    Scuad = 0
    for i in range(n):
        Scuad += (x[i] - media)**2

    return Scuad / (n-1)

muestras_bootstrap_usadas = set()

# OJO! No hace falta que las muestras sean distintas
def generarMuestraBootstrap(n, x):
    muestra = []
    for _ in range(n):
        I = int(n*random())
        muestra.append(x[I])
    
    key = tuple(sorted(muestra))
    if key not in muestras_bootstrap_usadas:
        muestras_bootstrap_usadas.add(key)
        return muestra

    return generarMuestraBootstrap(n, x)

estimadores = []
Scuad = Varianza_muestral(n, x, Media_muestral(n, x))
for _ in range(M):
    muestra_bootstrap = generarMuestraBootstrap(n, x)
    media = Media_muestral(n, muestra_bootstrap)
    estimadores.append(Varianza_muestral(n, muestra_bootstrap, media))

print(f"Estimación Bootstrap de σ2 con M = 10^3: {Varianza_muestral(M, estimadores, Media_muestral(M, estimadores))}")

# --------------------------------------- VERSION NUMPY ---------------------------------------

import numpy as np


data = np.array([1, 3])
n = len(data)

# Generamos todas las posibles muestras bootstrap (con reemplazo)
# Como n = 2 y 2 valores posibles → 2^2 = 4 muestras
from itertools import product
muestras_bootstrap = list(product(data, repeat=n))  # [(1,1), (1,3), (3,1), (3,3)]

estimadores = []
for muestra in muestras_bootstrap:
    muestra = np.array(muestra)
    estimadores.append(np.var(muestra, ddof=1))

estimadores = np.array(estimadores)

bootstrap_varianza = np.var(estimadores, ddof=1)

print(f"Estimación Bootstrap de σ2 - Versión con numpy: {bootstrap_varianza}")


np.random.seed(6)
data = np.array([5, 4, 9, 6, 21, 17, 11, 20, 7, 10, 21, 15, 13, 16, 8], dtype=float)
n = 15
M = 10**3

estimadores = []
for _ in range(M):
    sample = np.random.choice(data, size=n)
    estimadores.append(np.var(sample, ddof=1))

print(f"Estimación Bootstrap de σ2 con M = 10^3 - Versión con numpy: {np.var(estimadores, ddof=1)}")