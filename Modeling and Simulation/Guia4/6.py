from random import random
from time import perf_counter as pf

# Ejercicio 6. Una variable aleatoria X tiene una función de probabilidad puntual pi = P(X = i) dada por
# p0 = 0,15, p1 = 0,20, p2 = 0,10, p3 = 0,35, p4 = 0,20

p = [0.15, 0.20, 0.10, 0.35, 0.20]

# I) Describir mediante un pseudocódigo un algoritmo que simule X utilizando el método de la transfor-
# mada inversa y que minimice el número esperado de búsquedas.

# Paso 1: Generar U, una varaible aleatoria uniforme en el intervalo (0,1)
# Paso 2: Si U < 0.35, detenerse y devolver 3
# Paso 3: Si U < 0.55, detenerse y devolver 1
# Paso 4: Si U < 0.75, detenerse y devolver 4
# Paso 5: Si U < 0.90, detenerse y devolver 0
# Paso 6: Detenerse y devolver 2

# Como primero revisamos los valores más probables, el número esperado de búsquedas es mínimo

# II) Describir mediante un pseudocódigo un algoritmo que simule X utilizando el método de aceptación y
# rechazo con una variable soporte Y con distribución binomial B(4,0.45).

# Tomaremos la constante c tan pequeña como nos sea posible para nuestra Y.
# Para ello, primero calculamos las probabilidades de Y en el arreglo q
q = [0.55**4, 4*(0.45)*(0.55**3), 6*(0.45**2)*(0.55**2), 4*(0.45**3)*(0.55), 0.45**4]
# Luego el menor c, será el valor más grande de los pi/qi para i {0,...,4}
c = max([p[i]/q[i] for i in range(5)])
# Chequeamos por las dudas...
print("----------CHEQUEO----------")
for i in range(5):
    print(f"{p[i]} <= {q[i]*c}")
print("----------CHEQUEO----------")
print()
# Asi, el algoritmo queda como sigue:
# Paso 1: Simular Y
# Paso 2: Generar U, una varaible aleatoria uniforme en el intervalo (0,1)
# Paso 3: Si U < p[Y]/(c*q[Y]), detenerse y devolver Y. En caso contrario, volver al paso 1

# III) Compare la eficiencia de los dos algoritmos realizando 10000 simulaciones.

def TI():
    U = random()
    if U < 0.35: return 3
    if U < 0.55: return 1
    if U < 0.75: return 4
    if U < 0.90: return 0
    else:        return 2

# Aprovechando que sabemos que el valor más probable de una Binomial de parámetros (n,p) es int((n+1)*p), 
# partimos desde la acumulacion de probabilidades hasta ese valor y luego procedemos con el algoritmo
# tradicional del metodo de la transformada inversa dependiendo del cual sea el valor de la variable U.
# Todo esto con el afán de disminuir el número de comparaciones
def Binomial(n,p):
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
    
def AyR():
    while True:
        Y = Binomial(4,0.45)
        U = random()
        if U < p[Y]/(c*q[Y]):
            return Y
        
def Eficiencia(f,nsim):
    inicio = pf()
    for _ in range(nsim): f()
    fin = pf()
    return fin-inicio

print(f"Alogirtmo            | Tiempo Transcurrido")
print(f"------------------------------------------")
print(f"Transformada Inversa | {Eficiencia(TI,10000):.6f}")
print(f"Aceptación y Rechazo | {Eficiencia(AyR,10000):.6f}") 