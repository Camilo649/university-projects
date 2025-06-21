import numpy as np
from random import random
from math import log, pi, sqrt, cos, sin


# Ejercicio 1: Genere n valores de una variable aleatoria normal estándar de manera tal que se cumplan
# las condiciones: n ≥ 100 y S/√n < 0,1, siendo S el estimador de la desviación estándar de los n datos
# generados.

def MetodoPolar():
    """
    Simula X y Y dos variables aleatorias normales estándar mediante el Método Polar.
    """
    Rcuad = -2 * log(1-random())
    Theta = 2 * pi * random()
    X = sqrt(Rcuad) * cos(Theta)
    Y = sqrt(Rcuad) * sin(Theta)
    return X, Y

# Como la desviación estándar es conocida: sqrt(1) = 1, queremos ver que n >= 100 cumple que 1/sqrt(n) < 0.1:
# Como 1/sqrt(100) = 0.1, con n = 101 alcanza.
# Dado que generamos variables aleatorias normales de a 2, tomamos n = 102.
 

# a) ¿Cuál es el número de datos generados efectivamente?

n = 102

print(f"Cantidad de datos generados: {n}")


# b) ¿Cuál es la media muestral de los datos generados?

datos = np.empty(n, dtype=np.float64)
for i in range(0, n, 2):
    datos[i], datos[i+1] = MetodoPolar()

media_muestral = np.mean(datos)

print(f"Media Muestral: {media_muestral}")


# c) ¿Cuál es la varianza muestral de los datos generados?

varianza_muestral = np.var(datos, ddof=0)

print(f"Varianza Muestral: {varianza_muestral}")