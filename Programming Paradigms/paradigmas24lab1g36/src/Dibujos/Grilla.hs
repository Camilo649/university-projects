module Dibujos.Grilla (
    grilla,
    grillaConf
) where

import Dibujo (Dibujo, juntar, apilar, figura)
import FloatingPic(Conf(..), Output)
import Graphics.Gloss (text, translate, scale)
--usar text, translate, scale y testGrilla

type Basica = (Int, Int)

interpBas :: Output Basica
interpBas tup (x, y) _ _ = translate (x+29.7) (y+43.1) $ scale 0.15 0.15 $ text $ show tup

row :: [Dibujo a] -> Dibujo a
row [] = error "row: no puede ser vacío"
row [d] = d
row (d:ds) = juntar 1 (fromIntegral $ length ds) d (row ds)

column :: [Dibujo a] -> Dibujo a
column [] = error "column: no puede ser vacío"
column [d] = d
column (d:ds) = apilar 1 (fromIntegral $ length ds) d (column ds)

grilla :: [[Dibujo a]] -> Dibujo a
grilla = column . map row

testAll :: Dibujo Basica
testAll = grilla 
   (map (\y -> (map (\x -> figura (y, x)) [0..7])) [0..7])

grillaConf :: Conf 
grillaConf = Conf {
    name = "Grilla"
    , pic = testAll
    , bas = interpBas
}