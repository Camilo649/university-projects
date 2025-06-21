# Ejercicio 7. Para U1,U2, . . . variables aleatorias uniformemente distribuídas en el 
# intervalo (0, 1), se define:
# N = Mínimo{n : ∑ Ui > 1, i = 1, . . . , n}
# Es decir, N es igual a la cantidad de números aleatorios que deben sumarse para exceder a 1.

# a) Estimar E[N] generando n valores de N. Probar con n = 100,1000,10000,100000,1000000

import random
import numpy as np

def simulacion():
    suma = 0
    n = 0
    while suma <= 1:
        u = random.random()
        suma += u
        n += 1
    return n

def MonteCarloMin(n):
    esperanza = 0
    for _ in range(n):
        esperanza += simulacion()
    return esperanza / n

valor_real = np.e 
print("Valor real (aproximado):", valor_real)
for n in [100, 1000, 10000, 100000, 1000000]:
    E_N = MonteCarloMin(n)
    print(f"Valor esperado de N con {n} iteraciones: {E_N}, con error: {abs(E_N - valor_real)}")    
