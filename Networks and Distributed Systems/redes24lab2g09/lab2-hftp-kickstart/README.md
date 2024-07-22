## Lab 2 - Redes y Sistemas Distribuidos
### Estructura del servidor

El servidor está organizado en tres partes principales:

### Servidor

Se encarga de inicializarse y estar en espera de las solicitudes de conexión de los clientes. Por defecto, utiliza el puerto 19500. Cuando llega una solicitud, se crea un objeto de conexión y un nuevo hilo para procesarla. Una vez que el hilo termina, es decir, cuando se completa la conexión con ese cliente, el hilo se cierra.

### Manejador de conexiones

Su función es recibir las solicitudes de los clientes, procesarlas y enviar respuestas adecuadas. Este componente también gestiona posibles errores que puedan surgir durante la comunicación con los clientes.

### Constantes

Este archivo auxiliar contiene las constantes utilizadas en la implementación del servidor.

## Decisiones de diseño tomadas

### Servidor

- Se crea el directorio compartido en caso de que no exista, para evitar fallos por su ausencia.
- Se emplea un hilo por cada conexión con un cliente para permitir al servidor atender a varios clientes simultáneamente. Esta elección se hizo en favor de la eficiencia, ya que los hilos comparten memoria y son más simples de implementar que los procesos hijos o el uso de un servidor asíncrono.
- Los errores fatales no cierran el servidor, sino que solo desconectan al cliente que los generó, permitiendo que el servidor siga atendiendo a otros clientes.

### Constantes

- Se define `MAX_BUFFER_SIZE` en `2**32` para gestionar comandos maliciosos de gran longitud que podrían afectar el rendimiento del servidor.
- Se define `NEWLINE` como `\n` para detectar el carácter `\n` fuera de un terminador de pedido `\r\n` y notificar al cliente el error 100 (BAD EOL) y cerrar la conexión.

### Manejador de conexiones

- Se utiliza un objeto `Connection` con varios atributos para gestionar la conexión con el cliente, facilitando el código.
- Se modulariza el código en funciones para mejorar la legibilidad y mantenimiento del mismo.

#### Funciones específicas:

- `self.header`: Se encarga de enviar el encabezado de la respuesta al cliente y, en caso de código terminal, finaliza la conexión.
- `self.valid_file`: Verifica la existencia del archivo que se quiere enviar al cliente para evitar errores en los comandos `get_metadata` y `get_slice`.
- `self.command_selector`: Selecciona y ejecuta el comando deseado, verificando su validez y la de sus argumentos. Maneja errores mediante try-except para casos como `ConnectionResetError` o `BrokenPipeError`.
- `self._recv`: Similar a la función en `client.py`, pero con ajustes para manejar errores específicos y devolver el código de error 101 (BAD REQUEST) en caso de mensajes inválidos.
- `self.handle`: Función principal que gestiona la conexión con el cliente y mantiene el hilo activo. Se ejecuta un ciclo mientras la conexión esté activa, llamando a `self.read_line` para recibir datos y procesarlos. Si la conexión se interrumpe, el ciclo y el hilo se cierran.

### Estrategias para implementar un servidor que atienda múltiples clientes simultáneamente:

Existen tres estrategias para implementar un servidor que pueda atender múltiples clientes simultáneamente:

#### 1. Multiples hilos:
En este enfoque, cada vez que se recibe una petición de un cliente, se crea un nuevo hilo que se encarga de atender la petición. Este hilo se encarga de leer las peticiones del cliente, procesarlas y responderle. Una vez que el hilo termina su ejecución, se destruye.

#### 2. Creación de hijos:
En este caso, cada vez que se recibe una petición de un cliente, se crea un nuevo proceso hijo que se encarga de atender la petición. Este proceso hijo se encarga de leer las peticiones del cliente, procesarlas y responderle. Una vez que el proceso hijo termina su ejecución, se destruye. Esta estrategia es similar a la anterior pero tiene la diferencia de que al generar un nuevo proceso hijo, se genera un nuevo espacio de memoria.

