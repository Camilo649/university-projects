import matplotlib.pyplot as plt
import math

# b) Dar el valor de c y de a para que cada generador tenga período máximo.
# yi+1 = 5yi + c mod (2^5), xi+1 = axi mod (31)

c = 3 #mcd(3,2^5) = 1. -> Cualquier numero impar hubiese cumplido

# 5 ≡ 1 mod 2.

# Como 4 | M, tenemos que 5 ≡ 1 mod 4.

#Luego yi+1 = 5yi + 3 mod (2^5) tiene periodo maximo (K=32)


#Factores primos de 30 = 2,3,5
# 30/2 = 15, 30/3 = 10, 30/5 = 6

es_raiz_primitiva = False
a = 0
while not es_raiz_primitiva:
    a += 1
    if (((a**(31//2))%31 != 1) and ((a**(31//3))%31 != 1) and ((a**(31//5))%31 != 1)) or a == 31:
        es_raiz_primitiva = True

print(f"Raiz Primitiva de 31: {a}")

# Luego a es raiz primitiva de 31 y por lo tanto xi+1 = axi mod (31) tiene periodo maximo (K=31)


# Considerar el generador zi = yi + xi mod (2^5) y calcular su período.

def rng1b(a,c):
    x = 1
    y = 1
    z = (y + x) % 32
    ys = [y]
    xs = [x]
    zs = [z]
    for i in range(1000):
        y = (5*y + c) % 32
        x = (a*x) % 31
        z = (y + x) % 32
        ys.append(y)
        xs.append(x)
        zs.append(z)
    return ys, xs, zs

ys, xs, zs = rng1b(a,c)

print(zs)
print(f"El periodo del generador zi = yi + xi mod (32) es: {math.lcm(32, 31)}")

# Representar en tres gráficos separados pares (yi, yi+1), (xi, xi+1) y (zi, zi+1).

fig, ax = plt.subplots(3, 1)
ax[0].plot(ys[:-1], ys[1:], 'ro', label='y')
ax[1].plot(xs[:-1], xs[1:], 'bo', label='x')
ax[2].plot(zs[:-1], zs[1:], 'ko', label='z')
plt.show()