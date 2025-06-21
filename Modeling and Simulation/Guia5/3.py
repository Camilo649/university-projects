from random import random
from math import log

def composicion(func):
    """
    Simula una variable aleatoria con distribución de probabilidad dada por:
        F(x) = Σ(i=1,n) pi*Fi(x)
    donde pi son números no negativos cuya suma es 1 y Fi es la distribucion de probabilidad de la variable
    aleatoria i.
    func es una lista de pares con (pi,Fi(x))
    """
    U = random()
    lista_ordenada = sorted(func, key=lambda par: par[0])
    prob_acumulada = 0
    for p,F in lista_ordenada:
        prob_acumulada += p
        if U < prob_acumulada:
            return F
         
nsim = 10_000
media = 0
for _ in range(nsim):
    V = random()
    func = [(0.5, -log(V)*3), (0.3, -log(V)*5), (0.2, -log(V)*7)]
    media += composicion(func)
media /= nsim

valor_real = 4.4 # Hecho en la carpeta
print(f"Estimación de la media con {nsim} simulaciones: {media}, con error absoluto de {abs(media-valor_real)}")

        