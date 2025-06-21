import numpy as np
import random
from math import exp, sqrt

random.seed(42)

# Ejercicio 2: Estime mediante el método de Monte Carlo la integral


# i) integral (0,1): e^x / sqrt(2x) * dx

def f_i(x):
    return exp(x)/sqrt(2*x)

def g_i(x):
    return f_i(x)

# ii) integral (-inf,inf): x^2 * e^(-x^2)

# Como es una función par (Geogebra me lo confirmó) transformamos la integral como sigue:
# integral (-inf,inf): x^2 * e^(-x^2) * dx = integral (0,inf): 2 * x^2 * e^(-x^2) * dx
# Entonces, para Monte Carlo, la integral nos queda: integral (0,1): 2 * (1/u -1)^2 * e^(-(1/u -1)^2) * dx

def f_ii(x):
    return x**2 * exp(-x**2)

def g_ii(x):
    return 2 * f_ii(1/x - 1) * (1/x)**2


# a) Genere al menos 100 valores y deténgase cuando la desviación estándar muestral S del estimador sea
# menor que 0,01.

def estimar(d, f):
    """
    Devuelve la mínima cantidad de valores generados con el método de Monte Carlo hasta que la desviación estándar
    sea < d y también la estimación alcanzada para esa cantidad de valores.
    """
    Media = f(random.random())
    Scuad, N = 0, 1
    while N <= 100 or sqrt(Scuad/N) > d:
        N += 1
        X = f(random.random())
        MediaAnt = Media
        Media = MediaAnt + (X - MediaAnt) / N
        Scuad = Scuad * (1 - 1/(N-1)) + N * (Media - MediaAnt)**2
    return N, Media

d = 0.01
valor_real1, valor_real2 = 2.0685, 0.886227
iteraciones1, estimacion1 = estimar(d, g_i)
iteraciones2, estimacion2 = estimar(d, g_ii)

print(f"========================================== INTEGRAL I) ==========================================")
print(f"Cantidad aproximada de iteraciones necesarias para que la desviación estándar muestral del estimador sea menor que {d}: {iteraciones1}")
print(f"Estimación para {iteraciones1} iteraciones: {estimacion1}")

print(f"========================================== INTEGRAL II) ==========================================")
print(f"Cantidad aproximada de iteraciones necesarias para que la desviación estándar muestral del estimador sea menor que {d}: {iteraciones2}")
print(f"Estimación para {iteraciones2} iteraciones: {estimacion2}")


# ---------------------------------------------- COMPARACIÓN ----------------------------------------------

x = [2,4,4,4,5,5,7,9]
media_np , var_np = np.mean(x), np.var(x, ddof=1)
media_rec, var_rec = x[0], 1

n = 1
for i in range (7):
    n += 1
    MediaAnt = media_rec
    media_rec = MediaAnt + (x[i+1] - MediaAnt) / n
    var_rec = var_rec * (1 - 1/(n-1)) + n * (media_rec - MediaAnt)**2

media_posta = 0
for i in range(n):
    media_posta += x[i]
media_posta /= n

var_posta = 0
for i in range(n):
    var_posta += (x[i] - media_posta)**2
var_posta *= 1/(n-1)

# print(f"Media numpy: {media_np}, Varianza numpy: {var_np}")
# print(f"Media recursiva: {media_rec}, Varianza recursiva: {var_rec}")
# print(f"Media post: {media_posta}, Varianza post: {var_posta}")
