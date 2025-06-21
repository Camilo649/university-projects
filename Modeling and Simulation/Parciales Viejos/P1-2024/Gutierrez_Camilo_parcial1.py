from random import random
from math import log

def ejercicio3():
    def monte_carlo(N):
        integral = 0
        for _ in range(N):
            y = random()
            u = 1/y       #Cambio de Vairable
            integral += (u**2)/(u**2 * log(u+1))
        return integral/N
    
    for n in [1000,10000,100000]:
        print(f"Valor de la integral con {n} simulaciones: {monte_carlo(n)}")

ejercicio3() 

