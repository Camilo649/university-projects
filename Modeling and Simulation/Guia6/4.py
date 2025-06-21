import numpy as np
from random import random
from math import sqrt
from scipy.stats import norm


# Ejercicio 4: Para U1,U2, ... variables aleatorias uniformemente distribuidas en el intervalo (0, 1), se define:
#   N = Mínimo {n : Sumatoria(i=1, n) Ui > 1}
# Esto es, N es igual a la cantidad de números aleatorios que deben sumarse para exceder a 1 (o sea, la constante
# de Euler).


def simulare():
    contador = 0
    suma = 0
    while suma <= 1:
        contador += 1
        suma += random()
    return contador


# a) Estimar e a partir de la media muestral N¯ con 1000 simulaciones.


N = 1_000

muestras = []
for _ in range(N):
    muestras.append(simulare())

print(f"Estimación de e utilizando la media muestral con {N} simulaciones: {np.mean(muestras)}")


# b) Dar el valor obtenido de la varianza muestral de N¯ correspondiente a 1000 ejecuciones de la simulación.


print(f"Varianza muestral con {N} simulaciones: {np.var(muestras, ddof=1)}")


# c) Dar una estimación de e mediante un intervalo de confianza de 95% con longitud a lo sumo 0.025.


def Media_Muestral(z_alfa_2, L):
    d = L / (2 * z_alfa_2)
    Media, Scuad, n = simulare(), 0, 1
    while n <= 100 or sqrt(Scuad/n) > d:
        n += 1
        X = simulare()
        Media_Ant = Media
        Media = Media_Ant + (X - Media_Ant) / n
        Scuad = Scuad * (1 - 1/ (n-1)) + n * (Media - Media_Ant)**2
    return Media, n

media_interv, iteraciones = Media_Muestral(norm.ppf(0.975), 0.025)

print(f"Estimación de e con intervalo de confianza de 95% y longitud a lo sumo 0.025: {media_interv}")
print(f"Fueron requeridas {iteraciones} iteraciones")