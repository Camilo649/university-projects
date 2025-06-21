from random import random, seed
seed(42)
from scipy.stats import chi2


# Ejercicio 6: Un escribano debe validar un juego en cierto programa de televisión. El mismo consiste
# en hacer girar una rueda y obtener un premio según el sector de la rueda que coincida con una aguja.
# Hay 10 premios posibles, y las áreas de la rueda para los distintos premios, numerados del 1 al 10, son
# respectivamente:
#   31 %, 22 %, 12 %, 10 %, 8 %, 6 %, 4 %, 4 %, 2 %, 1 %.
# Los premios con número alto (e.j. un auto 0Km) son mejores que los premios con número bajo (e.j. 2x1
# para entradas en el cine). El escribano hace girar la rueda hasta que se cansa, y anota cuántas veces sale
# cada sector. Los resultados, para los premios del 1 al 10, respectivamente, son:
#   188, 138, 87, 65, 48, 32, 30, 34, 13, 2.


# a) Construya una tabla con los datos disponibles


k = 10
frec_obs = [188, 138, 87, 65, 48, 32, 30, 34, 13, 2]
n = sum(frec_obs)
p = [0.31, 0.22, 0.12, 0.1, 0.08, 0.06, 0.04, 0.04, 0.02, 0.01]
frec_esp = [n*p[i] for i in range (k)]


# b) Diseñe una prueba de hipótesis para determinar si la rueda es justa


# *insertar blabla*


# c) Defina el p-valor a partir de la hipótesis nula


# *insertar blabla*


# d) Calcule el p-valor bajo la hipótesis de que la rueda es justa, usando la aproximación chi cuadrado


t = 0
for i in range(k):
    t += (frec_obs[i] - frec_esp[i])**2 / frec_esp[i]
p_valor_chiCuad = 1 - chi2.cdf(t, k-1)

print(f"p-valor con Test chi-cuadrado de Pearson: {p_valor_chiCuad}")


# e) Calcule el p-valor bajo la hipótesis de que la rueda es justa, usando una simulación.


def BinomialMejorada(n, p):
    c = p / (1 - p)
    prob = (1 - p)**n
    F = prob
    for i in range(1, int((n + 1) * p) + 1):
        prob *= (c * (n - i + 1)) / i
        F += prob
    U = random()
    if U >= F:
        j = int((n + 1) * p) + 1
        while U >= F:
            prob *= (c * (n - j + 1)) / j
            F += prob
            j += 1
        return j - 1
    else:
        j = int((n + 1) * p)
        while U < F:
            F -= prob
            prob *= j / (c * (n - j + 1))
            j -= 1
        return j + 1

def generar_muestra():
    f_o = [0] * k
    probs = p.copy()
    N_restante = n
    p_acum = 0
    for i in range(k - 1):
        pi = probs[i] / (1 - p_acum)
        N = BinomialMejorada(N_restante, pi)
        f_o[i] = N
        N_restante -= N
        p_acum += probs[i]
    f_o[k - 1] = N_restante
    return f_o

def calcular_estadistico():
    f_o = generar_muestra()
    return sum((f_o[i] - frec_esp[i])**2 / frec_esp[i] for i in range(k))

def calcular_pvalor(nsim):
    count = 0
    for _ in range(nsim):
        if calcular_estadistico() >= t:
            count += 1
    return count / nsim

nsim = 100_000

print(f"Estimación del p-valor para {nsim} simulaciones: {calcular_pvalor(nsim)}")