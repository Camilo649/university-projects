module Pred (
    Pred,
    cambiar, 
    anyDib,
    allDib, 
    orP, 
    andP,
    falla, 
    ) where

import Dibujo

type Pred a = a -> Bool

-- Dado un predicado sobre básicas, cambiar todas las que satisfacen
-- el predicado por la figura básica indicada por el segundo argumento.
cambiar :: Pred a -> a -> Dibujo a -> Dibujo a
cambiar p y dibujo = mapDib (\x -> if p x then y else x) dibujo

-- Alguna básica satisface el predicado.
anyDib :: Pred a -> Dibujo a -> Bool
anyDib p dibujo = foldDib p (|| False) (|| False) (|| False) (\_ _ a b -> a || b) (\_ _ a b -> a || b) (||) dibujo

-- Todas las básicas satisfacen el predicado.
allDib :: Pred a -> Dibujo a -> Bool
allDib p dibujo = foldDib p (&& True) (&& True) (&& True) (\_ _ a b -> a && b) (\_ _ a b -> a && b) (&&) dibujo

-- Los dos predicados se cumplen para el elemento recibido.
andP :: Pred a -> Pred a -> Pred a
andP p1 p2 x = (p1 x) && (p2 x)

-- Algún predicado se cumple para el elemento recibido.
orP :: Pred a -> Pred a -> Pred a
orP p1 p2 x = (p1 x) || (p2 x)

falla :: Bool
falla = True
