---
title: Laboratorio de Funcional
author: Lucas Nieto, Agustín Melo, Camilo Gutiérrez
---
La consigna del laboratorio está en https://tinyurl.com/funcional-2024-famaf

# 1. Tareas
Pueden usar esta checklist para indicar el avance.

## Verificación de que pueden hacer las cosas.
- [x] Haskell instalado y testeos provistos funcionando. (En Install.md están las instrucciones para instalar.)

## 1.1. Lenguaje
- [x] Módulo `Dibujo.hs` con el tipo `Dibujo` y combinadores. Puntos 1 a 3 de la consigna.
- [x] Definición de funciones (esquemas) para la manipulación de dibujos.
- [x] Módulo `Pred.hs`. Punto extra si definen predicados para transformaciones innecesarias (por ejemplo, espejar dos veces es la identidad).

## 1.2. Interpretación geométrica
- [x] Módulo `Interp.hs`.

## 1.3. Expresión artística (Utilizar el lenguaje)
- [x] El dibujo de `Dibujos/Feo.hs` se ve lindo.
- [x] Módulo `Dibujos/Grilla.hs`.
- [x] Módulo `Dibujos/Escher.hs`.
- [x] Listado de dibujos en `Main.hs`.

## 1.4 Tests
- [x] Tests para `Dibujo.hs`.
- [x] Tests para `Pred.hs`.

# 2. Experiencia

Los viernes, dentro del horario de clases buscamos solucionar nuestras dudas con los profesores, y el resto de días trabajamos de forma coordinada, compartiendo ideas por medio de WhatsApp y coordinando reuniones de meet cuando nos trababamos con algún problema.

# 3. Preguntas
Al responder tranformar cada pregunta en una subsección para que sea más fácil de leer.

1. ¿Por qué están separadas las funcionalidades en los módulos indicados? Explicar detalladamente la responsabilidad de cada módulo.
2. ¿Por qué las figuras básicas no están incluidas en la definición del lenguaje, y en vez de eso, es un parámetro del tipo?
3. ¿Qué ventaja tiene utilizar una función de `fold` sobre hacer pattern-matching directo?
4. ¿Cuál es la diferencia entre los predicados definidos en Pred.hs y los tests?

## ¿Por qué están separadas las funcionalidades en los módulos indicados?

Las funcionalidades estan separadas por m'odulos para así armar un proyecto mejor estructurado e intuitivo, incluso para programadores ajenos al proyecto que deseen realizar sus propios dibujos.

Además, el modularizar funcionalidades nos brindó un camino a seguir a la hora de realizar el proyecto y nos permitió testear todo aquello que agregabamos conforme avanzabamos en el mismo. Esto último, hizo más fácil la tarea de indentificar errores, sobre todo en las instanciancias finales.

Las funciones que desempeña cada módulo son las siguientes:

- `Dibujos.hs` : Posee el tipo Dibujo con constructores recursivos que representan rotar, encimar, rot45, espejar, juntar, apilar y el elemento base que toma un parámetro de tipo (polimorfismo). Además tiene funciones que buscan simplificar la legibilidad del código, evitando repeticiones innecesarias, y nuestras dos funciones de orden superior: mapDib y folDib (similares a map y fold pero para dibujos). 

```haskell
data Dibujo a = Figura a | Rotar (Dibujo a) | Espejar (Dibujo a)
    | Rot45 (Dibujo a)
    | Apilar Float Float (Dibujo a) (Dibujo a)
    | Juntar Float Float (Dibujo a) (Dibujo a)
    | Encimar (Dibujo a) (Dibujo a)
    deriving (Eq, Show)
```

- `Pred.hs` : Ofrece funciones de predicados en dibujos para corroborar propiedades de los mismos.

- `FloatingPic.hs`: Brinda funciones y tipos de datos para trabajar con vectores. Entre dichos tipos `Conf`, que almacena un dibujo, su nombre y la interpretación geométrica de sus figuras básicas. 

- `Interp.hs` : Son funciones que describen la interpretación geométrica de los constructores de dibujo utlizando Gloss.

