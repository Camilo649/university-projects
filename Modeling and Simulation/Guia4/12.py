from random import random
import numpy as np
import matplotlib.pyplot as plt

# Ejercicio 12. ¿Qué distribución tiene la variable simulada por el siguiente algoritmo?
def QueDevuelve(p1,p2):
    X = int(np.log(1-random())/np.log(1-p1))+1
    Y = int(np.log(1-random())/np.log(1-p2))+1
    return min(X,Y)

# Por lo demostrado en la carpeta, la distribución de la variable es Geométrica de parámetro p1+p2-p1p2

# Escriba otro algoritmo que utilice un único número aleatorio (random()) y que simule una variable con
# la misma distribución que la simulada por QueDevuelve(0.05, 0.2).

def Simulacion(p1,p2):
    return int(np.log(1-random())/np.log(1-(p1+p2-p1*p2)))+1

# Simulamos
N = 100000
p1, p2 = 0.05, 0.2

datos_que_devuelve = [QueDevuelve(p1, p2) for _ in range(N)]
datos_simulacion = [Simulacion(p1, p2) for _ in range(N)]

# Armamos los histogramas
max_val = max(max(datos_que_devuelve), max(datos_simulacion))
x = np.arange(1, max_val+1)

# Frecuencias relativas
hist_que = np.array([datos_que_devuelve.count(k)/N for k in x])
hist_sim = np.array([datos_simulacion.count(k)/N for k in x])

# Gráfico
plt.figure(figsize=(10,6))
plt.bar(x-0.2, hist_que, width=0.4, label='QueDevuelve', alpha=0.7, color='royalblue')
plt.bar(x+0.2, hist_sim, width=0.4, label='Simulacion', alpha=0.7, color='salmon')
plt.xlabel('Valor de la Variable')
plt.ylabel('Frecuencia relativa')
plt.title('Comparación entre QueDevuelve y Simulacion')
plt.legend()
plt.grid(True, linestyle='--', alpha=0.5)
plt.xticks(x)
plt.show()