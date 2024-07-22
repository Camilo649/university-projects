import requests

# Obtener todas las películas
response = requests.get('http://localhost:5000/peliculas')
peliculas = response.json()
print("Películas existentes:")
for pelicula in peliculas:
    print(
        f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
print()

# Obtener detalles de una película específica
id_pelicula = 1  # ID de la película a obtener
response = requests.get(f'http://localhost:5000/peliculas/{id_pelicula}')
if response.status_code == 200:
    pelicula = response.json()
    print("Detalles de la película:")
    print(
        f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
else:
    print("Error al obtener los detalles de la película.")
print()

# Obtener peliculas por genero
genero = "Acción"
response = requests.get(f'http://localhost:5000/peliculas/{genero}')
peliculas = response.json()
if response.status_code == 200:
    print("Lista peliculas de acción:")
    for pelicula in peliculas:
        print(
            f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
else:
    print("Error al buscar peliculas por genero.")
print()

# Buscar pelicula por palabra
palabra = "The"
response = requests.get(
    f'http://localhost:5000/peliculas/buscar?titulo={palabra}')
peliculas = response.json()
if response.status_code == 200:
    print("Peliculas encontradas:")
    for pelicula in peliculas:
        print(
            f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
else:
    print("No se encontraron peliculas.")
print()

# Sugerir pelicula aleatoria
response = requests.get(f'http://localhost:5000/peliculas/sugerir')
pelicula = response.json()
if response.status_code == 200:
    print("La pelicula sugerida es:")
    print(
        f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
else:
    print("Error al sugerir pelicula")
print()

# Sugerir pelicula por género
genero = "Fantasía"
response = requests.get(f'http://localhost:5000/peliculas/sugerir/{genero}')
pelicula = response.json()
if response.status_code == 200:
    print(f"La pelicula sugerida de {genero} es:")
    print(
        f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
else:
    print(f"Error al sugerir pelicula de {genero}")
print()


# Agregar una nueva película
nueva_pelicula = {
    'titulo': 'Pelicula de prueba',
    'genero': 'Acción'
}
response = requests.post(
    f'http://localhost:5000/peliculas', json=nueva_pelicula)
if response.status_code == 201:
    pelicula_agregada = response.json()
    print("Película agregada:")
    print(
        f"ID: {pelicula_agregada['id']}, Título: {pelicula_agregada['titulo']}, Género: {pelicula_agregada['genero']}")
else:
    print("Error al agregar la película.")
print()

# Sugerir pelicula para un feriado
genero_buscado = {
    'genero': 'Acción',
    'tipo': 'None'
}
response = requests.post(
    f'http://127.0.0.1:5000/peliculas/sugerir', json=genero_buscado)
pelicula = response.json()
if response.status_code == 200:
    print(
        f"Pelicula sugerida para el feriado del dia {pelicula['dia']}/{pelicula['mes']}, con motivo {pelicula['motivo']} es:")
    print(f"Título: {pelicula['titulo']}")
else:
    print("Error al sugerir pelicula para un feriado")
print()

# Actualizar los detalles de una película
id_pelicula = 1  # ID de la película a actualizar
datos_actualizados = {
    'titulo': 'Nuevo título',
    'genero': 'Comedia'
}
response = requests.put(
    f'http://localhost:5000/peliculas/{id_pelicula}', json=datos_actualizados)
if response.status_code == 200:
    pelicula_actualizada = response.json()
    print("Película actualizada:")
    print(
        f"ID: {pelicula_actualizada['id']}, Título: {pelicula_actualizada['titulo']}, Género: {pelicula_actualizada['genero']}")
else:
    print("Error al actualizar la película.")
print()

# Eliminar una película
id_pelicula = 1  # ID de la película a eliminar
response = requests.delete(f'http://localhost:5000/peliculas/{id_pelicula}')
if response.status_code == 200:
    print("Película eliminada correctamente.")
else:
    print("Error al eliminar la película.")