- `Dibujos/Feo.hs` : Da una configuración que, en función de la interpretación de los constructores, describe una imagen, en este caso: [imagen_feo](https://drive.google.com/file/d/1pZcl3CG6MR_gIjUscRBGvsrQubVcH7kt/view?usp=sharing)

- `Dibujos/Grilla.hs` : Similar a Dibujos/Feo.hs, pero en este caso la interpretación de figuras basicas describe una grilla de coordenadas: [image_grilla](https://drive.google.com/file/d/1-O9_LurZZnaVJEWoZSas-kSqFYKvQypT/view?usp=sharing)

- `Dibujos/Escher.hs` : Brinda una configuración que describe la figura 16 del [articulo](https://cs.famaf.unc.edu.ar/~mpagano/henderson-funcgeo2.pdf) de Peter Henderson, con un nivel de profundidad ajustable: [imagen_escher_n=2](https://drive.google.com/file/d/1hLgI4rKpYsm1Lqjw9FPB1iH4EpRhu-YE/view?usp=sharing) y [imagen_escher_n=5](https://drive.google.com/file/d/1MOmBhQPNWjgc4TS5dPWXdnVCzH_QAb7R/view?usp=sharing)

- `Main.hs`: Es el modulo que nuclea al resto, donde se utilizan las configuración de cada dibujo para mostrar por pantalla las imagenes correspondiente a cada uno.

- `test/TestDibujo.hs` : Batería de test para las funciones definidas en Dibujo.hs.

- `test/TestGloss.hs` : Testea que la librería Gloss funcione correctamente.

- `test/TestHaha.hs` : Verifica si se puede utilizar la biblioteca `haha` correctamente.

- `test/TestPred.hs` : Batería de test para las funciones definidas en Pred.hs.

## ¿Por qué las figuras básicas no están incluidas en la definición del lenguaje, y en vez de eso, es un parámetro del tipo?

La definición del lenguaje no incluye un tipo específico para las figuras básicas, en su lugar usa un parámetro de tipo. Esto permite tener funciones polimórficas, es decir, no dependen de un tipo concreto, pueden ser ajustadas a cualquiera, lo que le da libertad al programador de definir dibujos diversos.

Esto último, puede ser aprovechado a la hora de crear interpretaciones básicas, pues dependiendo de las figuras que querramos plasmar podrían convenir más algunos tipos que otros. 

Por ej. en Escher queriamos mostrar triángulos y espacios en blanco (blank), por lo que resulto conveniente el tipo `Bool` (True para triángulos y False para blank), pero en Grilla debimos trabajar con cordenadas por lo que nos parecio buena idea tener un tipo `(Int, Int)`, y esto no generó ningún problema de tipos debido a la definción del lenguaje.   

## ¿Qué ventaja tiene utilizar una función de `fold` sobre hacer pattern-matching directo?

- **Código más limpio y legible**: Al utilizar `fold` se evita la repetición de código y se permite la reutilización de este. Como su propia implementación utiliza pattern-matching, la función que utilice `foldDib` no requiere hacer reursión en los contructores del tipo Dibujo.

- **Mayor abstracción**: `fold` permite abstraer la recursión de los constructores de Dibujo, permitiendo que el programador se enfoque en la lógica de la función que se está implementando.

- **Flexibilidad**: La función de `fold` permite al usuario proporcionar funciones específicas para cada constructor de la estructura de datos. Esto hace que el comportamiento de la función sea altamente personalizable y adaptable a diferentes necesidades.

## ¿Cuál es la diferencia entre los predicados definidos en Pred.hs y los tests?

Mientras que los tests se encargan de verificar la semántica correcta para las funciones y que las librerías se desempeñen adecuadamente, los predicados definidos en Pred.hs tienen el potencial de hacer mucho más como puede ser: utilizarse en guardas para definir el flujo de control del programa, crear un dibujo completamente diferente al cambiar determinadas figuras básicas por otras, etc. Todas estás funcionalidades permiten crear dibujos dinámicos, los cuales dan pie a animaciones.

Los tests no forman parte de la funcionalidad del código en sí. En contraste, los predicados de Pred están destinados a proporcionar funciones sobre dibujos genéricos otrogando una flexibilidad que se ajusta a las necesidades del programador.

# 4. Extras
Completar si hacen algo.