# Configuracion del entorno

-Crea un entorno virtual de Python utilizando venv.
python3 - m venv .venv

-En lugar de .venv puede ser cualquier nombre, pero es un estándar

-Activa el entorno virtual
source .venv/bin/activate

-Para desactivarlo
deactivate

-Con el venv activo vamos a instalar las librerías necesarias.

pip install - r requirements.txt

El archivo requirements.txt enumera las dependencias y las versiones específicas de los paquetes que tu aplicación necesita. Esto instalará todas las dependencias especificadas en el archivo requirements.txt en tu entorno virtual, asegurando que tu aplicación tenga acceso a las versiones correctas de los paquetes necesarios.

¿Por que usar un entorno virtual para ejecutar una aplicacion?

Usar un entorno virtual en Python es una práctica recomendada para evitar problemas de compatibilidad entre las dependencias de diferentes proyectos. Aquí hay algunas razones por las que es importante usar un entorno virtual:

Isolación de dependencias: Cada entorno virtual tiene su propia copia de las bibliotecas y dependencias del proyecto, lo que evita conflictos entre versiones de bibliotecas que pueden ser necesarias para diferentes proyectos.

Reproducibilidad del entorno: Al tener un archivo requirements.txt que lista todas las dependencias y sus versiones específicas, otro desarrollador(o tú mismo en el futuro) puede crear un entorno virtual idéntico con solo ejecutar pip install - r requirements.txt.

Facilidad para probar diferentes versiones de paquetes: Puedes probar diferentes versiones de una biblioteca en un entorno virtual sin afectar a otros proyectos que puedas tener en la misma máquina.

Aislamiento del sistema: Un entorno virtual no afecta al sistema operativo subyacente, lo que significa que puedes probar y desarrollar aplicaciones sin preocuparte por alterar la configuración global de Python en tu máquina.

En resumen, usar un entorno virtual te permite trabajar de manera más segura y organizada, evitando problemas potenciales con las dependencias de tus proyectos.

# API y su ejecucion

Este código implementa una API simple utilizando Flask, un framework de Python para construir aplicaciones web. La API permite realizar operaciones CRUD(Crear, Leer, Actualizar, Eliminar) en una lista de películas almacenadas en memoria. Aquí hay un resumen de lo que hace cada función:

obtener_peliculas(): Devuelve la lista completa de películas en formato JSON.

obtener_pelicula(id): Devuelve los detalles de una película específica según su ID en formato JSON.

agregar_pelicula(): Agrega una nueva película a la lista de películas. Los detalles de la nueva película se obtienen de los datos enviados en la solicitud POST.

actualizar_pelicula(id): Actualiza los detalles de una película existente según su ID. Los nuevos detalles se obtienen de los datos enviados en la solicitud PUT.

eliminar_pelicula(id): Elimina una película de la lista según su ID.

obtener_nuevo_id(): Utilidad para generar un nuevo ID para una película basándose en el último ID de la lista.

El código también establece las rutas URL para cada función de la API y ejecuta la aplicación Flask en el servidor local si el archivo se ejecuta directamente. La API se ejecutará en http: // 127.0.0.1: 5000 / y responderá a las solicitudes HTTP GET, POST, PUT y DELETE en las rutas / peliculas y / peliculas/<id > , donde < id > es el ID de la película.

app.add_url_rule() se utiliza para asociar las funciones con las rutas URL específicas y los métodos HTTP correspondientes. Por ejemplo, la primera línea(app.add_url_rule('/peliculas', 'obtener_peliculas', obtener_peliculas, methods=['GET'])) agrega una regla de URL para la ruta / peliculas que llama a la función obtener_peliculas() cuando se realiza una solicitud GET a esa ruta.

Al ejecutar el archivo Python que contiene este código(main.py), Flask comenzará a escuchar en http: // 127.0.0.1: 5000 / y responderá a las solicitudes HTTP según las rutas y métodos definidos. Puedes probar la API utilizando herramientas como postman o curl para enviar solicitudes GET, POST, PUT y DELETE a las rutas / peliculas y / peliculas/<id >

