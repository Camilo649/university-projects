import matplotlib.pyplot as plt
import math

# d) Utilice el generador RANDU
# ui = a · ui−1 m´od (M), a = 216 + 3, M = 231,
# para generar puntos aleatorios en el cubo [0, M) × [0, M] × [0, M), de la forma:
# (u1, u2, u3), (u4, u5, u6), . . .

def randu(a, M):
    x = 1
    l = [x]
    for _ in range(20000):
        x = (a * x) % M
        l.append(x)

    return l

lista = randu(2**16 + 3, 2**31)

xs = lista[0::3]
ys = lista[1::3]
zs = lista[2::3]

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(xs, ys, zs, c='r', marker='o')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.show()


# y estimar el porcentaje de puntos que caen en la esfera centrada en (M/2, M/2, M/2) de radio M/10.

contador = 0
for i in range(0, int(20001/3)):
    if ((xs[i] - 2**31/2)**2 + (ys[i] - 2**31/2)**2 + (zs[i] - 2**31/2)**2) <= (2**31/10)**2:
        contador += 1
estimacionRANDU = contador / (20001/3)

print(f"Estimacion de puntos en la esfera: {estimacionRANDU}")

# Repetir el procedimiento con el generador
# yi = a · yi−1 mod (M), a = 7^5, M = 231 − 1.

def rng():
    x = 1
    l = [x]
    for i in range(20000):
        x = (7**5 * x) % (2**31 - 1)
        l.append(x)

    return l

lista = rng()

xs = lista[0::3]
ys = lista[1::3]
zs = lista[2::3]

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(xs, ys, zs, c='r', marker='o')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.show()

contador = 0
for i in range(0, int(20001/3)):
    if ((xs[i] - 2**31/2)**2 + (ys[i] - 2**31/2)**2 + (zs[i] - 2**31/2)**2) <= (2**31/10)**2:
        contador += 1
estimacionRNG = contador / (20001/3)

print(f"Estimacion de puntos en la esfera: {estimacionRNG}")

# ¿Cuál de los dos generadores estima mejor el valor real?

valor_real = 4 * math.pi / 3000
print(f"Valor real:{valor_real}")
mn = min(estimacionRANDU-valor_real, estimacionRNG-valor_real)
if mn == estimacionRANDU-valor_real:
    print("El generador RANDU estima mejor el valor real, con un error de: ", mn)
else:
    print("El generador yi = 7^5*yi-1 mod (2^31 -1) estima mejor el valor real, con un error de: ", mn)