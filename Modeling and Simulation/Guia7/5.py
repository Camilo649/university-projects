import numpy as np
np.random.seed(42)
from math import factorial as fact
from scipy.stats import chi2


# Ejercicio 5: Calcular una aproximación del p−valor de la prueba de que los siguientes datos corresponden
# a una distribución binomial con parámetros (n = 8, p), donde p no se conoce:
#   6, 7, 3, 4, 7, 3, 7, 2, 6, 3, 7, 8, 2, 1, 3, 5, 8, 7.


n = 8
x = [6, 7, 3, 4, 7, 3, 7, 2, 6, 3, 7, 8, 2, 1, 3, 5, 8, 7]
N = len(x)
k = 9

# Como la esperanza de una variable aleatoria con distribución Binomial es n*p, podemos estimar a p con la media
# muestral sobre n:

p_sombrero = np.mean(x)/n

# Ahora podemos calcular el estimador t con la distribución estimada Binomial_sombrero

def Binomial_sombrero(i):
    return (fact(n) * p_sombrero**i * (1-p_sombrero)**(n-i)) / (fact(i) * fact(n-i))

frec_esp = [N*Binomial_sombrero(i) for i in range (k)]
frec_obs = [x.count(i) for i in range(k)]
t = 0
for i in range(k):
    t += (frec_obs[i] - frec_esp[i])**2 / frec_esp[i]

p_valor = 1 - chi2.cdf(t, k-1-1) # También restamos la cantidad de parámetros estimados

print(f"p-valor con Test chi-cuadrado de Pearson: {p_valor}")