La dirección IP 127.0.0.1 se refiere a la dirección de "localhost". Esta dirección IP se utiliza para referirse al propio dispositivo en el que se está ejecutando el software. Cuando una aplicación Flask(o cualquier servidor web) se ejecuta en 127.0.0.1, significa que la aplicación solo será accesible desde el mismo dispositivo en el que se está ejecutando.

El puerto 5000 es el puerto estándar en el que Flask suele ejecutarse de forma predeterminada.

Por lo tanto, al escuchar en http: // 127.0.0.1: 5000 /, la aplicación Flask solo estará disponible para las solicitudes que se realicen desde el mismo dispositivo en el que se está ejecutando la aplicación.

Para ejecutar la API, una vez activo el entorno virtual hacemos lo siguiente:
python3 main.py

# Solicitudes y consultas

Puedes utilizar la herramienta CURL para enviar solicitudes HTTP a la aplicación Flask, y ésta responderá realizando las operaciones correspondientes sobre la lista de películas en memoria. Por ejemplo:

Puedes enviar una solicitud GET a / peliculas para obtener la lista completa de películas.
Puedes enviar una solicitud GET a / peliculas/<id > para obtener los detalles de una película específica.
Puedes enviar una solicitud POST a / peliculas con los datos de una nueva película para agregarla a la lista.
Puedes enviar una solicitud PUT a / peliculas/<id > con los nuevos datos de una película para actualizarla.
Puedes enviar una solicitud DELETE a / peliculas/<id > para eliminar una película de la lista.

Estas solicitudes HTTP se procesarán en la aplicación Flask y se realizarán las operaciones correspondientes sobre la lista de películas en memoria.

La sintaxis para realizar las consultas con CURL son:

Obtener todas las películas(GET):
curl http: // 127.0.0.1: 5000/peliculas

Obtener una película por su ID(GET):
curl http: // 127.0.0.1: 5000/peliculas/1

Agregar una nueva película(POST):
curl - X POST http: // 127.0.0.1: 5000/peliculas - H "Content-Type: application/json" - d '{"titulo": "Nueva Película", "genero": "Drama"}'

Actualizar una película por su ID(PUT):
curl - X PUT http: // 127.0.0.1: 5000/peliculas/1 - H "Content-Type: application/json" - d '{"titulo": "Nuevo Título"}'

Eliminar una película por su ID(DELETE):
curl - X DELETE http: // 127.0.0.1: 5000/peliculas/1

Mas solicitudes disponibles en la API:

Una solicitud GET a / peliculas/<genero > para obtener una lista con las peliculas que pertenecen al genero especificado
Una solicitud GET a / peliculas/buscar para obtener una lista de peliculas que en su titulo contengan o coincidan con la busqueda.
Una solicitud GET a / peliculas/sugerir para obtener una pelicula sugerida aleatoriamente.
Una solicitud GET a / peliculas/sugerir/<genero > para obtener una pelicula sugerida aleatoriamente del genero especificado.
Una solicitud GET a / peliculas/sugerir/feriado/<genero > para obtener una pelicula sugerida aleatoriamente para ver en el proximo feriado calendario.

La sintaxis de estas consultas con CURL son las siguientes:

Obtener todas las peliculas pertenecientes a un genero especifico(GET):
curl http: // 127.0.0.1: 5000/peliculas/Drama

Obtener todas las peliculas que contengan o coincidan con la busqueda(GET):
curl http: // 127.0.0.1: 5000/peliculas/buscar?titulo = India

Obtener una pelicula aleatoria(GET):
curl http: // 127.0.0.1: 5000/peliculas/sugerir

Obtener una pelicula aleatoria por genero(GET):
curl http: // 127.0.0.1: 5000/peliculas/sugerir/Drama

Obtener una pelicula aleatoria por genero en el proximo feriado calendario(POST):
curl - X POST http: // 127.0.0.1: 5000/peliculas/sugerir - H "Content-Type: application/json" - d '{"genero": "Acción", "tipo": "None"}'
En esta solicitud es opcional poner el tipo de feriado. Si usted pone la constante None, por defecto le devolvera el feriado mas proximo independientemente del tipo.

La ultima solicitud trabaja con otra API a la cual consulta y obtiene el proximo feriado calendario.

Para realizar las consultas tendremos que abrir otra terminal o consola y realizar estas consultas alli, no donde estemos ejecutando la API main.py.
