--Ejercicio 1)

--a)

data Carrera = Matematica | Fisica | Computacion | Astronomia deriving (Show)

--b)

titulo :: Carrera -> String

titulo Matematica = "Licenciatura en Matematica"
titulo Fisica = "Licenciatura en Fisica"
titulo Computacion = "Licenciatura en Ciencias de la Computacion"
titulo Astronomia = "Licenciatura en Astronomia"

--c) 

data NotaBasica = Do | Re | Mi | Fa | Sol | La | Si deriving (Eq, Ord, Show)

--d) 

cifradoAmericano :: NotaBasica -> Char

cifradoAmericano Do = 'C'
cifradoAmericano Re = 'D'
cifradoAmericano Mi = 'E'
cifradoAmericano Fa = 'F'
cifradoAmericano Sol = 'G'
cifradoAmericano La = 'A'
cifradoAmericano Si = 'B'

--Ejercicio 3)

--a)

minimoElemento :: Ord (a) => [a] -> a

minimoElemento [a] = a
minimoElemento (x:xs) = min x (minimoElemento xs)

--b)

minimoElemento' :: (Ord (a), Bounded (a)) => [a] -> a

minimoElemento' [] = minBound 
minimoElemento' [a] = a
minimoElemento' (x:xs) = min x (minimoElemento' xs)


--c)

-- Cuando probamos la funcion en haskell nos da:

-- minimoElemento [Fa, La, Sol, Re, Fa]
-- Re

--Ejercicio 4)

--a)

type Ingreso = Int

data Cargo = Titular | Asociado | Adjunto | Asistente | Auxiliar deriving (Show)

data Area = Administrativa | Ensenanza | Economica | Postgrado deriving (Show)

data Persona = Decane 
             | Docente Cargo 
             | NoDocente Area 
             | Estudiante Carrera Ingreso deriving (Show)
             
--b)

-- El constructor Docente es del tipo  Cargo -> Persona

--c)

--FUNCION AUXILIAR

cargosIguales :: (Cargo, Persona) -> Bool

cargosIguales (Titular, (Docente Titular)) = True
cargosIguales (Asociado, (Docente Asociado)) = True
cargosIguales (Adjunto, (Docente Adjunto)) = True
cargosIguales (Asistente, (Docente Asistente)) = True
cargosIguales (Auxiliar, (Docente Auxiliar)) = True
cargosIguales _  = False

cuantos_doc :: [Persona] -> Cargo -> Int

cuantos_doc [] c = 0
cuantos_doc (p:ps) c = case cargosIguales (c,p) of 
                            True ->  1 + cuantos_doc ps c
                            _ -> 0 + cuantos_doc ps c   

--d)

--FUNCION AUXILIAR

cargos :: Cargo -> Cargo -> Bool

cargos Titular Titular = True
cargos Asociado Asociado = True
cargos Adjunto Adjunto = True
cargos Asistente Asistente = True
cargos Auxiliar Auxiliar = True
cargos _ _ = False

--FUNCION AUXILIAR

cargosIguales' :: Persona -> Persona -> Bool

cargosIguales' (Docente a) (Docente b) = (cargos a b)
cargosIguales' _ _ = False

cuantos_doc' :: [Persona] -> Cargo -> Int 

cuantos_doc' [] c = 0
cuantos_doc' (xs) c = length (filter (cargosIguales' (Docente c)) xs)                      
                                
-- Ejercicio 5)

--a)

data Alteracion = Bemol | Sostenido | Natural 
data NotaMusical = Nota NotaBasica Alteracion

sonido :: NotaBasica -> Int
sonido Do = 1
sonido Re = 3
sonido Mi = 5
sonido Fa = 6
sonido Sol = 8
sonido La = 10
sonido Si = 12

--b)

--FUNCION AUXILIAR

alteraciones :: Alteracion -> Alteracion -> Bool

alteraciones Bemol Bemol = True
alteraciones Sostenido Sostenido = True
alteraciones Natural Natural = True
alteraciones _ _ = False

sonidoCromatico :: NotaMusical -> Int
sonidoCromatico (Nota n a) | alteraciones a Sostenido = sonido n + 1
                           | alteraciones a Bemol = sonido n - 1
                           | alteraciones a Natural = sonido n + 0
                   
--c)

instance Eq NotaMusical
  where
       n1 == n2 = sonidoCromatico n1 == sonidoCromatico n2
       
--d)

instance Ord NotaMusical
  where
       n1 <= n2 = sonidoCromatico n1 <= sonidoCromatico n2
       
-- Ejercicio 6)

--a)

primerElemento :: [a] -> Maybe a

primerElemento [] = Nothing
primerElemento (x:xs) = Just x

--Ejercicio 7)

data Cola = VaciaC | Encolada Persona Cola deriving (Show)

--a) 

--1.

atender :: Cola -> Maybe Cola

atender VaciaC = Nothing
atender (Encolada p ps) = Just ps

--2.

encolar :: Persona -> Cola -> Cola

encolar p VaciaC = (Encolada p VaciaC)
encolar p (Encolada x xs) = (Encolada x (encolar p xs))

--3.

--cargosIguales :: Cargo -> Persona -> Bool

--cargosIguales Titular (Docente Titular) = True
--cargosIguales Asociado (Docente Asociado) = True
--cargosIguales Adjunto (Docente Adjunto) = True
--cargosIguales Asistente (Docente Asistente) = True
--cargosIguales Auxiliar (Docente Auxiliar) = True
--cargosIguales _ _  = False

busca :: Cola -> Cargo -> Maybe Persona

