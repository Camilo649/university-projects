from random import random
import time

# Ejercicio 4. Implemente cuatro métodos para generar una variable X que toma los valores del 1 al 10,
# con probabilidades p1 = 0,11, p2 = 0,14, p3 = 0,09, p4 = 0,08, p5 = 0,12, p6 = 0,10, p7 = 0,09, p8 =
# 0,07, p9 = 0,11, p10 = 0,09 usando:

p = [0.11, 0.14, 0.09, 0.08, 0.12, 0.10, 0.09, 0.07, 0.11, 0.09] # Arreglo de probabilidades

# a) Método de rechazo con una uniforme discreta, buscando la cota c más baja posible.

# Tomamos Y como una variable uniforme discreta en el intervalo [1,10] la cual si sabemos generar.
# Luego P(X = xj), P(Y = xj) > 0 para todo xj en el intervalo [1,10].
# Ahora, como la probabilidad más grande es 0.14, con tomar c = 1.4 se cumple para todo xj en [1,10] que 
#   P(X = xj)/P(Y = yj) = (usando que Y ~ U{1,..,10}) (P(X = xj)/0.1) <= 1.4 
# De lo anterior, Y cumple las propiedades necesarias para poder estimar a X siguiendo el método de
# aceptacion y rechazo, y c es la cota más baja posible para Y
def AyR1():
    while True:
        Y = int(random()*10)
        U = random()
        if U < (p[Y])/0.14:
            return Y + 1

# b) Método de rechazo con una uniforme discreta, usando c = 3.

def AyR2():
    while True:
        Y = int(random()*10)
        U = random()
        if U < (p[Y])/0.3:
            return Y + 1

# c) Transformada inversa.

# Para disminuir el valor esperado de comparaciones, compararamos primero los valores de p más probales
def TI():
    U = random()
    if U < 0.14:   return 2
    elif U < 0.26: return 5
    elif U < 0.37: return 1
    elif U < 0.48: return 9
    elif U < 0.58: return 6
    elif U < 0.67: return 3
    elif U < 0.76: return 7
    elif U < 0.85: return 10
    elif U < 0.93: return 4
    else:          return 8

# d) Método de la urna: utilizar un arreglo A de tamaño 100 donde cada valor i está en exactamente pi ∗ 100
# posiciones. El método debe devolver A[k] con probabilidad 0,01. ¿Por qué funciona?

# Construimos primero el arreglo A
A = [0] * 100
for j in range(len(p)):
    for i in range(int(p[j]*100)):
        A[i] = j+1

def Urna():
    U = int(random()*100)             # Elijo un indice de A aleatoriamente
    return A[U]
# El anterior algoritmo funciona pues
#   P(X = j) = P(p1 + ... + pj-1 <= U < p1 + ... + pj) =  p1 + ... + pj - (p1 + ... + pj-1) = pj

# ----------------------------------------Version Mejorada-------------------------------------------------

# Para optimizar el uso de memoria, utilizaremos dos arreglos en lugar de 1 con 100 elementos: D que
# contendrá las décimas de los pi, y C que contendrá las centécimas de los pi.
D = [1,2,5,6,9]
C = [1,2,2,2,2,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,9,10,10,10,10,10,10,10,10,10]
# Notar que si bien C es un arreglo grande, len(D) + len(C) = 5 + 50 = 55 que sigue siendo mejor que un solo
# arreglo de 100 valores
def UrnaMejorada():
    U = random()
    if U < 0.5:                  # Las décimas acumulan el 50% de la probabilidad total
        I = int(random()*len(D))
        return D[I]
    else:
        I = int(random()*len(C))
        return C[I]   
# El anterior algoritmo funciona puesto que
#   P(X = 1) = P(U < 0.5)*P(I = 0) + P(U >= 0.5)*P(I = 0) = 0.5*0.2 + 0.5*0.02 = 0.11 = p1
# Y asi siguiendo, podríamos ver que la probabilidad de que X = xj es pj

# ----------------------------------------Version Mejorada-------------------------------------------------

# Compare la eficiencia de los cuatro algoritmos realizando 10000 simulaciones.

nsim = 10000

inicio1 = time.perf_counter()
for _ in range(nsim): AyR1()
fin1 = time.perf_counter()

inicio2 = time.perf_counter()
for _ in range(nsim): AyR2()
fin2 = time.perf_counter()

inicio3 = time.perf_counter()
for _ in range(nsim): TI()
fin3 = time.perf_counter()

inicio4 = time.perf_counter()
for _ in range(nsim): Urna()
fin4 = time.perf_counter()

inicio5 = time.perf_counter()
for _ in range(nsim): UrnaMejorada()
fin5 = time.perf_counter()

print(f"Método    | Tiempo Transcurrido")
print(f"-------------------------------")
print(f"AyR c=1.4 | {fin1-inicio1:.6f}")
print(f"AyR c=3   | {fin2-inicio2:.6f}")
print(f"TI        | {fin3-inicio3:.6f}")
print(f"Urna      | {fin4-inicio4:.6f}")
print(f"Urna++    | {fin5-inicio5:.6f}")

# NOTA: Si bien ambos algoritmos de aceptación y rechazo tienen un valor esperado de comparaciones menor
# al algoritmo de la transformada inversa, estos son más lentos debido a la penalización de los múltiples
# accesos al arreglo p