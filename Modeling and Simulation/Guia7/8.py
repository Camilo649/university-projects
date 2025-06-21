import numpy as np
np.random.seed(42)
from math import sqrt, erf
from random import gauss, gammavariate, seed
seed(42)
from scipy.stats import kstest

df = 11

def p_valor_SK(n, Nsim):
    p_valor = 0

    def F(x):
        return erf(x / sqrt(2.0)) / 2.0 + 0.5

    def generar_muestra():
        muestra = []
        for _ in range(n):
            x = gauss(0.0, 1.0)
            y = 2.0 * gammavariate(0.5 * df, 2.0)
            muestra.append(x / (sqrt(y / df)))
        return muestra

    def calcular_estadistico():
        d_KS = 0
        uniformes = np.random.uniform(0, 1, n)
        uniformes.sort()
        for j in range(n):
            u = uniformes[j]
            d_KS = max(d_KS, (j + 1) / n - u, u - j / n)
        return d_KS

    x = generar_muestra()
    x.sort()
    d = 0
    for j in range(n):
        zj = F(x[j])
        d = max(d, (j + 1) / n - zj, zj - j / n)

    for _ in range(Nsim):
        d_j = calcular_estadistico()
        if d_j >= d:
            p_valor += 1

    return d, p_valor / Nsim, x


Nsim = 100_000
tams = [10, 20, 100, 1000]

print(f"Número de simulaciones por tamaño de muestra: {Nsim}")
print()
print(f"{'N':>6} | {'D':>10} | {'simulado':>10} | {'scipy':>10}")
print("-" * 48)

for tam in tams:
    d, pval_sim, muestra = p_valor_SK(tam, Nsim)
    res = kstest(muestra, 'norm', args=(0, 1))
    print(f"{tam:6d} | {d:10.4f} | {pval_sim:10.4f} | {res.pvalue:10.4f}")

# Nota: En este ejercicio se evidencia como no podemos tomar buenas decisiones sobre muestras pequeñas.
