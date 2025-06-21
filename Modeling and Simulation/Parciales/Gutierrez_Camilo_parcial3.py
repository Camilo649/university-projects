import numpy as np
from math import exp, log, factorial as fact, sqrt
from random import random, seed
from scipy.stats import chi2, norm
# Fijamos semillas para poder replicar los resultados
np.random.seed(42)
seed(42)


def ejercicio2():
    print("================================= Ejercicio 2 =================================")

    datos = [
                15.22860536, 40.60145536, 33.67482894, 44.03841737, 15.69560109, 16.2321714, 25.02174735, 
                30.34655637, 3.3181228, 5.69447539, 10.1119561, 49.10266584, 3.6536329, 35.82047148, 3.37816632,
                36.72299321, 50.67085322, 3.25476304, 20.12426236, 20.2668814, 17.49593589, 2.70768636,
                14.77332745, 1.72267967, 23.34685662, 8.46376635, 9.18330789, 9.97428217, 2.33951729,
                137.51657441, 9.79485269, 10.40308179, 1.57849658, 6.26959703, 4.74251574, 1.53479053,
                34.74136011, 27.47600572, 9.1075566, 1.88056595, 27.59551348, 6.82283137, 12.45162807,
                28.01983651, 0.36890593, 7.82520791, 3.17626161, 46.91791271, 38.08371186, 41.10961135
            ]
    n = len(datos)
    datos.sort()
    lamda = 0.05

    d = 0
    for j in range(n):
        F_y = 1 - exp(-lamda*datos[j]) # Acumulada de la exponencial(0.05)
        d = max(d, (j+1)/n - F_y, F_y - j/n)
    print(f"Estadístico KS: {d}")

    # Simulaciones

    p_valor_unif = 0
    Nsim = 100_000

    def calcular_estadistico_uniformes():
        d_KS = 0
        uniformes = np.random.uniform(0, 1, n)
        uniformes.sort()
        for j in range(n):
            u = uniformes[j]
            d_KS = max(d_KS, (j + 1) / n - u, u - j / n)
        return d_KS
    
    for _ in range(Nsim):
        if calcular_estadistico_uniformes() > d:
            p_valor_unif += 1

    p_valor_unif /= Nsim

    print(f"p-valor KS simulado con uniformes: {p_valor_unif}")


    p_valor_exp = 0

    def calcular_estadistico_exponenciales():
        d_KS = 0
        exponenciales = []
        for _ in range(n):
            exponenciales.append(-log(1 - random())/lamda)  # Generamos datos de una exponencial(0.05)
        exponenciales.sort()
        for j in range(n):
            F_y = 1 - exp(-lamda*exponenciales[j]) # Acumulada de la exponencial(0.05)
            d_KS = max(d_KS, (j + 1) / n - F_y, F_y - j / n)
        return d_KS
    
    for _ in range(Nsim):
        if calcular_estadistico_exponenciales() > d:
            p_valor_exp += 1

    p_valor_exp /= Nsim

    print(f"p-valor KS simulado con exponenciales: {p_valor_exp}")

ejercicio2()


def ejercicio3():
    print("================================= Ejercicio 3 =================================")

    n_bin = 5
    k = 6 # Cantidad de valores distintos (len[0,1,2,3,4,5])
    n = 1_000
    p_sombrero = 0.494
    m = 1 # Cantidad de parámetros estimados (en nuestro caso, solo estimamos p)

    def Prob_Binomial(i, p):
        """
        Devuelve P(X = i), donde X es una variable aleatoria de distribución Binomial de parámetros (5, p)
        """
        if i < k:
            return (fact(n_bin) * p**i * (1-p)**(n_bin-i)) / (fact(i) * fact(n_bin-i))
        return 0
    
    frec_esp = [n*Prob_Binomial(i, p_sombrero) for i in range (k)]
    frec_obs = [38, 144, 342, 287, 164, 25]
    t = 0
    for i in range(k):
        t += (frec_obs[i] - frec_esp[i])**2 / frec_esp[i]

    print(f"Estadístico Chi2: {t}")

    p_valor = 1 - chi2.cdf(t, k-1-m)

    print(f"p-valor Chi2: {p_valor}")

    # Simulación

    p_valor_sim = 0
    Nsim = 1_000

    probs_sombrero = [Prob_Binomial(i, p_sombrero) for i in range (k)]

    def calcular_estadistico():
        f_o = np.random.multinomial(n, probs_sombrero)
        p_estimado = sum(i*f_o[i] for i in range(k))
        p_estimado /= n*n_bin
        f_e = [n*Prob_Binomial(i, p_estimado) for i in range (k)]
        return sum((f_o[i] - f_e[i])**2 / f_e[i] for i in range(k))
    
    for _ in range(Nsim):
        if calcular_estadistico() >= t:
            p_valor_sim += 1
    
    p_valor_sim /= Nsim
    
    print(f"p-valor Chi2 simulado: {p_valor_sim}")

ejercicio3()


def ejercicio4():
    print("================================= Ejercicio 4 =================================")

    # Para poder aplicar Monte Carlo, transofrmamos la integral como sigue:
    #   integral (2, 3): e^-x * (1 - x^4) * dx = integral (0, 1): e^-(u + 2) * (1 - (u + 2)^4) du

    def f(x):
        return exp(-x) * (1 - x**4)

    def g(x):
        return f(x + 2)
    
    d = 0.001

    # Por lo visto en el teórico, la longitud del intervalo va a estar dado por:
    #   2 * sqrt(Scuad/n) * z_alfa_2
    # En nuestro caso, 0.95 = 1 - alfa <=> a = 0.05
    # Entonces 1 - alfa/2 = 0.975 y por lo tanto:
    z_alfa_2 = norm.ppf(0.975)

    def EstimarIntegral(d):
        """
        Devuelve la estimación del valor del área de la integral simulada con el método de Monte Carlo hasta 
        que el semi-ancho del intervalo de confianza del 95% sea < d, su varianza y también, la mínima 
        cantidad de iteraciones (>= 100 para poder aplicar el TCL) que cumplen la condición.
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
    offset = z_alfa_2 * stdNs / sqrt(Ns)
    ICNs = [mediaNs - offset, mediaNs + offset]
    
    print(f"{Ns:^11} {mediaNs:^11.4f} {stdNs:^11.4f} [{ICNs[0]:.4f}, {ICNs[1]:.4f}]")

ejercicio4()