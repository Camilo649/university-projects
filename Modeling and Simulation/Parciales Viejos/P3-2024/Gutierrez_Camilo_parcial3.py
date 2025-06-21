import numpy as np
from scipy.stats import norm, chi2
from math import factorial as fact, sqrt
from random import random


def ejercicio2():

    n = 9
    datos = [1.628, 1.352, 1.800, 1.420, 1.594, 2.132, 1.614, 1.924, 1.692]
    datos.sort()

    mu_sombrero = np.mean(datos)
    sigma_sombrero = np.std(datos, ddof=1)

    print(f"Estimación de mu: {mu_sombrero}")
    print(f"Estimación de sigma: {sigma_sombrero}")

    d = 0
    for j in range(n):
        y = norm.cdf(datos[j], mu_sombrero, sigma_sombrero)
        d = max(d, (j+1)/n - y, y - j/n)
    print(f"Estadístico KS: {d}")

    # Simulación

    p_valor = 0
    Nsim = 100_000

    def calcular_estadistico():
        d_KS = 0
        uniformes = np.random.uniform(0, 1, n)
        uniformes.sort()
        for j in range(n):
            u = uniformes[j]
            d_KS = max(d_KS, (j + 1) / n - u, u - j / n)
        return d_KS
    
    for _ in range(Nsim):
        if calcular_estadistico() > d:
            p_valor += 1

    p_valor /= Nsim


    print(f"p-valor simulado KS: {p_valor}")

    # Incisio e
    uniformes = [0.23, 0.12, 0.45, 0.67, 0.01, 0.51, 0.38, 0.92, 0.84]
    uniformes.sort()
    d_e = 0
    for j in range(n):
        u = uniformes[j]
        d_e = max(d_e, ((j+1)/n) - u, u - (j/n))
    print(f"Estadístico KS del inciso e: {d_e:.4f}")    


# ejercicio2()

def ejercicio3():

    n_bin = 3
    k = 4 # Cantidad de valores distintos
    n = 1_000
    p_sombrero = 0.217

    def Binomial(i, p):
        return (fact(n_bin) * p**i * (1-p)**(n_bin-i)) / (fact(i) * fact(n_bin-i))
    
    frec_esp = [n*Binomial(i, p_sombrero) for i in range (k)]
    frec_obs = [490, 384, 111, 15]
    t = 0
    for i in range(k):
        t += (frec_obs[i] - frec_esp[i])**2 / frec_esp[i]

    print(f"Estadístico Chi2: {t}")

    p_valor = 1 - chi2.cdf(t, k-1-1) # También restamos la cantidad de parámetros estimados

    print(f"p-valor Chi2: {p_valor}")

    # Simulación

    p_valor_sim = 0
    Nsim = 100_000

    probs = [Binomial(i, p_sombrero) for i in range (k)]

    def calcular_estadistico():
        f_o = np.random.multinomial(n, probs)
        p_estimado = sum(i*f_o[i] for i in range(k))
        p_estimado /= n*n_bin
        f_e = [n*Binomial(i, p_estimado) for i in range (k)]
        return sum((f_o[i] - f_e[i])**2 / f_e[i] for i in range(k))
    
    for _ in range(Nsim):
        if calcular_estadistico() >= t:
            p_valor_sim += 1
    
    p_valor_sim /= Nsim
    
    print(f"p-valor Chi2 simulado: {p_valor_sim}")

# ejercicio3()

def ejercicio4():

    # Para poder aplicar Monte Carlo, transofrmamos la integral como sigue:
    #   integral (0, inf): x/(1 + x^4) * dx = integral (0, 1): (1/u - 1) / (1 + (1/u - 1)^4) * 1/u^2 * du

    def f(x):
        return x/(1 + x**4)

    def g(x):
        return f(1/x - 1) * (1/x)**2
    
    d = 0.001

    # Por lo visto en el teórico, la longitud del intervalo va a estar dado por:
    #   2 * sqrt(Scuad/n) * z_alfa_2
    # En nuestro caso, 0.95 = 1 - alfa <=> a = 0.05
    # Entonces 1 - alfa/2 = 0.975 y por lo tanto:
    z_alfa_2 = norm.ppf(0.975)

    def EstimarIntegral(d):
        """
        Devuelve la estimación del valor del área de la integral simulada con el método de Monte Carlo hasta que
        el semi-ancho del intervalo de confianza del 95% sea < d, su varianza y también, la mínima cantidad de
        iteraciones (>= 100 para poder aplicar el TCL) que cumplen la condición.
        """
        Media = g(random())
        Scuad, n = 0, 1
        bound = d/z_alfa_2
        while n <= 100 or sqrt(Scuad/n) > bound:
            n += 1
            X = g(random())
            MediaAnt = Media
            Media = MediaAnt + (X - MediaAnt) / n
            Scuad = Scuad * (1 - 1/(n-1)) + n * (Media - MediaAnt)**2 
        return Media, Scuad, n
    

    print(f"{'Nº de sim.':^12} {'𝐼':^12} {'S':^8} {'IC (95%)':^21}")

    for Nsim in [1000, 5000, 7000]:
        
        valores = []
        for _ in range(Nsim):
            valores.append(g(random()))

        estimacion = np.mean(valores)
        desviacion_estandar = np.std(valores, ddof=1)
        offset = z_alfa_2 * desviacion_estandar / sqrt(Nsim)
        CI = [estimacion - offset, estimacion + offset]

        print(f"{Nsim:^11} {estimacion:^11.4f} {desviacion_estandar:^11.4f} [{CI[0]:.4f}, {CI[1]:.4f}]")
    
    mediaNs, varianzaNs, Ns = EstimarIntegral(d)
    stdNs = sqrt(varianzaNs)
    ICNs = [mediaNs - z_alfa_2 * stdNs / sqrt(Ns), mediaNs + z_alfa_2 * stdNs / sqrt(Ns)]
    
    print(f"{Ns:^11} {mediaNs:^11.4f} {stdNs:^11.4f} [{ICNs[0]:.4f}, {ICNs[1]:.4f}]")

ejercicio4()
    
