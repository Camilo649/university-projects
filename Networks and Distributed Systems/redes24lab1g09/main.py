import random
import json  # Importamos esta librería para poder impirmir carcateres no ASCII
# Importamos esta librería para poder poder trabajar con caracteres unicode
from unidecode import unidecode
from proximo_feriado import NextHoliday
from flask import Flask, request

app = Flask(__name__)
peliculas = [
    {'id': 1, 'titulo': 'Indiana Jones', 'genero': 'Acción'},
    {'id': 2, 'titulo': 'Star Wars', 'genero': 'Acción'},
    {'id': 3, 'titulo': 'Interstellar', 'genero': 'Ciencia ficción'},
    {'id': 4, 'titulo': 'Jurassic Park', 'genero': 'Aventura'},
    {'id': 5, 'titulo': 'The Avengers', 'genero': 'Acción'},
    {'id': 6, 'titulo': 'Back to the Future', 'genero': 'Ciencia ficción'},
    {'id': 7, 'titulo': 'The Lord of the Rings', 'genero': 'Fantasía'},
    {'id': 8, 'titulo': 'The Dark Knight', 'genero': 'Acción'},
    {'id': 9, 'titulo': 'Inception', 'genero': 'Ciencia ficción'},
    {'id': 10, 'titulo': 'The Shawshank Redemption', 'genero': 'Drama'},
    {'id': 11, 'titulo': 'Pulp Fiction', 'genero': 'Crimen'},
    {'id': 12, 'titulo': 'Fight Club', 'genero': 'Drama'}
]


def obtener_peliculas():
    return json.dumps(peliculas, ensure_ascii=False, indent=4)


def obtener_peliculas_genero(genero):
    # Lógica que devuelve todas las peliculas de un genero
    peliculas_del_genero = []
    for pelicula in peliculas:
        if unidecode(pelicula["genero"]) == unidecode(genero):
            peliculas_del_genero.append(pelicula)
    return json.dumps(peliculas_del_genero, ensure_ascii=False, indent=4)


def obtener_pelicula(id):
    # Lógica para buscar la película por su ID y devolver sus detalles
    pelicula_encontrada = next(
        pelicula for pelicula in peliculas if pelicula["id"] == id)
    return json.dumps(pelicula_encontrada, ensure_ascii=False)


def buscar_pelicula():
    # Lógica que devuelve todas las peliculas que coincidan con search
    coincidencias = []
    titulo = request.args.get('titulo')
    for pelicula in peliculas:
        if titulo in pelicula["titulo"]:
            coincidencias.append(pelicula)
    return json.dumps(coincidencias, ensure_ascii=False, indent=4)


def agregar_pelicula():
    nueva_pelicula = {
        'id': obtener_nuevo_id(),
        'titulo': request.json['titulo'],
        'genero': request.json['genero']
    }
    peliculas.append(nueva_pelicula)
    print(peliculas)  # Imprime la lista de manera ordenada
    return json.dumps(nueva_pelicula, ensure_ascii=False), 201


def actualizar_pelicula(id):
    # Lógica para buscar la película por su ID y actualizar sus detalles
    pelicula_actualizada = next(
        pelicula for pelicula in peliculas if pelicula["id"] == id)
    if "titulo" in request.json:
        pelicula_actualizada["titulo"] = request.json["titulo"]
    if "genero" in request.json:
        pelicula_actualizada["genero"] = request.json["genero"]
    return json.dumps(pelicula_actualizada, ensure_ascii=False)


def eliminar_pelicula(id):
    # Lógica para buscar la película por su ID y eliminarla
    pelicula_eliminada = next(
        pelicula for pelicula in peliculas if pelicula["id"] == id)
    peliculas.remove(pelicula_eliminada)
    return json.dumps({'mensaje': 'Película eliminada correctamente'}, ensure_ascii=False)


def sugerir_pelicula():
    # Lógica para devolver una pelicula aleatoria
    return json.dumps(random.choice(peliculas), ensure_ascii=False)


def sugerir_pelicula_genero(genero):
    # Lógica para devolver una pelicula aleatoria en base a genero
    peliculas_del_genero = []
    for pelicula in peliculas:
        if unidecode(pelicula["genero"]) == unidecode(genero):
            peliculas_del_genero.append(pelicula)
    return json.dumps(random.choice(peliculas_del_genero), ensure_ascii=False)


def sugerir_pelicula_feriado():
    # Lógica para devolver una pelicula aleatoria en base a genero y el próximo feriado de cierto tipo
    if "tipo" in request.json:
        genero = request.json["genero"]
    peliculas_del_genero = []
    for pelicula in peliculas:
        if pelicula["genero"] == genero:
            peliculas_del_genero.append(pelicula)
    próximo_feriado = NextHoliday()
    if "tipo" in request.json:
        tipo = request.json["tipo"]
    próximo_feriado.fetch_holidays(tipo)
    día = próximo_feriado.holiday['dia']
    mes = próximo_feriado.holiday['mes']
    motivo = próximo_feriado.holiday['motivo']
    titulo = random.choice(peliculas_del_genero)['titulo']
    return json.dumps({"dia": día, "mes": mes, "motivo": motivo, "titulo": titulo}, ensure_ascii=False)


def obtener_nuevo_id():
    if len(peliculas) > 0:
        # Accede a la ultima pelicula en la lista y devuelve su ID
        ultimo_id = peliculas[-1]['id']
        return ultimo_id + 1
    else:
        return 1


app.add_url_rule('/peliculas', 'obtener_peliculas',
                 obtener_peliculas, methods=['GET'])
app.add_url_rule('/peliculas/<int:id>', 'obtener_pelicula',
                 obtener_pelicula, methods=['GET'])
app.add_url_rule('/peliculas/<string:genero>', 'obtener_peliculas_genero',
                 obtener_peliculas_genero, methods=['GET'])
# Llamar con curl http://127.0.0.1:5000/peliculas/buscar?titulo=strign_a_buscar
app.add_url_rule('/peliculas/buscar', 'buscar_pelicula',
                 buscar_pelicula, methods=['GET'])
app.add_url_rule('/peliculas/sugerir', 'sugerir_pelicula',
                 sugerir_pelicula, methods=['GET'])
app.add_url_rule('/peliculas/sugerir/<string:genero>',
                 'sugerir_pelicula_genero', sugerir_pelicula_genero, methods=['GET'])
app.add_url_rule('/peliculas', 'agregar_pelicula',
                 agregar_pelicula, methods=['POST'])
app.add_url_rule('/peliculas/sugerir', 'sugerir_pelicula_feriado',
                 sugerir_pelicula_feriado, methods=['POST'])
app.add_url_rule('/peliculas/<int:id>', 'actualizar_pelicula',
                 actualizar_pelicula, methods=['PUT'])
app.add_url_rule('/peliculas/<int:id>', 'eliminar_pelicula',
                 eliminar_pelicula, methods=['DELETE'])

if __name__ == '__main__':
    app.run()
