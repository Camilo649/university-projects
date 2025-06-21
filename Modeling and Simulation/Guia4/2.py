from random import random
from math import exp
import time

# Ejercicio 2. Se desea construir una aproximación de:
# ∑(k=1,N): exp(k/N), donde N = 10000.


# a) Escriba un algoritmo para estimar la cantidad deseada.

def sumatoriaSimulada(N, M):
    suma = 0
    for _ in range(M):
        U = int(random()*N) + 1
        suma += exp(U/N)

    return (suma/M) * N

# b) Obtenga la aproximación sorteando 100 números aleatorios.

S = sumatoriaSimulada(10000,100)
print(f"Estimacion de la sumatoria para {100} iteraciones: {S}")

# c) Escriba un algoritmo para calcular la suma de los primeros 100 términos, y compare el valor exacto
# con las dos aproximaciones, y el tiempo de cálculo.

def sumatoriaPosta(N):
    suma = 0
    for k in range(N):
        suma += exp(k/N)

    return suma 

valor_exacto = sumatoriaPosta(10000)

inicioA = time.perf_counter()
SA = sumatoriaSimulada(10000,100)
finA = time.perf_counter() 

inicioP = time.perf_counter()
SP = sumatoriaPosta(100)
finP = time.perf_counter() 

print(f"Sumatoria Simulada | Error Absoluto ≈ {abs(SA-valor_exacto):.6f} | Tiempo de Calculo ≈ {finA-inicioA:.6f} |")
print(f"Sumatoria Posta    | Error Absoluto ≈ {abs(SP-valor_exacto):.6f} | Tiempo de Calculo ≈ {finP-inicioP:.6f} |")

