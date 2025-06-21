from random import random
from math import exp, factorial as fact
import numpy as np

# Ejercicio 8.
# a) Desarrolle el método de la Transformada Inversa y el de Rechazo para generar una variable aleatoria
# X cuya distribución de probabilidad está dada por:
#   P(X = i) = ((λ^i/i!) * e^−λ) / (∑(j = 0,k) (λ^j/j!) * e^−λ) para (i = 0, . . . , k)

def calcularQ(k,λ):
    """
    Calcula las primeras k probabilidades de una varaible aleatoria con distribución de Poisson con parámetro λ
    """
    q = [0] * (k+1)
    q[0] = exp(-λ)
    for i in range(1, k+1):
        q[i] = q[i-1]*(λ/(i))
    return q

def calcularP(k,λ):
    """
    Calcula las probabilidades de X para λ y k concretos
    """
    s = 0
    for j in range(k+1):
        s +=  (λ**j/fact(j)) * exp(-λ)
    p = calcularQ(k,λ)
    for i in range(k+1): p[i] /= s
    return p

def TI(k,λ):
    p = calcularP(k,λ)
    pord = sorted(p, reverse=True)
    U = random()
    F = 0
    for i in range(k+1):
        F += pord[i]
        if U < F: return p.index(pord[i])

# Debido a la forma de la distribución de probabilidad de X, es claro que una variable aleatoria Y con
# distribución de Poisson que toma como parámetro el mismo λ que el de X, cumple que P(Y = x) > 0 si
# P(X = x) > 0, para todo x en el rango de X. Debido a este, tomaremos tal Y para el método de
# aceptacion y rechazo

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

def AyR(k,λ):
    # Calculamos primero la MÍNIMA c para poder ser utilizada en el método de aceptación y rechazo
    p = calcularP(k,λ)
    q = calcularQ(k,λ)
    c = max(p[i]/q[i] for i in range(k+1))
    while True:
        Y = PoissonMejorada(λ)
        if Y <= k:
            U = random()
            if U < p[Y]/(c*q[Y]):
                return Y

# b) Estime P(X > 2) con k = 10 y λ = 0,7, y 1000 repeticiones. Compare con el valor exacto.

def Simulacion(f,nsim):
    """
    Estima la probabilidad de que la variable aleatoria X con parámetros k = 10 y λ = 0,7
    sea mayor estricto que 2 con nsim simulaciones. La funcion f debe simular la variable
    """
    contador = 0
    for _ in range(nsim):
        if f(10,0.7) > 2:
            contador += 1
    
    return contador/nsim

p = calcularP(10,0.7)
valor_real = 1 - (p[0] + p[1] + p[2])

print(f"Transformada Inversa  | Aceptación y Rechazo | Valor Real")
print(f"---------------------------------------------------------")
print(f"{Simulacion(TI,1000):.6f}              | {Simulacion(AyR,1000):.6f}             | {valor_real:.6f}")  

# c) Generalice el problema escribiendo un pseudocódigo para el método de rechazo para cualquier va-
# riable aleatoria truncada usando como soporte a la variable original (con “cualquier variable aleatoria
# truncada” nos referimos a una variable como la vista en el inciso (a) pero ahora truncada en cualquier
# parte i = a, ..., b).

# Sea X la variable truncada y Y la de soporte
# Paso 1: Calculamos los valores de X y Y en el intervalo [a,b] y los guardamos en los arreglo p y q
# respectivamente
# Paso 2: Obtenemos la MÍNIMA constante c que cumple P(X = x)/P(Y = x) <= c para todo x tal que P(Y = x)
# > 0 y x esta en el rango de X. Para ello, nos quedamos con el más grande p[i]/q[i] con i entre [0,b-a+1]
# Paso 3: Simulamos Y
# Paso 4: Si Y no pertenece al intervalo [a,b], volvemos al paso 3
# Paso 5: Simulamos una variable aleatoria U con distribución uniforme en el intervalo (0,1)
# Paso 6: Si U < p[Y]/(c*q[Y]), detenerse y devolver Y. En caso contrario, volver al paso 3 
