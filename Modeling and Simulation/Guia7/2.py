import random
random.seed(42)
from scipy.stats import chi2
from time import perf_counter as pc


# Ejercicio 2: Para verificar que cierto dado no estaba trucado, se registraron 1000 lanzamientos, resultando
# que el número de veces que el dado arrojó el valor i (i = 1, 2, 3, 4, 5, 6) fue, respectivamente, 158, 172, 164,
# 181, 160, 165. Aproximar el p−valor de la prueba: “el dado es honesto”

n = 1000
p = [1/6, 1/6, 1/6, 1/6, 1/6, 1/6]
k = 6


# a) utilizando la prueba de Pearson con aproximación chi-cuadrada,


frec_obs = [158, 172, 164, 181, 160, 165]
frec_esp = [1000/6, 1000/6, 1000/6, 1000/6, 1000/6, 1000/6]
t = 0
for i in range(k):
    t += (frec_obs[i] - frec_esp[i])**2 / frec_esp[i]
p_valor_Pearson = 1 - chi2.cdf(t, k-1)

print(f"p-valor con Test chi-cuadrado de Pearson: {p_valor_Pearson}")


# b) realizando una simulación.


# -------------------------
# Simulación 1: muestreo directo
# -------------------------
def generar_muestra():
    muestra = []
    for _ in range(n):
        U = random.random()
        i = 0
        prob = p[0]
        while i < len(p):
            if U <= prob:
                muestra.append(i)
                break
            i += 1
            prob += p[i]
    return muestra

def calcular_estadistico(muestra):
    f_o = [muestra.count(i) for i in range(k)]
    return sum((f_o[i] - frec_esp[i])**2 / frec_esp[i] for i in range(k))

def calcular_pvalor(nsim):
    count = 0
    for _ in range(nsim):
        muestra = generar_muestra()
        if calcular_estadistico(muestra) >= t:
            count += 1
    return count / nsim

# -------------------------
# Simulación 2: binomial mejorada
# -------------------------
def BinomialMejorada(n, p):
    c = p / (1 - p)
    prob = (1 - p)**n
    F = prob
    for i in range(1, int((n + 1) * p) + 1):
        prob *= (c * (n - i + 1)) / i
        F += prob
    U = random.random()
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

def generar_muestra2():
    f_o = [0] * k
    N_restante = n
    p_acum = 0
    for i in range(k - 1):
        pi = p[i] / (1 - p_acum)
        N = BinomialMejorada(N_restante, pi)
        f_o[i] = N
        N_restante -= N
        p_acum += p[i]
    f_o[k - 1] = N_restante
    return f_o

def calcular_estadistico2():
    f_o = generar_muestra2()
    return sum((f_o[i] - frec_esp[i])**2 / frec_esp[i] for i in range(k))

def calcular_pvalor2(nsim):
    count = 0
    for _ in range(nsim):
        if calcular_estadistico2() >= t:
            count += 1
    return count / nsim

# -------------------------
# Comparación
# -------------------------
nsim = 100_000

start1 = pc()
pval1 = calcular_pvalor(nsim)
time1 = pc() - start1

start2 = pc()
pval2 = calcular_pvalor2(nsim)
time2 = pc() - start2

print(f"\nSimulación 1 (muestreo directo):")
print(f"  p-valor estimado = {pval1:.4f}")
print(f"  Tiempo = {time1:.2f} segundos")

print(f"\nSimulación 2 (binomial mejorada):")
print(f"  p-valor estimado = {pval2:.4f}")
print(f"  Tiempo = {time2:.2f} segundos")