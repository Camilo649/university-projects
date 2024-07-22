---
title: Laboratorio de Programación Orientada a Objetos
author: Camilo Guitiérrez, Lucas Nieto.
---

El enunciado del laboratorio se encuentra en [este link](https://docs.google.com/document/d/1wLhuEOjhdLwgZ4rlW0AftgKD4QIPPx37Dzs--P1gIU4/edit#heading=h.xe9t6iq9fo58).

# 1. Tareas
Pueden usar esta checklist para indicar el avance.

## Verificación de que pueden hacer las cosas.
- [x] Java 17 instalado. Deben poder compilar con `make` y correr con `make run` para obtener el mensaje de ayuda del programa.

## 1.1. Interfaz de usuario
- [x] Estructurar opciones
- [x] Construir el objeto de clase `Config`

## 1.2. FeedParser
- [x] `class Article`
    - [x] Atributos
    - [x] Constructor
    - [x] Método `print`
    - [x] _Accessors_
- [x] `parseXML`

## 1.3. Entidades nombradas
- [x] Pensar estructura y validarla con el docente
- [x] Implementarla
- [x] Extracción
    - [x] Implementación de heurísticas
- [x] Clasificación
    - [x] Por tópicos
    - [x] Por categorías
- Estadísticas
    - [x] Por tópicos
    - [x] Por categorías
    - [x] Impresión de estadísticas

## 1.4 Limpieza de código
- [x] Pasar un formateador de código
- [x] Revisar TODOs

# 2. Experiencia
En una primera instancia, nos resultó abrumador el hecho de pensar toda estructura
compleja como un objeto. Estábamos acostumbrados a definir estructuras en C pero tener
clases para las cuales solo usamos sus métodos y no tener meras funciones en un archivo
aparte que satisfagan las mismas necesidades escapaba de nuestra forma habitual de
resolver problemas. Asimismo nos vimos envueltos en incertidumbre al momento de decidir
cuando era conveniente crear un objeto desde cero o cuando conveía más hacer que herede
de una superclase y al momento de determinar si usar una interfaz para definir un
comportamiento o optar por tener una clase abstracta con ciertas implementaciones
comunes a sus clases hijas. También nos pareció un poco engorroso la necesidad de tener
una clase pública por archivo y no poder tener varias relacionadas en un mismo fichero.
  Llegando al final del laboratorio y tras hablar y recibir ayuda de docentes y
compañeros creemos haber obtenido un cierto grado de visibilidad respecto a las
facilidades y el poder de expresión que trae un lenguaje del paradigma orientado a
objetos, considerándolo útil como lenguaje de propósito general.
  Nuestra manera de trabajar fue principalmente los viernes en el laboratorio de la
facultad, organizándonos vía Whatsapp cuando hacía falta y trabajando cooperativamente
a través de GoogleMeet para concretar lo que nos faltó en la presencialidad.

# 3. Preguntas
1. Explicar brevemente la estructura de datos elegida para las entidades nombradas.

Las entidades nombradas son del tipo class NamedEntity. Dicha clase es de visibilidad 
publica y se compone por cinco variables de clase con niveles de visibilidad
privados y metódos publicos, de tal forma que solo se puede interactuar con dichos 
campos por medio de sus metódos asociados. Las variables de clase son:

- Name: nombre asociado a la entidad nombrada, sirve como identificador.
- Topics: lista de topicos asociados. Una vez creada la clase, se puden agregar más
tópicos con el método addTopics
- KeyWords: lista de palabras clave, es como si fueran nombres alternativos. En el lab, 
se utilizan para poder asociar palabras a entidades nombradas con nombres similares. 
Al igual que Topics tambien puede incorporar nuevas palabras luego de crearse la instancia.
- counter: contador de entidad. Se utiliza para llevar las apariciones de entidades 
nombradas en el texto.
- Category: se refiere a su tipo de categoria asociado. Esta variable es del tipo 
class Category, una clase abstracta que cuenta con un indentificador de tipo que solamente 
puede ser instanciado por sus clases derivadas. Sus hijas son :
            
    **LOCATION:** permite tener la longitud y latitud de una ubicación.
    
    **ORGANIZATION:** alamacena el tipo de organización (por ej. 'gubernamental').
    
    **PERSON:** almacena información de una persona, como su nombre formal y edad. 
    
    **OTHER:** esta clase se utiliza para clasificar a aquellas entidades que no caen
            dentro de ninguno de los tipos de categorias anteriores.

> Las entidades nombradas se crean a partir de las entradas de dictionary.json

2. Explicar brevemente cómo se implementaron las heurísticas de extracción.

Nos pareció útil definir una clase abstracta *Heuristic* que implemente funciones comunes
a cada heurística y que también les obligue a tener un comportamiento definidio mediante
el uso de métodos abstractos.
  La heurística *NoPrefixDotCapHeuristic* acepta palabras que empiecen con mayúscula
siempre que estas no vayan inmediatamente después de un punto. La motivación fue eliminar
la gran cantidad de falsos positivos que generaba la heurística original pero a coste de
perder, en menor cantidad, algunas entidades nombradas.
  Por su parte, la heurística *FilterCapHeuristic* no descarta ningún positivo verdadero
encontrado por la heurística original y logra eliminar en gran medidad el total de falsos
positivos mediante una lista de palabas a filtrar. Las desventaja de esta heurística es
que requiere de más cómputo y memoria que las anteriores.

# 4. Extras

Agregamos una funcionalidad extra al campo las opciones, si se ejecuta make con el 
argumento '-f' se puede especificar mas de un feed a procesar.  