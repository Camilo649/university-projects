from random import random, uniform
from math import exp, log
from time import perf_counter as pc


def TI():
    """
    Simula una variable aleatoria con densidad de probabilidad dada por:
        f(x) = 1/x, si 1 <= x <= e
        f(x) = 0  , en otro caso 
    utilizando el método de la Transformada Inversa.
    """
    U = random()
    return exp(U)

def AyR():
    """
    Simula una variable aleatoria con densidad de probabilidad dada por:
        f(x) = 1/x, si 1 <= x <= e
        f(x) = 0  , en otro caso 
    utilizando el método de la Aceptación y Rechazo con una variable aleatoria uniforme en el intervalo (1,e) y la
    constante c = e-1.
    """
    while True:
        Y = uniform(1, exp(1))
        U = random()
        if U < 1/Y:
            return Y


def eficiencia(n, f):
    """
    Devuelve el tiempo transcurrido durante n ejecuciones de la función f
    """
    inicio = pc()
    for _ in range(n):
        f()
    final = pc()
    return final-inicio

def promedio(n, f):
    """
    Devuelve el promedio de n valores generados por la función f
    """
    suma = 0
    for _ in range(n):
        suma += f()
    return suma/n

nsim = 10_000
E1, E2 = eficiencia(nsim, TI), eficiencia(nsim, AyR)
P1, P2 = promedio(nsim, TI), promedio(nsim, AyR)
Promedio_real = exp(1) - 1 # Prueba en la carpeta

print(f"Eficiencia Transofrmada Inversa para {nsim} simulaciones: {E1}")
print(f"Eficiencia Aceptación y Rechazo para {nsim} simulaciones: {E2}")
print(f"Promedio Transofrmada Inversa para {nsim} simulaciones: {P1}, con error absoluto: {abs(Promedio_real-P1)}")
print(f"Promedio Aceptación y Rechazo para {nsim} simulaciones: {P2}, con error absoluto: {abs(Promedio_real-P2)}")

def probMenorOIgualA2(n, f):
    """
    Estima la probabilidad de que la variable aleatoria X sea <= 2 con n simulaciones.
    La función f debe simular a la variable X.
    """
    contador = 0
    for _ in range(n):
        if f() <= 2:
            contador += 1
    return contador/n

Prob1, Prob2 = probMenorOIgualA2(nsim, TI), probMenorOIgualA2(nsim, AyR)
Probabilidad_real = log(2) # Prueba en la carpeta

print(f"P(X <= 2) Transofrmada Inversa para {nsim} simulaciones: {Prob1}, con error absoluto: {abs(Probabilidad_real-Prob1)}")
print(f"P(X <= 2) Aceptación y Rechazo para {nsim} simulaciones: {Prob2}, con error absoluto: {abs(Probabilidad_real-Prob2)}")