busca VaciaC c = Nothing
busca (Encolada p ps) c = case cargosIguales (c, p) of 
                         True -> Just p
                         _ -> busca ps c
--b)

-- El tipo "Cola" se parece al tipo Lista, particularmente a una lista de personas.

--Ejercicio 8)

data ListaAsoc a b = Vacia | Nodo a b ( ListaAsoc a b ) deriving (Show)

type Diccionario = ListaAsoc String String
type Padron = ListaAsoc Int String

--a)

type GuiaTel = ListaAsoc String Int

--b)

--1.

la_long :: ListaAsoc a b -> Int

la_long Vacia = 0
la_long (Nodo a b l) = 1 + la_long l

--2.

la_concat :: ListaAsoc a b -> ListaAsoc a b -> ListaAsoc a b

la_concat Vacia Vacia = Vacia
la_concat Vacia (Nodo a b l) = (Nodo a b l)
la_concat (Nodo a b l) lista2 = (Nodo a b  (la_concat l lista2))
  
--Ejecución Manual                             
--la_concat (Nodo 1 2 (Nodo 2 3 Vacia)) (Nodo 4 5 Vacia)
--(Nodo 1 2 ( la_concat (Nodo 2 3 Vacia) (Nodo 4 5 Vacia))
--(Nodo 1 2 ( Nodo 2 3 (la_concat Vacia (Nodo 4 5 Vacia))))
--(Nodo 1 2 ( Nodo 2 3 (Nodo 4 5 Vacia)))

--3.

la_agregar :: ListaAsoc a b -> a -> b -> ListaAsoc a b

la_agregar Vacia a b = (Nodo a b Vacia)
la_agregar (Nodo a b l) c d = (Nodo c d (Nodo a b l))

--4.

la_pares :: ListaAsoc a b -> [(a, b)]

la_pares Vacia = []
la_pares (Nodo a b l) = (a, b): la_pares l

--5.

la_busca :: Eq a => ListaAsoc a b -> a -> Maybe b

la_busca Vacia a = Nothing
la_busca (Nodo c b l) a | a == c = Just b
                        | a /= c = la_busca l a

--6.

la_borrar :: Eq a => a -> ListaAsoc a b -> ListaAsoc a b

la_borrar a Vacia = Vacia
la_borrar a (Nodo c b l) | a == c = l                          
                         | a /= c = (Nodo c b (la_borrar a l))
                         
--Ejercicio 9)

data Arbol a = Hoja | Rama ( Arbol a ) a ( Arbol a ) deriving (Show)

type Prefijos = Arbol String
can , cana , canario , canas , cant , cantar , canto :: Prefijos
can = Rama cana "can" cant
cana = Rama canario "a" canas
canario = Rama Hoja "rio" Hoja
canas = Rama Hoja  "s" Hoja
cant = Rama cantar "t" canto
cantar = Rama Hoja "ar" Hoja
canto = Rama Hoja "o" Hoja      
                         
--a)

a_long :: Arbol a -> Int

a_long (Rama Hoja a Hoja) = 1
a_long (Rama Hoja a (Rama t c q)) = 1 + a_long (Rama t c q)
a_long (Rama (Rama r b s ) a Hoja) = 1 + a_long (Rama r b s)
a_long (Rama (Rama r b s ) a (Rama t c q)) = 1 + a_long (Rama r b s) + a_long (Rama t c q)

--b) 

a_hojas :: Arbol a -> Int

a_hojas Hoja = 1
a_hojas (Rama Hoja a Hoja) = 2
a_hojas (Rama Hoja a (Rama t c q)) = 1 + a_hojas (Rama t c q)
a_hojas (Rama (Rama r b s ) a Hoja) = 1 + a_hojas (Rama r b s)
a_hojas (Rama (Rama r b s ) a (Rama t c q)) = a_hojas (Rama r b s) + a_hojas (Rama t c q)

--c)

a_inc :: Num a => Arbol a -> Arbol a

a_inc (Rama Hoja a Hoja) = (Rama Hoja a Hoja)
a_inc (Rama Hoja a (Rama t c q)) = (Rama Hoja (a + 1) (a_inc (Rama t c q)))
a_inc (Rama (Rama r b s ) a Hoja) = (Rama (a_inc (Rama r b s )) (a + 1) Hoja)
a_inc (Rama (Rama r b s ) a (Rama t c q)) = (Rama (a_inc (Rama r b s )) (a + 1) (a_inc (Rama t c q)))

--d)

a_map :: (a -> b) -> Arbol a -> Arbol b

a_map f (Rama Hoja a Hoja) = (Rama Hoja (f a) Hoja)
a_map f (Rama Hoja a (Rama t c q)) = (Rama Hoja (f a) (a_map f (Rama t c q)))
a_map f (Rama (Rama r b s ) a Hoja) = (Rama (a_map f (Rama r b s )) (f a) Hoja)
a_map f (Rama (Rama r b s ) a (Rama t c q)) = (Rama (a_map f (Rama r b s )) (f a) (a_map f (Rama t c q)))

a_inc' :: Num a => Arbol a -> Arbol a

a_inc' (Rama Hoja a Hoja) = a_map (+1) (Rama Hoja a Hoja)
a_inc' (Rama Hoja a (Rama t c q)) = a_map (+1) (Rama Hoja a (Rama t c q))
a_inc' (Rama (Rama r b s ) a Hoja) = a_map (+1) (Rama (Rama r b s ) a Hoja)
a_inc' (Rama (Rama r b s ) a (Rama t c q)) = a_map (+1) (Rama (Rama r b s ) a (Rama t c q))
