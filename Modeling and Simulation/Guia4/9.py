from random import random
from time import perf_counter as pf

# Ejercicio 9. Implemente dos métodos para simular una variable geométrica Geom(p):
# a) Usando transformada inversa y aplicando la fórmula recursiva para P(X = i).

# Sea X es una variable aleatoria con distribución geométrica de parámetro p e i un valor >= 1:
# ◆ P(X = 0) = p
# ◆ P(X = i) = p*(1-p)^(i-1)
# ◆ P(X = i+1) = (1-p)*P(X = i)
# Con esta recursión en mente, damos el siguiente algoritmo
def TI(p):
    prob = p
    q = 1-p
    U = random()
    F = prob
    i = 0
    while U >= F:
        i += 1
        prob *= q
        F += prob
    return i + 1

# b) Simulando ensayos con probabilidad de éxito p hasta obtener un éxito.

# Para simular cada ensayo independiente, simularemos una variable aleatoria con distribucion Bernoulli
# de parámetro p
def Bernoulli(p):
    U = random()
    if U < p: return 1
    else:     return 0

def Geometrica(p):
    fracasos = 0
    while Bernoulli(p) == 0:
        fracasos += 1
    return fracasos + 1

# Compare la eficiencia de estos algoritmos para p = 0,8 y para p = 0,2.
# Para cada caso, realice 10000 simulaciones y calcule el promedio de los valores obtenidos. Comparar estos
# valores con el valor esperado de la distribución correspondiente. Si están alejados, revisar el código.

def Eficiencia(f,p,nsim):
    inicio = pf()
    for _ in range(nsim): f(p)
    fin = pf()
    return fin-inicio

def EsperanzaGeometrica(f,p,nsim):
    ensayos = 0
    for _ in range(nsim):
        ensayos += f(p)
    return ensayos/nsim

E21, E22 = EsperanzaGeometrica(TI,0.8,10000), EsperanzaGeometrica(Geometrica,0.8,10000)
E11, E12 = EsperanzaGeometrica(TI,0.2,10000), EsperanzaGeometrica(Geometrica,0.2,10000)

print(f"                                       | TI con Recursión | Ensayos Independientes")
print(f"----------------------------------------------------------------------------------")
print(f"Tiempo Transcurrido p = 0,8            | {Eficiencia(TI,0.8,10000):.6f}         | {Eficiencia(Geometrica,0.8,10000):.6f}")
print(f"Tiempo Transcurrido p = 0,2            | {Eficiencia(TI,0.2,10000):.6f}         | {Eficiencia(Geometrica,0.2,10000):.6f}")
print(f"Esperanza p = 0,8                      | {E21:.6f}         | {E22:.6f}")
print(f"Esperanza p = 0,2                      | {E11:.6f}         | {E12:.6f}")
print(f"Error Absoluto de la Esperanza p = 0.8 | {abs(E21 - 1/0.8):.6f}         | {abs(E22 - 1/0.8):.6f}")  
print(f"Error Absoluto de la Esperanza p = 0.2 | {abs(E11 - 1/0.2):.6f}         | {abs(E12 - 1/0.2):.6f}")  

# NOTA: En términos generales, tiende a ser más veloz el algoritmo con recursión. Pero esto se debe a la llamada
# a la función Bernoulli que realiza el algoritmo con ensayos independientes. Si la uniforme se generase dentro
# de la función Geometrica, las tendencias se verían invertidas