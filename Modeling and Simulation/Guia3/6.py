# Ejercicio 6. Es posible aproximar el valor de π calculando el área de un círculo de radio 1
# centrado en 0. Para eso, se necesitan generar N puntos aleatorios en la caja [−1, 1] ×
# [−1, 1] y contar la cantidad de veces que los mismos caen dentro del círculo. El cociente
# entre este número y N, multiplicado por 4 (el área del cuadrado donde está contenido el
# círculo) es una aproximación de π. Probar con n = 1000,10000,100000

import random
import math

def MonteCarloPi(n):
    Pi = 0
    for _ in range(n):
        u,v = 2*random.random() - 1, 2*random.random() - 1
        if u**2 + v**2 <= 1:
            Pi += 1
    return 4 * Pi / n

for n in [1000, 10000, 100000]:
    pi_approx = MonteCarloPi(n)
    error = abs(pi_approx - math.pi)
    print(f"Valor aproximado de π con {n} iteraciones: {pi_approx}, con error: {error}")