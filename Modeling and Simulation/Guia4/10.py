from random import random
import numpy as np

# Ejercicio 10.
# (a) Desarrolle un método para generar una variable aleatoria X cuya distribución de probabilidad está
# dada por:
# P(X = j) = (1/2)^(j+1) + ((1/2)*2^(j-1))/3^j para j = 1,2,3...

# No podemos utilizar ni el método del alias o el de la urna puesto que X toma infinitos valores.
# Tampoco pareciera que pudieramos ver la probabilidad de masa de X como requiere el método de composición.
# Y como, no encontramos (al menos a simple vista) otra variable aleatoria discreta que sepamos generar
# que cumpla que si P(X = k) > 0, entonces P(Y = k) > 0 para todo k en los naturales (lo más cerca que
# se llegó fue probar con una geométrica de parámetro p=5/12 💀), optamos por simular a X mediante el
# método de la Transformada Inversa
def TI():
    U = random()
    j = 1
    F = 5/12
    while True:
        if U < F: return j
        j += 1
        F += (1/2)**(j+1) + ((1/2)*2**(j-1)) / 3**j

# (b) Estime E(X) con 1000 repeticiones y compare con la esperanza exacta.

def Esperanza(N):
    resultados = np.empty(N)
    for i in range(N):
        resultados[i] = TI()
    return np.mean(resultados)

valor_exacto = 2.5 # Según Wolframalpha
E = Esperanza(1000)

print(f"Estimación de la esperanza: {E:.6f}")
print(f"Esperanza exacta: {valor_exacto:.6f}")
print(f"Error relativo: {abs(valor_exacto-E)*100:.6f}%")
