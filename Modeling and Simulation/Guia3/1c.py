import math
from sympy import isprime

# c) Indicar en cuáles de los siguientes casos el generador
# yi+1 = ayi + c mod (M)
# genera una secuencia de período máximo.
# • a = 125, c = 3, M = 2^9
# • a = 123, c = 3, M = 2^9
# • a = 5, c = 0, M = 71
# • a = 7, c = 0, M = 71

def prime_factors(n):
    """
    Devuelve los factores primos de n.
    """
    factors = set()
    d = 2
    while d * d <= n:
        while (n % d) == 0:
            factors.add(d)
            n //= d
        d += 1
    if n > 1:
        factors.add(n)
    return factors

def maxPeriodo(a, c, M):
    """
    Determina si el generador yi+1 = ayi + c mod (M) tiene período máximo.
    """
    if c!=0:
        # Caso generador mixto
        if math.gcd(c, M) != 1:
            return False
        
        for p in prime_factors(M):
            if a % p != 1:
                return False
            
        if M/4 == 0 or a % 4 != 1:
            return False
    else:
        # Caso generador multiplicativo
        if not isprime(M):
            return False
        
        for p in prime_factors(M-1):
            print(f"{pow(a, (M-1) // p, M)}")
            if pow(a, (M-1) // p, M) == 1:
                return False

    return True


casos = [
    (125, 3, 2**9),
    (123, 3, 2**9),
    (5, 0, 71),
    (7, 0, 71)
]

# Evaluamos cada caso
for a, c, M in casos:
    if maxPeriodo(a, c, M):
        print(f"El generador yi+1 = {a}yi + {c} mod ({M}) tiene periodo maximo.")
    else:
        print(f"El generador yi+1 = {a}yi + {c} mod ({M}) NO tiene periodo maximo.")
