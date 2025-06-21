from random import random
import numpy as np

# Ejercicio 3. Se lanzan simultáneamente un par de dados legales y se anota el resultado de la suma de ambos.
# El proceso se repite hasta que todos los resultados posibles: 2, 3, . . . , 12 hayan aparecido al menos una vez.
# Estudiar mediante una simulación la variable N, el número de lanzamientos necesarios para cumplir el
# proceso. Cada lanzamiento implica arrojar el par de dados.


# a) Describa la estructura lógica del algoritmo que permite simular en computadora el número de lanza-
# mientos necesarios para cumplir el proceso.

# Paso 1: Declarar un contador en 0 que represente el numero de lanzamientos
# Paso 2: Generar dos valores de variables aleatorias uniformes en el intervalo (1,6)
# Paso 3: Si la suma de los valores no habia aparecido antes, la guardamos
# Paso 4: Aumentar contador en 1
# Paso 5: Terminar si han aparecido todos los resultados y devolver el valor del contador. En caso contrario, volver al paso 2

# b) Mediante una implementación en computadora:

# (i) estime el valor medio y la desviación estándar del número de lanzamientos, repitiendo el algo-
# ritmo: 100, 1000, 10000 y 100000 veces.

def Simulacion():
    contador = 0
    lanzamientos = set()
    while lanzamientos != set(range(2, 13)):
        D1,D2 = int(random()*6) + 1, int(random()*6) + 1
        lanzamiento = D1 + D2
        if lanzamiento not in lanzamientos:
            lanzamientos.add(lanzamiento)
        contador += 1

    return contador

def EsperanzaYDesviacionEstandar(N):
    resultados = np.empty(N)
    for i in range(N):
        resultados[i] = Simulacion()
    return np.mean(resultados), np.std(resultados)

for n in [100, 1000, 10000, 100000]:
    E,V = EsperanzaYDesviacionEstandar(n)
    print(f"{n:>7} iteraciones | Esperanza ≈ {E:.6f} | Desviación Estándar ≈ {V:.6f}")

# (ii) estime la probabilidad de que N sea por lo menos 15 y la probabilidad de que N sea a lo sumo
# 9, repitiendo el algoritmo: 100, 1000, 10000 y 100000.

def AlMenos15(N):
    contador = 0
    for _ in range(N):
        if Simulacion() >= 15:
            contador += 1
    
    return contador/N

def ALoSumo9(N):
    contador = 0
    for _ in range(N):
        if Simulacion() <= 9:
            contador += 1
    
    return contador/N

for n in [100, 1000, 10000, 100000]:
    print(f"{n:>7} iteraciones | P(N >= 15) ≈ {AlMenos15(n):.6f} | P(N <= 9) ≈ {ALoSumo9(n):.6f}")
