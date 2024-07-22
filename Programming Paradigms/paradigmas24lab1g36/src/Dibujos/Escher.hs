module Dibujos.Escher where

import Dibujo (Dibujo, figura, juntar, apilar, rot45, rotar, encimar, espejar, cuarteto, encimar4, r270)
import Graphics.Gloss (blank, line, pictures)
import qualified Graphics.Gloss.Data.Point.Arithmetic as V
import FloatingPic(Conf(..), Output, zero)

-- Supongamos que eligen.
type Escher = Bool

interpBas :: Output Escher
interpBas False _ _ _ = blank
interpBas True a b c = pictures [line $ triangulo a b c]
  where
    triangulo x y z = map (x V.+) [zero, z, y, zero]


-- El dibujo u.
dibujoU :: Dibujo Escher -> Dibujo Escher
dibujoU p = encimar4 (triangulo2)
    where 
        triangulo2 = espejar (rot45 p)

-- El dibujo t.
dibujoT :: Dibujo Escher -> Dibujo Escher
dibujoT p = encimar p (encimar triangulo2 triangulo3)
    where 
        triangulo2 = espejar (rot45 p)
        triangulo3 = r270 (triangulo2)

-- Esquina con nivel de detalle en base a la figura p.
esquina :: Int -> Dibujo Escher -> Dibujo Escher
esquina 0 _ = figura False
esquina n p = cuarteto (esquina (n-1) p) (lado (n-1) p) (rotar(lado (n-1) p)) (dibujoU p)

-- Lado con nivel de detalle.
lado :: Int -> Dibujo Escher -> Dibujo Escher
lado 0 _ = figura False
lado n p = cuarteto (lado (n-1) p) (lado (n-1) p) (rotar(dibujoT p)) (dibujoT p)

noneto :: Dibujo a -> Dibujo a -> Dibujo a -> Dibujo a -> Dibujo a -> Dibujo a -> Dibujo a -> 
          Dibujo a -> Dibujo a -> Dibujo a
noneto p q r s t u v w x = apilar 1 2 (juntar 1 2 p (juntar 1 1 q r))
                            (apilar 1 1 (juntar 1 2 s (juntar 1 1 t u))
                            (juntar 1 2 v $ juntar 1 1 w x))

-- El dibujo de Escher:
escher :: Int -> Escher -> Dibujo Escher
escher n p = noneto (esquina n (figura p)) 
            (lado n (figura p))
            (rotar $ rotar $ rotar $ esquina n (figura p))
            (rotar $ lado n (figura p)) 
            (dibujoU $ figura p) 
            (rotar $ rotar $ rotar $ lado n (figura p))
            (rotar $ esquina n (figura p))
            (rotar $ rotar $ lado n (figura p))
            (rotar $ rotar $ esquina n (figura p))

escherConf :: Conf
escherConf = Conf {
    name = "Escher"
    , pic = escher 5 True
    , bas = interpBas 
}