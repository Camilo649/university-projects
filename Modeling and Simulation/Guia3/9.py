# Ejercicio 9. Un juego consiste en dos pasos. En el primer paso se tira un dado convencional. Si sale 1 o
# 6 tira un nuevo dado y se le otorga al jugador como puntaje el doble del resultado obtenido
# en esta nueva tirada; pero si sale 2, 3, 4 o 5 en la primer tirada, el jugador debería tirar
# dos nuevos dados, y recibiría como puntaje la suma de los dados. Si el puntaje del jugador
# excede los 6 puntos entonces gana.

# a) Realizar un cálculo teórico de la probabilidad de que un jugador gane.

valor_real = 5/9 # El calculo esta en la carpeta

# b) Estime la probabilidad de que un jugador gane mediante una simulación.

import random

def DiceGame(N):
    wins = 0
    for _ in range(N):
        points = 0
        W1 = int(6*random.random()) + 1
        if W1 == 1 or W1 == 6:
            W2 = int(6*random.random()) + 1
            points += 2 * W2
        else:
            W2 = int(6*random.random()) + 1
            W3 = int(6*random.random()) + 1
            points += W2 + W3

        if points > 6:
            wins += 1

    return wins / N

print(f"Probabilidad de ganar con 1000000 realizaciones: {DiceGame(1000000)}, con error: {abs(DiceGame(1000000) - valor_real)}")
