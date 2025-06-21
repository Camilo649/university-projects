import numpy as np
from random import random
from math import pi, sqrt
from scipy.stats import norm


# Ejercicio 6: Estime π sorteando puntos uniformemente distribuidos en el cuadrado cuyos vértices son:
# (1, 1), (−1, 1), (−1, −1), (1, −1), y contabilizando la fracción que cae dentro del círculo inscrito de radio 1.


def simularPi():
    u,v = 2*random() - 1, 2*random() - 1
    if u**2 + v**2 <= 1:
        return 4
    return 0


# a) Utilice un algoritmo para estimar la proporción de puntos que caen dentro del círculo y deténgase cuando
# la desviación estandar muestral del estimador sea menor que 0,01.


# ---------------------------------------------- COMPARACIÓN ----------------------------------------------

N = 1_000_000
estimacion = 0
for _ in range(N): estimacion += simularPi()
estimacion /= N

# print(f"Error absoluto para {N} iteraciones: {abs(estimacion - pi):6.6f}")

# ---------------------------------------------- COMPARACIÓN ----------------------------------------------


def EstimarPiRec(d):
    Media, Scuad, n = simularPi(), 0, 1
    while n <= 100 or sqrt(Scuad/n) >= d:
        n += 1
        Media_Ant = Media
        Media = Media_Ant + (simularPi() - Media_Ant) / n
        Scuad = Scuad * (1 - 1/ (n-1)) + n * (Media - Media_Ant)**2
    
    return Media, Scuad, n

media_muestral, varianza_muestral, n = EstimarPiRec(0.01)

print("Estimación Recursiva")
print(f"Estimación de π: {media_muestral}")
print(f"Varianza muestral: {varianza_muestral}")
print(f"Número de simulaciones necesarias: {n}")


# b) Obtenga un intervalo de ancho menor que 0,1, el cual contenga a π con el 95% de confianza. ¿Cuántas
# ejecuciones son necesarias?


def Media_Muestral_Interv(z_alfa_2, L):
    d = L / (2 * z_alfa_2)
    Media, Scuad, n = simularPi(), 0, 1
    while n <= 100 or sqrt(Scuad/n) >= d:
        n += 1
        Media_Ant = Media
        Media = Media_Ant + (simularPi() - Media_Ant) / n
        Scuad = Scuad * (1 - 1/ (n-1)) + n * (Media - Media_Ant)**2
    return Media, n


media_muestral, n = Media_Muestral_Interv(norm.ppf(0.975), 0.1)

print("Estimación con intervalo de confianza del 95% de longitud menor a 0.1")
print(f"Estimación de π: {media_muestral}")
print(f"Número de simulaciones necesarias: {n}")