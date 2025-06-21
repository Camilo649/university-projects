# Ejercicio 5. Calcule exactamente el valor de las siguientes integrales. Mediante una
# simulación de Monte Carlo con n = 1000, 5000, 10000 iteraciones, calcule a su vez un valor
# aproximado y compare con el valor exacto.

import random
import math

def a(n):
    integral = 0
    for _ in range(n):
        u = random.random()
        integral += (1 - u**2)**(3/2)
    return integral / n

print("Inciso a:")
real_value = (3 * math.pi) / 16
print("Valor real(aproximado):", real_value)
ap = [(1000,a(1000)), (5000,a(5000)), (10000,a(10000))]
for n,v in ap:
    print(f"Valor aproximado con {n} iteraciones: {v}, con error: {abs(v - real_value)}")

def b(n):
    integral = 0
    for _ in range(n):
        u = random.random()
        integral += (u+2)/((u+2)**2 - 1)
    return integral / n

print("Inciso b:")
real_value = math.log(8/3) / 2
print("Valor real(aproximado):", real_value)
bp = [(1000,b(1000)), (5000,b(5000)), (10000,b(10000))]
for n,v in bp:
    print(f"Valor aproximado con {n} iteraciones: {v}, con error: {abs(v - real_value)}")

def c(n):
    integral = 0
    for _ in range(n):
        u = random.random()
        y = 1/u - 1
        integral += (y) * (1 + (y)**2)**-2 * 1/(u**2)
    return integral / n

print("Inciso c:")
real_value = 1/2
print("Valor real:", real_value)
cp = [(1000,c(1000)), (5000,c(5000)), (10000,c(10000))]
for n,v in cp:
    print(f"Valor aproximado con {n} iteraciones: {v}, con error: {abs(v - real_value)}")

def d(n):
    integral = 0
    for _ in range(n):
        u = random.random()
        y = 1/u - 1
        integral += math.e**-(y)**2 * (1/u**2)
    return 2 * integral / n 

print("Inciso d:")
real_value = math.sqrt(math.pi)
print("Valor real(aproximado):", real_value)
dp = [(1000,d(1000)), (5000,d(5000)), (10000,d(10000))]
for n,v in dp:
    print(f"Valor aproximado con {n} iteraciones: {v}, con error: {abs(v - real_value)}")

def f(n):
    integral = 0
    for _ in range(n):
        u = random.random()
        y = 1/u - 1
        integral += -(math.exp(-2 * y) - math.exp(-y)) * (1 / u**2)
    return integral / n

print("Inciso f:")
real_value = 1/2
print("Valor real(aproximado):", real_value)
fp = [(1000,f(1000)), (5000,f(5000)), (10000,f(10000))]
for n,v in fp:
    print(f"Valor aproximado con {n} iteraciones: {v}, con error: {abs(v - real_value)}")

al = [a(100), a(1000), a(10000), a(100000), a(1000000)]
bl = [b(100), b(1000), b(10000), b(100000), b(1000000)]
cl = [c(100), c(1000), c(10000), c(100000), c(1000000)]
dl = [d(100), d(1000), d(10000), d(100000), d(1000000)]
fl = [f(100), f(1000), f(10000), f(100000), f(1000000)]

print(f"Valores aproximados de a: {al}")
print(f"Valores aproximados de b: {bl}")
print(f"Valores aproximados de c: {cl}")
print(f"Valores aproximados de d: {dl}")
print(f"Valores aproximados de f: {fl}")