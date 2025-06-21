from random import random
from math import sqrt

def ejercicio1():
    def monte_carlo(N):
        integral = 0
        for _ in range(N):
            Y = random()
            U = 6*Y + 1 # Cambio de Variable
            integral += sqrt(U + sqrt(U))

        return 6 * integral/N
    
    for n in [1000, 10000, 100000]:
        print(f"Estimacion de la integral I con {n} simulaciones: {monte_carlo(n)}")

ejercicio1()

def ejercicio2():
    def juego():
        suma = 0
        sumandos = 0
        while suma <= 1: # Termina cuando suma > 1
            suma += random()
            sumandos += 1
        
        return sumandos
    
    def pares(N):
        veces_que_fue_impar = 0
        for _ in range (N):
            if (juego() % 2) == 1:
                veces_que_fue_impar += 1
            
        return veces_que_fue_impar/N
    
    for n in [100, 1000, 10000]:
        print(f"Estimacion de p con {n} simulaciones: {pares(n)}")

ejercicio2()
