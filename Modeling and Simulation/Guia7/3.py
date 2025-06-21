import numpy as np
np.random.seed(42)
from scipy.stats import kstest


# Ejercicio 3: Calcular una aproximación del p−valor de la hipótesis: “Los siguientes 10 números son
# aleatorios”:
#   0.12, 0.18, 0.06, 0.33, 0.72, 0.83, 0.36, 0.27, 0.77, 0.74.

x = [0.12, 0.18, 0.06, 0.33, 0.72, 0.83, 0.36, 0.27, 0.77, 0.74]
x.sort()

# Si la hipótesis fuera cierta, entonces cada xi debería tener la misma probabilidad de ocurrir. Es decir,
# que queremos ver si los datos vienen de una distribución uniforme en el intervalo (0,1).

# Para calcular el p-valor, utilizaremos el Test de Kolmogorov-Smirnov:

# Asumimos los parámetros a y b de la distribución uniforme en base a la muestra, por lo que no es necesario
# estimarlos.

def calcular_estadistico():
    d_KS = 0
    uniformes = np.random.uniform(0,1,n)
    uniformes.sort()
    for j in range(n):
        u = uniformes[j]
        d_KS = max(d_KS, (j+1)/n - u, u - j/n)

    return d_KS

n = 10
d = 0
for j in range(n):
    yj = x[j]                           # La inversa de la acumulada de la uniforme en (0,1) es la identidad
    d = max(d, (j+1)/n - yj, yj - j/n)
p_valor = 0
Nsim = 100_000
for _ in range(Nsim):
    d_j = calcular_estadistico()
    if d_j >= d:
        p_valor += 1

p_valor /= Nsim
    
print(f"p-valor con Test de Kolmogorov-Smirnov para {Nsim} simulaciones: {p_valor}")

res = kstest(x, 'uniform')

print(f"p-valor con Test de Kolmogorov-Smirnov (utilizando scipy.stats): {res.pvalue}")