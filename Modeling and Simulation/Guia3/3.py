# Ejercicio 3. Las máquinas tragamonedas usualmente generan un premio cuando hay un acierto.
# Supongamos que se genera el acierto con el siguiente esquema: se genera un número aleatorio,
# y
# i) si es menor a un tercio, se suman dos nuevos números aleatorios
# ii) si es mayor o igual a un tercio, se suman tres números aleatorios .
# Si el resultado de la suma es menor o igual a 2, se genera un acierto.
# a) ¿Cuál es la probabilidad de acertar?.

# Rta: es 8/9. 
# El calculo esta en la carpeta

# b) Implementar un algoritmo en computadora que estime la probabilidad de acertar, esto es,\
# la fracción de veces que se acierta en n realizaciones del juego.
# Probar con n = 100,1000,10000,100000,1000000 

import random

def slot_machine(N):
    wins = 0
    for _ in range(N):
        U = random.random()
        W1 = random.random()
        W2 = random.random()

        if U < 1/3:
            X = W1 + W2
        else:
            W3 = random.random()
            X = W1 + W2 + W3

        if X <= 2:
            wins += 1
    return wins / N

print("Probabilidad de acertar con 100 realizaciones:", slot_machine(100))
print("Probabilidad de acertar con 1000 realizaciones:", slot_machine(1000))
print("Probabilidad de acertar con 10000 realizaciones:", slot_machine(10000))
print("Probabilidad de acertar con 100000 realizaciones:", slot_machine(100000))
print("Probabilidad de acertar con 1000000 realizaciones:", slot_machine(1000000))