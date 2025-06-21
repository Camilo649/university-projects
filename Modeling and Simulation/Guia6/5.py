import numpy as np
from random import random
from math import sqrt
from scipy.stats import norm


# Ejercicio 5: Considere una sucesión de números aleatorios {Ui}i y sea M el primer n tal que la variable Un
# es menor que su variable predecesora. Es decir,
#   M = n tal que U1 ≤ U2 ≤ · · · ≤ Un−1 y Un < Un−1


# a) Justifique que P(M > n) = 1/n!, n ≥ 0.


# Hecho en la carpeta


# b) Utilice la identidad
# E[M] =
# ∞
# ∑
# n=0
# P(M > n)
# para mostrar que E[M] = e.


# Hecho en la carpeta


# c) Utilice el resultado del item anterior para dar un estimador de E[M], calcule el valor de su varianza
# muestral. Mediante una simulación estime el valor de e deteniéndose cuando la varianza muestral sea
# menor que 0,01.

# Estimaremos E[M] con la media muestral y por lo visto en b), la media muestral tambien estima a e.

def simularM():
    count = 1
    U = random()
    U_Ant = 0
    while U_Ant <= U:
        count += 1
        U_Ant = U
        U = random()
    
    return count

def Media_Muestral_Rec(d):
    Media, Scuad, n = simularM(), 0, 1
    while n <= 100 or Scuad/n >= d:
        n += 1
        Media_Ant = Media
        Media = Media_Ant + (simularM() - Media_Ant) / n
        Scuad = Scuad * (1 - 1/ (n-1)) + n * (Media - Media_Ant)**2
    
    return Media, Scuad, n

media_muestral, varianza_muestral, n = Media_Muestral_Rec(0.01)

print("Estimación Recursiva")
print(f"Estimacion de E[M]: {media_muestral}")
print(f"Varianza muestral: {varianza_muestral}")
print(f"Numero de simulaciones necesarias: {n}")


# d) Dé una estimación de e mediante un intervalo de ancho menor que 0,1 y con una confianza del 95%

def Media_Muestral_Interv(z_alfa_2, L):
    d = L / (2 * z_alfa_2)
    Media, Scuad, n = simularM(), 0, 1
    while n <= 100 or sqrt(Scuad/n) >= d:
        n += 1
        Media_Ant = Media
        Media = Media_Ant + (simularM() - Media_Ant) / n
        Scuad = Scuad * (1 - 1/ (n-1)) + n * (Media - Media_Ant)**2
    return Media, n


media_muestral, n = Media_Muestral_Interv(norm.ppf(0.975), 0.1)

print("Estimación con intervalo de confianza del 95% de longitud menor a 0.1")
print(f"Estimacion de E[M]: {media_muestral}")
print(f"Numero de simulaciones necesarias: {n}")