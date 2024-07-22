module Dibujo (
    Dibujo,
    encimar, 
    figura,
    apilar,
    juntar,
    rot45,
    rotar,
    espejar,
    r90,
    r180,
    r270,
    encimar4,
    cuarteto,
    ciclar,
    mapDib,
    change,
    foldDib,
    figuras,
    figuras_gen,
    (^^^),
    (.-.),
    (///)
    ) where


-- nuestro lenguaje 
data Dibujo a = Figura a | Rotar (Dibujo a) | Espejar (Dibujo a)
  | Rot45 (Dibujo a)
  | Apilar Float Float (Dibujo a) (Dibujo a)
  | Juntar Float Float (Dibujo a) (Dibujo a)
  | Encimar (Dibujo a) (Dibujo a)
  deriving (Eq, Show)

-- combinadores
infixr 6 ^^^

infixr 7 .-.

infixr 8 ///

comp :: Int -> (a -> a) -> a -> a 
comp n f x
  | n <= 0    = x
  | n == 1    = f x
  | otherwise = f (comp (n - 1) f x)



-- Funciones constructoras
figura :: a -> Dibujo a
figura = Figura

encimar :: Dibujo a -> Dibujo a -> Dibujo a
encimar = Encimar

apilar :: Float -> Float -> Dibujo a -> Dibujo a -> Dibujo a
apilar = Apilar

juntar  :: Float -> Float -> Dibujo a -> Dibujo a -> Dibujo a
juntar = Juntar

rot45 :: Dibujo a -> Dibujo a
rot45 = Rot45

rotar :: Dibujo a -> Dibujo a
rotar = Rotar

espejar :: Dibujo a -> Dibujo a
espejar = Espejar 

(^^^) :: Dibujo a -> Dibujo a -> Dibujo a
(^^^) a b = encimar a b 

(.-.) :: Dibujo a -> Dibujo a -> Dibujo a
(.-.) a b = apilar 1.0 1.0 a b

(///) :: Dibujo a -> Dibujo a -> Dibujo a
(///) a b = juntar 1.0 1.0 a b 

-- rotaciones
r90 :: Dibujo a -> Dibujo a
r90 d = rotar d  

r180 :: Dibujo a -> Dibujo a
r180 d = comp 2 r90 d

r270 :: Dibujo a -> Dibujo a
r270 d = comp 3 r90 d

-- una figura repetida con las cuatro rotaciones, superimpuestas.
encimar4 :: Dibujo a -> Dibujo a
encimar4 d = (r270 d) ^^^ ((r180 d) ^^^ ((r90 d) ^^^ d))

-- cuatro figuras en un cuadrante.
cuarteto :: Dibujo a -> Dibujo a -> Dibujo a -> Dibujo a -> Dibujo a
cuarteto a b c d = (a /// b) .-. (c /// d) 

-- un cuarteto donde se repite la imagen, rotada (¡No confundir con encimar4!)
ciclar :: Dibujo a -> Dibujo a
ciclar d = cuarteto d (r90 d) (r180 d) (r270 d)

-- map para nuestro lenguaje
mapDib :: (a -> b) -> Dibujo a -> Dibujo b
mapDib f (Figura a) = Figura (f a)
mapDib f (Rotar a) = Rotar (mapDib f a)
mapDib f (Espejar a) = Espejar (mapDib f a)
mapDib f (Rot45 a) = Rot45 (mapDib f a)
mapDib f (Apilar n m a b) = Apilar n m (mapDib f a) (mapDib f b)
mapDib f (Juntar n m a b) = Juntar n m (mapDib f a) (mapDib f b)
mapDib f (Encimar a b) = Encimar (mapDib f a) (mapDib f b)
-- verificar que las operaciones satisfagan
-- 1. map figura = id
-- 2. map (g . f) = mapDib g . mapDib f

-- Cambiar todas las básicas de acuerdo a la función.
change :: (a -> Dibujo b) -> Dibujo a -> Dibujo b
change f (Figura a) = f a
change f (Rotar a) = Rotar (change f a)
change f (Espejar a) = Espejar (change f a)
change f (Rot45 a) = Rot45 (change f a)
change f (Apilar n m a b) = Apilar n m (change f a) (change f b)
change f (Juntar n m a b) = Juntar n m (change f a) (change f b)
change f (Encimar a b) = Encimar (change f a) (change f b)

-- Principio de recursión para Dibujos.
foldDib ::
  (a -> b) ->
  (b -> b) ->
  (b -> b) ->
  (b -> b) ->
  (Float -> Float -> b -> b -> b) ->
  (Float -> Float -> b -> b -> b) ->
  (b -> b -> b) ->
  Dibujo a ->
  b
foldDib fFigura fRotar fEspejar fRot45 fApilar fJuntar fEncimar dibujo = case dibujo of
  Figura a        -> fFigura a
  Rotar d         -> fRotar (foldDib fFigura fRotar fEspejar fRot45 fApilar fJuntar fEncimar d)
  Espejar d       -> fEspejar (foldDib fFigura fRotar fEspejar fRot45 fApilar fJuntar fEncimar d)
  Rot45 d         -> fRot45 (foldDib fFigura fRotar fEspejar fRot45 fApilar fJuntar fEncimar d)
  Apilar x y d1 d2 -> fApilar x y (foldDib fFigura fRotar fEspejar fRot45 fApilar fJuntar fEncimar d1) (foldDib fFigura fRotar fEspejar fRot45 fApilar fJuntar fEncimar d2)
  Juntar x y d1 d2 -> fJuntar x y (foldDib fFigura fRotar fEspejar fRot45 fApilar fJuntar fEncimar d1) (foldDib fFigura fRotar fEspejar fRot45 fApilar fJuntar fEncimar d2)
  Encimar d1 d2   -> fEncimar (foldDib fFigura fRotar fEspejar fRot45 fApilar fJuntar fEncimar d1) (foldDib fFigura fRotar fEspejar fRot45 fApilar fJuntar fEncimar d2)

figuras :: Dibujo a -> [a]
figuras dibujo = figuras_gen dibujo []

figuras_gen :: Dibujo a -> [a] -> [a]
figuras_gen (Figura a) xs = a : xs
figuras_gen (Rotar a) xs = figuras_gen a xs
figuras_gen (Espejar a) xs = figuras_gen a xs
figuras_gen (Rot45 a) xs = figuras_gen a xs
figuras_gen (Apilar _ _ a b) xs = figuras_gen a xs ++ figuras_gen b xs
figuras_gen (Juntar _ _ a b) xs =  figuras_gen a xs ++ figuras_gen b xs
figuras_gen (Encimar a b) xs = figuras_gen a xs ++ figuras_gen b xs

