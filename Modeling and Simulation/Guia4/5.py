from random import random
from math import log
import numpy as np
from time import perf_counter

# Ejercicio 5. Implemente dos métodos para generar una binomial Bin(n, p):
# I) Usando transformada inversa.

# Aprovechando que sabemos que el valor más probable de una Binomial de parámetros (n,p) es int((n+1)*p), 
# partimos desde la acumulacion de probabilidades hasta ese valor y luego procedemos con el algoritmo
# tradicional del metodo de la transformada inversa dependiendo del cual sea el valor de la variable U.
# Todo esto con el afán de disminuir el número de comparaciones
def Binomial1(n,p):
    c = p/(1-p)
    prob = (1-p)**n
    F = prob
    for i in range(1, int((n+1)*p) + 1): # Acumulamos hasta int((n+1)*p)
        prob *= (c*(n-i+1))/i 
        F += prob
    U = random()
    if U >= F:                           # Algoritmo normal de la transformada inversa
        j = int((n+1)*p) + 1
        while U >= F:
            prob *= (c*(n-j+1))/j
            F += prob
            j += 1
        return j-1
    else:                                # Algoritmo normal de la transformada inversa descendente
        j = int((n+1)*p) 
        while U < F:
            F -= prob
            prob *= j/(c*(n-j+1))
            j -= 1
        return j+1

# II) Simulando n ensayos con probabilidad de éxito p y contando el número de éxitos.

# Simular un ensayo equivale a generar un valor de una variable aleatoria con distribucion Bernoulli de
# parámetro p. Para generar n ensayos, podemos optimizar el proceso generando k valores de una variable
# aleatoria geométrica de parámetro p hasta que la suma de los k valores obtenidos sea mayor o igual que n
def Geometrica(p):
    U = random()
    return int(log(1-U)/log(1-p)) + 1

def NBernoullis(N,p):
    Bernoullis = np.zeros(N)
    k = Geometrica(p)-1
    while k < N:
        Bernoullis[k] = 1
        k += Geometrica(p)
    return Bernoullis

def Binomial2(n,p):
    B = NBernoullis(n,p)
    return int(B.sum())

# Para ambos métodos:
# a) Compare la eficiencia de ambos algoritmos para n = 10 y p = 0,3, evaluando el tiempo necesario para
# realizar 10000 simulaciones.

def EficienciaBinomial(f,n,p,nsim):
    inicio = perf_counter()
    for _ in range(nsim): f(n,p)
    fin = perf_counter()
    return fin-inicio

print(f"Alogirtmo | Tiempo Transcurrido")
print(f"-------------------------------")
print(f"Binomial1 | {EficienciaBinomial(Binomial1,10,0.3,10000):.6f}")
print(f"Binomial2 | {EficienciaBinomial(Binomial2,10,0.3,10000):.6f}") 

# NOTA: Si bien con 10000 iteraciones pareciera ser que el método de la TI inversa es más eficiente, al umentar
# la cantidad, se ve que no es así. Lo que aquí sucede, es que las llamadas a funciones penalizan al segundo
# algoritmo, pero para un mayor número de iteraciones, tal penalización resulta marginal

# b) Estime el valor con mayor ocurrencia y la proporción de veces que se obtuvieron los valores 0 y 10
# respectivamente.
# c) Compare estos valores con las probabilidades teóricas de la binomial. Si están alejados, revise el código.

def b(f,nsim):
    """
    Estima el valor de mayor ocurrencia y la proporción de veces que se obtuvieron los valores 0 y 10
    para una variable aleatoria binomial de parámetros (10,0.3) con nsim simulaciones. La funcion f debe
    simular la variable
    """
    ocurrencias = np.zeros(11) # Nos interesan los valores desde 0 hasta n
    for _ in range(nsim):
        ocurrencias[f(10,0.3)] += 1
    return np.argmax(ocurrencias), ocurrencias[0]/nsim, ocurrencias[10]/nsim

# Estimamos con 1000000 simulaciones para que la probabilidad de obtener 10 no sea 0 tantas veces
max1, cero1, diez1 = b(Binomial1,1000000)
max2, cero2, diez2 = b(Binomial2,1000000)
cero, diez = 0.7**10, 0.3**10

print(f"                           | Binomial1 | Binomial2 | Binomial Real")
print(f"------------------------------------------------------------------")
print(f"Valor con mayor ocurrencia | {max1}         | {max2}         | 3")  
print(f"Proporción 0               | {cero1*100:.6f}% | {cero2*100:.6f}% | {cero*100:.6f}%")
print(f"Proporción 10              | {diez1*100:.6f}% | {diez2*100:.6f}% | {diez*100:.6f}%")