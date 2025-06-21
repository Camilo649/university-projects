import numpy as np
from math import exp
from random import random

def PoissonMejorada(lamda):
    p = exp(-lamda)
    F = p
    for i in range(1, int(lamda)+1): # Acumulamos hasta el valor más probable
        p *= lamda/i
        F += p
    U = random()
    if U >= F:
        j = int(lamda)+1
        while U >= F:
            p *= lamda/j
            F += p
            j += 1
        return j-1
    else:
        j = int(lamda)
        while U < F:
            F -= p
            p *= j/lamda
            j -= 1
        return j+1

datos = np.zeros(30, int) #muestras
N = np.zeros(6, int) #frecuencias observadas
p = np.zeros(6,float) #p(sim)
pvalor = 0
for _ in range(10000):
    for j in range(30):
        datos[j] = PoissonMejorada(2.9)
    N *= 0
    for observacion in datos:
        if observacion < 5:
            N[observacion] += 1
        else:
            N[5] += 1
    _lambda = sum(datos) / len(datos)
    p[0] = exp(-_lambda)
    for i in range(1,5):
        p[i] = p[i-1] * _lambda / i
    p[5] = 1 - sum(p[:5])
    T = 0
    for i in range(6):
        T += (N[i] - 30 * p[i])**2 / (30 * p[i])
    if T >= 19.887012:
        pvalor += 1
print('p valor: ', pvalor / 10000)