from random import random, uniform
from math import log


def ejercicio1():
    print("================================= Ejercicio 1 =================================")
    
    def generarA():
        A = [0] * 100
        for i in range (32,53):
            A[i] = 1
        for i in range (53,86):
            A[i] = 2
        for i in range (86,100):
            A[i] = 3
        return A
    
    A = generarA()

    def Urna():
        I = int(100 * random())
        return A[I]

def ejercicio2():
    print("================================= Ejercicio 2 =================================")

    C = -0.5*log(1.5)
    def TI():
        U = random()
        if U < 1/3:
            return log(3*U)
        return C - 0.5*log(1-U)
    
    def ProbXMenorOIgual1(nsim):
        count = 0
        for _ in range (nsim):
            if TI() <= 1:
                count += 1
        
        return count/nsim
    
    nsim = 10_000
    print(f"P(X <= 1) = {ProbXMenorOIgual1(nsim)}")

ejercicio2()

def ejercicio3():
    print("================================= Ejercicio 3 =================================")

    def AyR():
        while True:
            U = random()
            Y = uniform(-1,1)
            if U < 1 - Y**2:
                return Y
            
    def ProbXMayorA0(nsim):
        count = 0
        for _ in range (nsim):
            if AyR() > 0:
                count += 1

        return count/nsim
    
    nsim = 1_000_000 # Estimamos con 1 millón de simulaciones
    print(f"P(X > 0) = {ProbXMayorA0(nsim)}")

ejercicio3()

def ejercicio4():
    print("================================= Ejercicio 4 =================================")
    
    def simularX():
        U = random()
        tirada_actual = ''
        if U < 1/3:
            tirada_actual = "cara"
        else:
            tirada_actual = "cruz"
        tirada_anterior = ''
        count = 1
        while tirada_actual != tirada_anterior:
            count += 1
            tirada_anterior = tirada_actual
            U = random()
            if U < 1/3:
                tirada_actual = "cara"
            else:
                tirada_actual = "cruz"

        return count
    
    def ProbXIgual4(nsim, f):
        count = 0
        for _ in range (nsim):
            if f() == 4:
                count += 1

        return count/nsim
    
    nsim = 1_000_000 # Estimamos con 1 millón de simulaciones
    print(f"P(X = 4) = {ProbXIgual4(nsim, simularX)}")

    def Geometrica(p):
        U = random()
        return int(log(1-U)/log(1-p)) + 1

    def p(n):
        if n < 2:
            return 0
        return (2**(n-1) + 2) / 3**n

    def AyR():
        while True:
            U = random()
            Y = Geometrica(1/3)
            if Y >= 2 and U < p(Y) / (2/3)**Y:
                return Y
            
    print(f"Método de Aceptación y Rechazo: P(X = 4) = {ProbXIgual4(nsim, AyR)}")


ejercicio4()