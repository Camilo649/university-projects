from random import random


def Ejercicio1():
    print("================================= Ejercicio 1 =================================")

    def AyR():
        while True:
            Y = random()
            U = random()
            if U < 225 * (Y**2 -2*Y**3 + Y**4) / 4:
                return Y
            
    def Esperanza(nsim):
        E = 0
        for _ in range(nsim):
            E += AyR()

        return E/nsim
    
    nsim = 10_000
    print(f"Estimacion del valor esperado para {nsim} simulaciones: {Esperanza(nsim)}")   

Ejercicio1()

def Ejercicio2():
    print("================================= Ejercicio 2 =================================")

    def codigoX(p):
        I = 10
        F = p
        pi = p
        U = random()
        while U >= F:
            I += 1
            pi *= (1-p)
            F += pi

        return I

    def Esperanza(nsim, p):
        E = 0
        for _ in range(nsim):
            E += codigoX(p)

        return E/nsim
    
    nsim = 10_000
    p = 0.5
    print(f"Estimacion del valor esperado para {nsim} simulaciones para p = {p}: {Esperanza(nsim, p)}")

Ejercicio2()
