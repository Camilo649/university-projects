from random import random
from math import exp

def ejercicio2():
    def juego(N):
        victorias = 0
        for _ in range (N):
            U = random()
            V = random()
            if max(U,V) > 0.6:
                victorias += 1
        
        return victorias/N
    
    n = 10000
    print(f"Estiamcion de la probabilidad de que gane A para {n} simulaciones: {juego(n)}")

ejercicio2()

def ejercicio4():
    def monte_carlo_a(N):
        integral = 0
        for _ in range (N):
            X = random()
            Y = random()
            integral += 1-exp(-(X+Y))

        return integral/N
    
    def monte_carlo_b(N):
        integral = 0
        for _ in range (N):
            X = random()
            Y = 1/X # Cambio de Variable
            integral += Y**2 * exp(-Y**2) * Y**2

        return integral/N
    
    for n in [1000, 10000, 100000, 1000000]:
        print(f"Estimacion de la integral a con {n} simulaciones: {monte_carlo_a(n)}")
        print(f"Estimacion de la integral b con {n} simulaciones: {monte_carlo_b(n)}")

ejercicio4()