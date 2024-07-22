import requests
import pytest
import requests_mock


@pytest.fixture
def mock_response():
    with requests_mock.Mocker() as m:
        # Simulamos la respuesta para obtener todas las películas
        m.get('http://localhost:5000/peliculas', json=[
            {'id': 1, 'titulo': 'Indiana Jones', 'genero': 'Acción'},
            {'id': 2, 'titulo': 'Star Wars', 'genero': 'Acción'},
        ])

        # Simulamos la respuesta para agregar una nueva película
        m.post('http://localhost:5000/peliculas', status_code=201,
               json={'id': 3, 'titulo': 'Pelicula de prueba', 'genero': 'Acción'})

        # Simulamos la respuesta para obtener detalles de una película específica
        m.get('http://localhost:5000/peliculas/1',
              json={'id': 1, 'titulo': 'Indiana Jones', 'genero': 'Acción'})

        # Simulamos la respuesta para obtener las peliculas de determinado genero
        m.get('http://localhost:5000/peliculas/Acción', json=[
            {'id': 1, 'titulo': 'Indiana Jones', 'genero': 'Acción'},
            {'id': 2, 'titulo': 'Star Wars', 'genero': 'Acción'}
        ])

        # Simulamos la respuesta para buscar una pelicula determinada
        m.get('http://localhost:5000/peliculas/buscar?titulo=India',
              json={'id': 1, 'titulo': 'Indiana Jones', 'genero': 'Acción'})

        # Simulamos la respuesta para obtener una pelicula sugerida aleatoriamente
        m.get('http://localhost:5000/peliculas/sugerir',
              json={'id': 2, 'titulo': 'Star Wars', 'genero': 'Acción'})

        # Simulamos la respuesta para obtener una pelicula sugerida según genero
        m.get('http://localhost:5000/peliculas/sugerir/Acción',
              json={'id': 2, 'titulo': 'Star Wars', 'genero': 'Acción'})

        # Simulamos la respuesta para obtener una pelicula sugerida según genero para el próximo feriado
        m.post('http://localhost:5000/peliculas/sugerir', json={"dia": 29,
                                                                "mes": 3, "motivo": "Viernes Santo Festividad Cristiana",
                                                                "titulo": "Pulp Fiction"})

        # Simulamos la respuesta para actualizar los detalles de una película
        m.put('http://localhost:5000/peliculas/1', status_code=200,
              json={'id': 1, 'titulo': 'Nuevo título', 'genero': 'Comedia'})

        # Simulamos la respuesta para eliminar una película
        m.delete('http://localhost:5000/peliculas/1', status_code=200)

        yield m


def test_obtener_peliculas(mock_response):
    response = requests.get('http://localhost:5000/peliculas')
    assert response.status_code == 200
    assert len(response.json()) == 2


def test_obtener_detalle_pelicula(mock_response):
    response = requests.get('http://localhost:5000/peliculas/1')
    assert response.status_code == 200
    assert response.json()['titulo'] == 'Indiana Jones'


def test_obtener_peliculas_genero(mock_response):
    response = requests.get('http://localhost:5000/peliculas/Acción')
    assert response.status_code == 200
    assert response.json()[0]['genero'] == 'Acción'
    assert len(response.json()) == 2


def test_buscar_pelicula(mock_response):
    response = requests.get(
        'http://localhost:5000/peliculas/buscar?titulo=India')
    assert response.status_code == 200
    assert response.json()['titulo'] == 'Indiana Jones'


def test_sugerir_pelicula(mock_response):
    response = requests.get('http://localhost:5000/peliculas/sugerir')
    assert response.status_code == 200
    assert len(response.json()) == 3


def test_sugerir_pelicula_genero(mock_response):
    response = requests.get('http://localhost:5000/peliculas/sugerir/Acción')
    assert response.status_code == 200
    assert response.json()['genero'] == 'Acción'


def test_sugerir_pelicula_feriado(mock_response):
    genero_buscado = {'genero': 'Crimen', 'tipo': 'None'}
    response = requests.post(
        'http://localhost:5000/peliculas/sugerir', json=genero_buscado)
    assert response.status_code == 200
    assert len(response.json()) == 4


def test_agregar_pelicula(mock_response):
    nueva_pelicula = {'titulo': 'Pelicula de prueba', 'genero': 'Acción'}
    response = requests.post(
        'http://localhost:5000/peliculas', json=nueva_pelicula)
    assert response.status_code == 201
    assert response.json()['id'] == 3


def test_actualizar_detalle_pelicula(mock_response):
    datos_actualizados = {'titulo': 'Nuevo título', 'genero': 'Comedia'}
    response = requests.put(
        'http://localhost:5000/peliculas/1', json=datos_actualizados)
    assert response.status_code == 200
    assert response.json()['titulo'] == 'Nuevo título'


def test_eliminar_pelicula(mock_response):
    response = requests.delete('http://localhost:5000/peliculas/1')
    assert response.status_code == 200
