# a) Determinar el período de la secuencia de von Neumann generada a partir de la semilla:
# i) 3009 ii) 7600 iii) 1234 iv) 4321

def von_neumann(seed):
    """
    Genera la secuencia de von Neumann y determina su período.
    """
    seen = {}  # Diccionario para almacenar la posición de cada número
    count = 0  # Contador de iteraciones
    
    while seed not in seen:
        seen[seed] = count  # Guardamos la posición en la que apareció el número
        count += 1
        seed = (seed ** 2 // 100) % 10000  # Extraer los 4 dígitos centrales
    
    return count, seen.keys()

# Evaluamos las semillas dadas
seeds = [3009, 7600, 1234, 4321]
for s in seeds:
    period, sequence = von_neumann(s)
    print(f"Semilla: {s} -> Período: {period}, Secuencia: {list(sequence)}")


