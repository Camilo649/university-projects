# Ejercicio 2. Se propone el siguiente juego en el cual todas las variables aleatorias que se
# generan son independientes e idénticamente distribuidas U(0, 1): Se simula la variable
# aleatoria U. Si U < 1/2, se suman dos nuevos números aleatorios W1 +W2. Pero si U ≥ 1/2, se
# suman tres números aleatorios. El resultado de la suma, en cualquiera de los casos, es una
# variable aleatoria X. Se gana en el juego si X ≥ 1.

# a) ¿Cuál es la probabilidad de ganar?.

# Rta: es 2/3. 
# El calculo esta en la carpeta

# b) Implementar un algoritmo en computadora que estime la probabilidad de ganar, esto es,
# la fracción de veces que se gana en n realizaciones del juego.
# Probar con n = 100,1000,10000,100000,1000000

import random

def game(N):
    wins = 0
    for _ in range(N):
        U = random.random()
        W1 = random.random()
        W2 = random.random()

        if U < 0.5:
            X = W1 + W2
        else:
            W3 = random.random()
            X = W1 + W2 + W3

        if X >= 1:
            wins += 1
    return wins / N

print("Probabilidad de ganar con 100 realizaciones:", game(100))
print("Probabilidad de ganar con 1000 realizaciones:", game(1000))
print("Probabilidad de ganar con 10000 realizaciones:", game(10000))
print("Probabilidad de ganar con 100000 realizaciones:", game(100000))
print("Probabilidad de ganar con 1000000 realizaciones:", game(1000000))    