from random import random


# Ejercicio 7: Sean X1, ... , Xn variables aleatorias i.i.d., con media desconocida μ. Para constantes a < b, se
# quiere estimar p = P(a < (∑ (i=1,n): Xi/n − μ) < b). Estimar p if n = 10 y los valores de Xi son 56, 101, 78, 67,
# 93, 87, 64, 72, 80 y 69. Tomar a = −5, b = 5.

n = 10
x = [56, 101, 78, 67,93, 87, 64, 72, 80, 69]
a = -5
b = 5

# Como desconocemos las distribución de las variables, utilizaremos la distribución empírica

media = 0 
for i in range(n):
    media += x[i]
media /= n          # Estimamos mu con la media muestral

muestras_bootstrap_usadas = set()

def calcularEstimador(n, x):
    estimador = 0
    for i in range(n):
        estimador += x[i]/n

    return estimador - media

# OJO! No hace falta que las muestras sean distintas
def generarMuestraBootstrap(n, x):
    muestra = []
    for _ in range(n):
        I = int(n*random())
        muestra.append(x[I])
    
    key = tuple(sorted(muestra))
    if key not in muestras_bootstrap_usadas:
        muestras_bootstrap_usadas.add(key)
        return muestra

    return generarMuestraBootstrap(n, x)

def simularProp(n, x, a, b):
    count = 0
    M = 1000                    # Acotamos con un valor más chico porque n^n es ENORME
    for _ in range(M):
        ThetaSombrero = calcularEstimador(n, generarMuestraBootstrap(n, x))
        if a < ThetaSombrero < b:
            count += 1
        
    return count/M

print(f"Estimación Bootstrap de P(-5 < (∑ (i=1,10): Xi/n − μ) < 5) con M = 10^3: {simularProp(n, x, a, b)}")
