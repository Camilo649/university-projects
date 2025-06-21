from random import random, seed
seed(42)
from scipy.stats import kstest
from math import exp, log


# Ejercicio 9: En un estudio de vibraciones, una muestra aleatoria de 15 componentes del avión fueron
# sometidos a fuertes vibraciones hasta que se evidenciaron fallas estructurales. Los datos proporcionados
# son los minutos transcurridos hasta que se evidenciaron dichas fallas.
#     1.6, 10.3, 3.5, 13.5, 18.4, 7.7, 24.3, 10.7, 8.4, 4.9, 7.9, 12, 16.2, 6.8, 14.7
# Pruebe la hipótesis nula de que estas observaciones pueden ser consideradas como una muestra de la
# distribución exponencial.

n = 15
x = [1.6, 10.3, 3.5, 13.5, 18.4, 7.7, 24.3, 10.7, 8.4, 4.9, 7.9, 12, 16.2, 6.8, 14.7]
x.sort()

# Como la esperanza de una variable aleatoria con distribución Exponencial es el parámetro 1/lambda, podemos
# estimar lambda con la inversa de la media muestral:

lambda_sombrero = n/sum(x)

def F_exponencial(x, l):
    return 1 - exp(-x*l)

def generar_muestra():
    muestra = []
    for _ in range(n):
        muestra.append(-log(1-random()) / lambda_sombrero) # Las muestras siempre son en base al lambda_sombrero
    
    return muestra

def calcular_estadistico():
    d_KS = 0
    muestra = generar_muestra()
    muestra.sort()
    theta = n/sum(muestra)
    for j in range(n):
        y = F_exponencial(muestra[j], theta)
        d_KS = max(d_KS, (j+1)/n - y, y - j/n)

    return d_KS

d = 0
for j in range(n):
    y = F_exponencial(x[j], lambda_sombrero)
    d = max(d, (j+1)/n - y, y - j/n)
p_valor = 0
Nsim = 100_000
for _ in range(Nsim):
    d_j = calcular_estadistico()
    if d_j >= d:
        p_valor += 1

p_valor /= Nsim
    
print(d)

print(f"p-valor con Test de Kolmogorov-Smirnov para {Nsim} simulaciones: {p_valor}")

res = kstest(x, 'expon', args=(0, 1/lambda_sombrero))

print(f"p-valor con Test de Kolmogorov-Smirnov (utilizando scipy.stats): {res.pvalue}")

# Nota: kstest da un p-valor más alto ya que asume que lambda_sombrero es el parámetro y no una estimación.