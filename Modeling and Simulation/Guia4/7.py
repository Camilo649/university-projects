from random import random
from math import exp

# Ejercicio 7. Estime P(Y > 2) con λ = 10, y 1000 repeticiones para la variable Poisson, simulando con
# método de transformada inversa común e inversa mejorado.

def Poisson(lamda):
    U = random()
    i = 0
    p = exp(-lamda)
    F = p
    while U >= F:
        i += 1
        p *= lamda/i
        F += p
    return i

def PoissonMejorada(lamda):
    p = exp(-lamda)
    F = p
    for i in range(1, int(lamda)+1): # Acumulamos hasta el valor más probable
        p *= lamda/i
        F += p
    U = random()
    if U >= F:
        j = int(lamda)+1
        while U >= F:
            p *= lamda/j
            F += p
            j += 1
        return j-1
    else:
        j = int(lamda)
        while U < F:
            F -= p
            p *= j/lamda
            j -= 1
        return j+1
    
def Simulacion(f,lamda,nsim):
    """
    Estima la probabilidad de que una variable aleatoria con distribucion de Poisson de parámetro lamda
    sea mayor estricto que 2 con nsim simulaciones. La funcion f debe simular la variable
    """
    contador = 0
    for _ in range(nsim):
        if f(lamda) > 2:
            contador += 1
    
    return contador/nsim

print(f"Poisson  | Poisson Mejorada | Poisson Real")
print(f"------------------------------------------")
print(f"{Simulacion(Poisson,10,1000):.6f} | {Simulacion(PoissonMejorada,10,1000):.6f}         | {1 - (exp(-10) + (exp(-10)*10) + (exp(-10)*50)):.6f}")  