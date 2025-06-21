from random import random
from time import perf_counter as pc
from math import sqrt, log

def ej1():

    # Arreglo de probabilidades para la variable X
    p = [0.14, 0.11, 0.08, 0.09, 0.10, 0.12, 0.11, 0.07, 0.09, 0.09]

    def AyR():
        while True:
            Y = int(10*random()) + 51 # Simulamos Y ~ U{51,60}
            U = random()
            if U < p[Y-51] / 0.14:
                return Y  

    # Ordenamos p para minimizar el numero de comparaciones
    p_with_index = list(enumerate(p))
    p_ord = sorted(p_with_index, key=lambda x: x[1], reverse=True)

    def TI():
        prob = 0
        U = random()
        for i in range (len(p_ord) - 1):
            prob += p_ord[i][1]
            if U < prob:
                return p_ord[i][0] + 51

        return p_ord[9][0] + 51

    A = [51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, # 14 veces el valor 51
         52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52,             # 11 veces el valor 52
         53, 53, 53, 53, 53, 53, 53, 53,                         # 8 veces el valor 53
         54, 54, 54, 54, 54, 54, 54, 54, 54,                     # 9 veces el valor 54
         55, 55, 55, 55, 55, 55, 55, 55, 55, 55,                 # 10 veces el valor 55
         56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56,         # 12 veces el valor 56
         57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57,             # 11 veces el valor 57
         58, 58, 58, 58, 58, 58, 58,                             # 7 veces el valor 58
         59, 59, 59, 59, 59, 59, 59, 59, 59,                     # 9 veces el valor 59
         60, 60, 60, 60, 60, 60, 60, 60, 60]                     # 9 veces el valor 60

    def Urna():
        I = int(100 * random())
        return A[I]
    
    def EficienciaYEsperanza(nsim, f):
        """
        Devuelve el tiempo transcurrido tras estimar la esperanza de la variable aleatoria X por medio de nsim
        ejecuciones de la función f, donde f simula a la variable X. Además, devuelve también la esperanza
        estimada.
        """
        inicio = pc()
        E = 0
        for _ in range(nsim):
            E += f()
        E /= nsim
        final = pc()
        return final-inicio, E
    
    nsim = 10_000
    T1, E1 = EficienciaYEsperanza(nsim, AyR)
    T2, E2 = EficienciaYEsperanza(nsim, TI)
    T3, E3 = EficienciaYEsperanza(nsim, Urna) 
    Esperanza_real = sum((51 + i) * pi for i, pi in enumerate(p))


    print(f"Método | Tiempo | Esperanza | Error Absoluto")
    print(f"--------------------------------------------")
    print(f"AyR    | {T1:4.4f} | {E1:6.6f} | {abs(E1-Esperanza_real):11.11f}")
    print(f"TI     | {T2:4.4f} | {E2:6.6f} | {abs(E2-Esperanza_real):11.11f}")
    print(f"Urna   | {T3:4.4f} | {E3:6.6f} | {abs(E3-Esperanza_real):11.11f}")

#ej1()

def ej2():

    def TI():
        U = random()
        if U < 0.5:
            return sqrt(2*U)
        return 2*U
    
    def f(x):
        if 0 <= x <= 1:
            return x
        elif 1 < x <= 2:
            return 0.5
        return 0

    def AyR():
        while True:
            Y = 2*random() # Simulamos Y ~ U(0,2)
            U = random()
            if U < f(Y):
                return Y
            
    # Para determinar cual de los métodos es más eficiente, compararemos cuánto tarda cada uno con 1000000 de
    # ejecuciones
    def eficiencia(nsim, f):
        inicio = pc()
        for _ in range(nsim):
            f()
        final = pc()
        return final-inicio
    
    nsim = 1_000_000
    T1 = eficiencia(nsim,TI)
    T2 = eficiencia(nsim, AyR)

    print(f"Método | Tiempo")
    print(f"---------------")
    print(f"TI     | {T1:4.4f}")
    print(f"AyR    | {T2:4.4f}")
    print()
    if T1 < T2:
        print("De lo anterior, el método de la Transformada Inversa es el más eficiente de los dos.")
    else:
        print("De lo anterior, el método de la Aceptación y Rechazo es el más eficiente de los dos.")

ej2()

def ej3():

    def simularS():
        S = 0
        K = int(log(1-random())/log(1-0.15)) + 1 # Simulamos una Geométrica(0.15)
        while K < 100:
            S += 1
            K += int(log(1-random())/log(1-0.15)) + 1
        return S
    
    def ProbSMayorQue20(nsim):
        count = 0
        for _ in range(nsim):
            if simularS() > 20:
                count += 1
            
        return count/nsim
    
    nsim = 1_000_000 
    prob = ProbSMayorQue20(nsim)
    print(f"Probabilidad de que el lavadero tenga que antender a más de 20 personas el sábado: {prob}")

ej3()

def ej4():

    def lambda_t(t):
        if 0 <= t <= 4:
            return t**2 -2*t + 2
        return 0


    def eventosPoissonNH(lamda,lambda_t,T):
        """
        Simula un Proceso de Poisson No Homogéneo mediante el método de adelgazamiento cuya función de intensidad es 
        lambda_t. Devuelve una lista con el tiempo en el que ocurrió cada evento hasta un timpo T.
        """
        Eventos = []
        t = -log(1 - random()) / lamda
        while t <= T:
            V = random()
            if V < lambda_t(t) / lamda:
                Eventos.append(t)
            t += -log(1 - random()) / lamda
        return Eventos
    
    print("Tiempos de arribo hasta T=4:")
    print(eventosPoissonNH(10,lambda_t,4))

ej4()

