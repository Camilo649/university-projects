from random import shuffle

def ExpectationAndVariance(N):
    cards = list(range(100))
    results = []

    for _ in range (N):
        shuffle(cards)
        succes = sum(cards[i] == i for i in range(100))
        results.append(succes)

    esp = sum(results) / N
    var = sum((x - 1)**2 for x in results) / N #Restamos 1 porque sabemos que E[X] == 1

    return esp, var

def Experiment1(N, r):
    """
    Estima la probabilidad de que las primeras r cartas sean coincidencias
    """
    cards = list(range(100))
    succes = 0
    for _ in range(N):
        shuffle(cards)
        if cards[:r] == list(range(r)):
            succes += 1

    return succes/N

def Experiment2(N, r):
    """
    Estima la probabilidad de que las primeras r cartas sean coincidencias
    """
    cards = list(range(100))
    succes = 0
    for _ in range(N):
        shuffle(cards)
        if cards[:r] == list(range(r)):
            matches = [i for i in range(r, 100) if cards[i] == i]
            if len(matches) == 0:
                succes += 1

    return succes/N
    

for n in [100, 1000, 10000, 100000]:
    E,V = ExpectationAndVariance(n)
    print(f"{n:>7} iteraciones | Esperanza ≈ {E:.6f} | Varianza ≈ {V:.6f}")


for n in [100, 1000, 10000, 100000]:
    print(f"{n:>7} iteraciones | P(10 primeras coincidencias) ≈ {Experiment1(n,10):.6f}")
    print(f"{n:>7} iteraciones | P(exactamente 10 primeras coincidencias) ≈ {Experiment2(n,10):.6f}")

