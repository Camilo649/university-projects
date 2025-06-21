import numpy as np
import warnings
warnings.filterwarnings("ignore", category=RuntimeWarning)
from random import random
from math import pi, sin, sqrt
from scipy.stats import norm


# Ejercicio 3: Calcule mediante un método de Monte Carlo las siguientes integrales:


# i) integral (π, 2π): sin(x)/x * dx

# Para poder aplicar Monte Carlo, transofrmamos la integral como sigue:
#   integral (π, 2π): sin(x)/x * dx = integral (0, 1): sin(π*(u + 1))/(u + 1) * du

def MonteCarlo1(N):
    muestras = []
    for _ in range(N):
        U = random() + 1
        muestras.append(sin(pi*U)/U)

    estimacion = np.mean(muestras)
    varianza = np.var(muestras, ddof=1)
    desviacion_estandar = np.std(muestras, ddof=1)
    CI95 = [estimacion - norm.ppf(0.975) * desviacion_estandar / sqrt(N), estimacion + norm.ppf(0.975) * desviacion_estandar / sqrt(N)]


    return estimacion, varianza, desviacion_estandar, CI95


# ii) integral (0, inf): 3/(3 + x^4) * dx

# Para poder aplicar Monte Carlo, transofrmamos la integral como sigue:
#   integral (0, inf): 3/(3 + x^4) * dx = integral (0, 1): 3/(3 + (1/u - 1)^4) * 1/u^2 * du

def MonteCarlo2(N):
    muestras = []
    for _ in range(N):
        U = random()
        muestras.append(3 / (3 + (1/U - 1)**4) * 1/U**2)

    estimacion = np.mean(muestras)
    varianza = np.var(muestras, ddof=1)
    desviacion_estandar = np.std(muestras, ddof=1)
    CI95 = [estimacion - norm.ppf(0.975) * desviacion_estandar / sqrt(N), estimacion + norm.ppf(0.975) * desviacion_estandar / sqrt(N)]


    return estimacion, varianza, desviacion_estandar, CI95


# ---------------------------------------------- COMPARACIÓN ----------------------------------------------

N = 1_000_000
valor_real1, valor_real2 = -0.433785, 1.4618
estimacion1, _, _, _ = MonteCarlo1(N)
estimacion2, _, _, _ = MonteCarlo2(N)

# print(f"Error absoluto para {N} iteraciones integral 1: {abs(estimacion1 - valor_real1):6.6f}")
# print(f"Error absoluto para {N} iteraciones integral 2: {abs(estimacion2 - valor_real2):6.6f}")

# ---------------------------------------------- COMPARACIÓN ----------------------------------------------


# a) Obtenga mediante simulación en computadora el valor de la integral deteniendo la simulación cuando
# el semi-ancho del intervalo de confianza del 95% sea justo inferior a 0,001.

d = 0.001

# Por lo visto en el teórico, la longitud del intervalo va a estar dado por:
#   2 * sqrt(Scuad/n) * z_alfa_2
# En nuestro caso, 0.95 = 1 - alfa <=> a = 0.05
# Entonces 1 - alfa/2 = 0.975 y por lo tanto:
z_alfa_2 = norm.ppf(0.975)
# Como queremos que el semi-ancho del intervalo (la mitad del intervalo) sea < d, vamos a detener la simulación
# cuando sqrt(Scuad/n) * z_alfa_2 < d <=> sqrt(Scuad/n) < d/z_alfa_2

def EstimarIntegral(d, f):
    """
    Devuelve la estimación del valor del área de la integral simulada con el método de Monte Carlo hasta que el
    semi-ancho del intervalo de confianza del 95% sea < d, su varianza y también, la mínima cantidad de iteraciones (>= 100
    para poder aplicar el TCL) que cumplen la condición. Aquí f debe devolver la media y la varianza para N 
    iteraciones.
    """
    N = 100
    Media, Scuad, _, _ = f(N)
    bound = d/z_alfa_2
    while sqrt(Scuad/N) >= bound:
        N += 1
        X, _, _, _ = f(1)
        MediaAnt = Media
        Media = MediaAnt + (X - MediaAnt) / N
        Scuad = Scuad * (1 - 1/(N-1)) + N * (Media - MediaAnt)**2 
    return Media, Scuad, N

# b) Indique cuál es el número de simulaciones Ns necesarias en la simulación realizada para lograr la con-
# dición pedida y complete con los valores obtenidos la siguiente tabla (usando 4 decimales):

print("============================ INTEGRAL i ============================")
print(f"{'Nº de sim.':^12} {'𝐼':^12} {'S':^8} {'IC (95%)':^21}")

for n in [1000, 5000, 7000]:
    estimacion, varianza, std, CI = MonteCarlo1(n)
    print(f"{n:^11} {estimacion:^11.4f} {std:^11.4f} [{CI[0]:.4f}, {CI[1]:.4f}]")

mediaNs, varianzaNs, Ns = EstimarIntegral(d, MonteCarlo1)
stdNs = sqrt(varianzaNs)
ICNs = [mediaNs - z_alfa_2 * stdNs / sqrt(Ns), mediaNs + z_alfa_2 * stdNs / sqrt(Ns)]

print(f"{Ns:^11} {mediaNs:^11.4f} {stdNs:^11.4f} [{ICNs[0]:.4f}, {ICNs[1]:.4f}]")

print("============================ INTEGRAL ii ============================")
print(f"{'Nº de sim.':^12} {'𝐼':^12} {'S':^8} {'IC (95%)':^21}")

for n in [1000, 5000, 7000]:
    estimacion, varianza, std, CI = MonteCarlo2(n)
    print(f"{n:^11} {estimacion:^11.4f} {std:^11.4f} [{CI[0]:.4f}, {CI[1]:.4f}]")

mediaNs, varianzaNs, Ns = EstimarIntegral(d, MonteCarlo2)
stdNs = sqrt(varianzaNs)
ICNs = [mediaNs - z_alfa_2 * stdNs / sqrt(Ns), mediaNs + z_alfa_2 * stdNs / sqrt(Ns)]

print(f"{Ns:^11} {mediaNs:^11.4f} {stdNs:^11.4f} [{ICNs[0]:.4f}, {ICNs[1]:.4f}]")


# Nota: A mayor varianza, mayor Ns.

