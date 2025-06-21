from random import random
from math import exp

def ejercicio2():
    def juego(N):
        victoriasA = 0
        for _ in range (N):
            U = random()
            V = random()
            # A gana la primera jugada
            if U > 0.5 and V < 0.5:
                victoriasA += 1
            else:
                # Se tiene que haber dado un empate (B tampoco gano) y luego gana A
                if not(U < 0.5 and V > 0.5) and (random() > 0.5 and random() < 0.5):
                    victoriasA += 1 

        return victoriasA/N
    
    n = 100000
    print(f"Estimacion del inciso 2b con {n} simulaciones: {juego(n)}")

ejercicio2()

def ejercicio4():
    def integral_a(N):
        integral = 0
        for _ in range(N):
            y = random()
            u = 6*y - 3
            integral += (u)/(u-exp(u))

        return 6*integral/N
    
    def integral_b(N):
        integral = 0
        for _ in range(N):
            y = random()
            u = 1/y - 2
            integral += (u**3) * (exp(-(u**3))) * (1/(y**2))
            
        return integral/N
    
    for n in [1000, 10000, 100000, 1000000]:
        print(f"Estimacion de la integral a con {n} simulaciones: {integral_a(n)}")
        print(f"Estimacion de la integral b con {n} simulaciones: {integral_b(n)}")

ejercicio4()