#### 3. Async server:
En este caso, se utilizan técnicas de programación asincrónicas para procesar múltiples solicitudes de manera eficiente sin bloquear el hilo de ejecución. En lugar de crear un hilo de ejecución para cada cliente y dentro del hilo esperar a que cada operación se complete, se registra una función de devolución de llamada (callback) que se ejecutará una vez que se complete la operación. Con esta estrategia, el servidor puede procesar múltiples solicitudes en paralelo sin necesidad de un gran número de hilos de ejecución, lo que lo hace más eficiente y escalable que las estrategias anteriores.

### Cambios necesarios en el diseño del código para implementar cada una de estas estrategias:

#### Multiples hilos:
Modificar el código para que cada vez que se reciba una petición de un cliente, se cree un nuevo hilo que se encargue de atenderlo y se destruya una vez que se cierre la conexión. La gestión de los hilos se puede realizar utilizando la librería `threading` de Python.

#### Creación de hijos:
Modificar el código para que cada vez que se reciba una petición de un cliente, se cree un nuevo proceso hijo que se encargue de atenderlo y se destruya una vez que se cierre la conexión. La gestión de los procesos hijos se puede realizar utilizando la librería `multiprocessing` de Python.

#### Async server:
Utilizar la librería `asyncio` de Python y rehacer gran parte del código del proyecto para utilizar una arquitectura basada en eventos. Se debería crear un loop de eventos que se encargue de manejar las conexiones de los clientes y las peticiones que estos realizan.

### Diferencias al correr el servidor desde diferentes direcciones IP:

- **localhost**: El servidor solo puede ser accedido desde la misma máquina en la que se está ejecutando. Es una dirección IP que se utiliza para referirse a la propia máquina.
  
- **127.0.0.1**: Es equivalente a localhost y se refiere a la dirección IP reservada que se usa para comunicarse con la misma máquina a través de la red. Es decir, el servidor solo es accesible desde la misma máquina en la que se está ejecutando.

- **0.0.0.0**: El servidor puede ser accedido desde cualquier máquina de la red. Es una dirección IP que se utiliza para referirse a cualquier interfaz de red disponible en la máquina. Cuando se le dice a un servidor que escuche en 0.0.0.0, significa "escuchar en cada interfaz de red disponible".

### Preguntas

- 1. ¿Qué estrategias existen para poder implementar este mismo servidor pero con capacidad de atender múltiples clientes simultáneamente? Investigue y responda brevemente qué cambios serían necesarios en el diseño del código.

- Existen básicamente dos formas: usar multihilos o usar poll (ambas implementadas en este laboratorio).
  En la versión multihilos dejamos que el sistema operativo maneje la conexión entrante independientemente de lo que en ella se solicite y vamos chequeando constantemente si hay información que extraer del socket.
  Por su parte, cuando trabajamos con poll no estamos interactuando todo el tiempo con los sockets, sino que es el sistema operativo el encargado de avisarnos cuando se produce un nuevo evento del tipo que nosotros estamos esperando, lo que nos otorga más libertad para manejar las conexiones pudiendo darles más prioridad a cierto tipo de eventos que a otros.

- 2. Pruebe ejecutar el servidor en una máquina del laboratorio, mientras utiliza el cliente desde otra, hacia la ip de la máquina servidor. ¿Qué diferencia hay si se corre el servidor desde la IP “localhost”, “127.0.0.1” o la ip “0.0.0.0”?

- Pudimos efectuar la conexión cuando conectamos el servidor a "localhost" y a "0.0.0.0" pero no en "127.0.0.1". Esto sucede porque la dirección ip 127.0.0.1 sólo permite utilizar esta dirección localmente, lo que no pasa cuando usamos localhost que si permite que otros hosts se conecten a la dirección local por medio de Internet o 0.0.0.0 que lo hace para la red local pero no es utilizable en internet porque no es una dirección ip válida.