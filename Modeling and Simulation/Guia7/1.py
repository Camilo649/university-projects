import random
random.seed(42)
from scipy.stats import chi2


# Ejercicio 1: De acuerdo con la teoría genética de Mendel, cierta planta de guisantes debe producir flores
# blancas, rosas o rojas con probabilidad 1/4, 1/2 y 1/4, respectivamente. Para verificar experimentalmente
# la teoría, se estudió una muestra de 564 guisantes, donde se encontró que 141 produjeron flores blancas,
# 291 flores rosas y 132 flores rojas. Aproximar el p-valor de esta muestra:


# a) utilizando la prueba de Pearson con aproximación chi-cuadrada.


# En la carpeta llegamos a que el valor del estadístico es
t = 3888/4559
p_valor = 1 - chi2.cdf(t, 3-1)

print(f"p-valor con Test chi-cuadrado de Pearson: {p_valor}")


# b) realizando una simulación.


# 1) Se generan N muestras de tamaño 564 que cumplen H0

n = 564
p = [0.25, 0.5, 0.25]

def generar_muestra():
    muestra = []
    for _ in range(n):
        prob = p[0]
        i = 0
        U = random.random()
        while i <= len(p):
            if U <= prob: 
                muestra.append(i)
                break
            i += 1
            prob += p[i]

    return muestra

frec_esp = [141, 282, 141]
k = 3

def calcular_estadistico(muestra):
    T = 0
    frec_obs = [0] * k
    for i in range (k):
        frec_obs[i] = muestra.count(i)
        T += (frec_obs[i] - frec_esp[i])**2 / frec_esp[i]

    return T
    
def calcular_pvalor(nsim):
    count = 0
    for _ in range(nsim):
        muestra = generar_muestra()
        if calcular_estadistico(muestra) >= t:
            count += 1
    
    return count/nsim

nsim = 100_000

print(f"Estimación del p-valor para {nsim} simulaciones: {calcular_pvalor(nsim)}")

    