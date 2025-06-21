# Ejercicio 8. Para U1,U2, . . . números aleatorios, se define:
# N = Máximo {n : ∏ Ui >= e^-3, i = 1, . . . , n} 
# Mediante n simulaciones determinar:

# a) Estimar E[N] generando n valores de N. Probar con n = 100,1000,10000,100000,1000000

import random
import numpy as np

def simulacion():
    producto = 1
    n = 0
    while producto >= np.exp(-3):
        u = random.random()
        producto *= u
        n += 1
    return n - 1 

def MonteCarloMax(n):
    esperanza = 0
    for _ in range(n):
        esperanza += simulacion()
            
    return esperanza / n

valor_real = 3
print("Valor real (aproximado):", valor_real)
for n in [100, 1000, 10000, 100000, 1000000]:
    E_N = MonteCarloMax(n)
    print(f"Valor esperado de N con {n} iteraciones: {E_N}, con error: {abs(E_N - valor_real)}")

# b) P(N = i) para i = 0, 1, 2, 3, 4, 5, 6, usando n = 1000000

def MonteCarloProb(n, i):
    contador = 0
    for _ in range(n):
        if simulacion() == i:
            contador += 1
    return contador / n

for i in range(7):
    p = MonteCarloProb(1000000, i)
    print(f"P(N = {i}) con 1000000 iteraciones: {p}")