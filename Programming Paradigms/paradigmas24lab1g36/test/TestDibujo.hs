module Main (main) where
import Dibujo
import Test.HUnit 

-- Tests para la función figuras
testFiguras :: Test
testFiguras = TestList [
    "figura" ~: figuras (figura (1 :: Int)) ~?= [1],
    "figura" ~: figuras (rotar (figura (1 :: Int))) ~?= [1],
    "figura" ~: figuras (espejar (figura (1 :: Int))) ~?= [1],
    "figura" ~: figuras (rot45 (figura (1 :: Int))) ~?= [1],
    "figura" ~: figuras (apilar 1 1 (figura (1 :: Int)) (figura (2 :: Int))) ~?= [1, 2],
    "figura" ~: figuras (juntar 1 1 (figura (1 :: Int)) (figura (2 :: Int))) ~?= [1, 2],
    "figura" ~: figuras (encimar (figura (1 :: Int)) (figura (2 :: Int))) ~?= [1, 2]
    ]

-- Tests para la función foldDib
testFoldDib :: Test
testFoldDib = TestList [
    "foldDib" ~: foldDib id id id id (\_ _ a _ -> a) (\_ _ a _ -> a) (\a _ -> a) (figura (1 :: Int)) ~?= 1,
    "foldDib" ~: foldDib id id id id (\_ _ a _ -> a) (\_ _ a _ -> a) (\a _ -> a) (rotar (figura (1 :: Int))) ~?= 1,
    "foldDib" ~: foldDib id id id id (\_ _ a _ -> a) (\_ _ a _ -> a) (\a _ -> a) (espejar (figura (1 :: Int))) ~?= 1,
    "foldDib" ~: foldDib id id id id (\_ _ a _ -> a) (\_ _ a _ -> a) (\a _ -> a) (rot45 (figura (1 :: Int))) ~?= 1,
    "foldDib" ~: foldDib id id id id (\_ _ a _ -> a) (\_ _ a _ -> a) (\a _ -> a) (apilar 1 1 (figura (1 :: Int)) (figura (2 :: Int))) ~?= 1,
    "foldDib" ~: foldDib id id id id (\_ _ a _ -> a) (\_ _ a _ -> a) (\a _ -> a) (juntar 1 1 (figura (1 :: Int)) (figura (2 :: Int))) ~?= 1,
    "foldDib" ~: foldDib id id id id (\_ _ a _ -> a) (\_ _ a _ -> a) (\a _ -> a) (encimar (figura (1 :: Int)) (figura (2 :: Int))) ~?= 1
    ]

-- Tests para la función mapDib
testMapDib :: Test
testMapDib = TestList [
    "mapDib" ~: mapDib (+ 1) (figura (1 :: Int)) ~?= figura 2,
    "mapDib" ~: mapDib (+ 1) (rotar (figura (1 :: Int))) ~?= rotar (figura 2),
    "mapDib" ~: mapDib (+ 1) (espejar (figura (1 :: Int))) ~?= espejar (figura 2),
    "mapDib" ~: mapDib (+ 1) (rot45 (figura (1 :: Int))) ~?= rot45 (figura 2),
    "mapDib" ~: mapDib (+ 1) (apilar 1 1 (figura (1:: Int)) (figura (2 :: Int))) ~?= apilar 1 1 (figura 2) (figura 3),
    "mapDib" ~: mapDib (+ 1) (juntar 1 1 (figura (1 :: Int)) (figura (2 :: Int))) ~?= juntar 1 1 (figura 2) (figura 3),
    "mapDib" ~: mapDib (+ 1) (encimar (figura (1 :: Int)) (figura (2 :: Int))) ~?= encimar (figura 2) (figura 3)
    ]

-- Tests para la función change
testChange :: Test
testChange = TestList [
    "change" ~: change (\x -> figura (x + 1)) (figura (1 :: Int)) ~?= figura 2,
    "change" ~: change (\x -> figura (x + 1)) (rotar (figura (1 :: Int))) ~?= rotar (figura 2),
    "change" ~: change (\x -> figura (x + 1)) (espejar (figura (1 :: Int))) ~?= espejar (figura 2),
    "change" ~: change (\x -> figura (x + 1)) (rot45 (figura (1 :: Int))) ~?= rot45 (figura 2),
    "change" ~: change (\x -> figura (x + 1)) (apilar 1 1 (figura (1 :: Int)) (figura (2 :: Int))) ~?= apilar 1 1 (figura 2) (figura 3),
    "change" ~: change (\x -> figura (x + 1)) (juntar 1 1 (figura (1 :: Int)) (figura (2 :: Int))) ~?= juntar 1 1 (figura 2) (figura 3),
    "change" ~: change (\x -> figura (x + 1)) (encimar (figura (1 ::Int)) (figura (2 :: Int))) ~?= encimar (figura 2) (figura 3)
    ]

-- Tests para la función figuras_gen
testFigurasGen :: Test
testFigurasGen = TestList [
    "figuras_gen" ~: figuras_gen (figura (1 :: Int)) [] ~?= [1],
    "figuras_gen" ~: figuras_gen (rotar (figura (1 :: Int))) [] ~?= [1],
    "figuras_gen" ~: figuras_gen (espejar (figura (1 :: Int))) [] ~?= [1],
    "figuras_gen" ~: figuras_gen (rot45 (figura (1 :: Int))) [] ~?= [1],
    "figuras_gen" ~: figuras_gen (apilar 1 1 (figura (1 :: Int)) (figura (2 :: Int))) [] ~?= [1, 2],
    "figuras_gen" ~: figuras_gen (juntar 1 1 (figura (1 :: Int)) (figura (2 :: Int))) [] ~?= [1, 2],
    "figuras_gen" ~: figuras_gen (encimar (figura (1 :: Int)) (figura (2 ::  Int))) [] ~?= [1, 2]
    ]

-- Tests para la función cuarteto

testCuarteto :: Test
testCuarteto = TestList [
    "cuarteto" ~: cuarteto (figura (1 :: Int)) (figura (2 :: Int)) (figura (3 :: Int)) (figura (4 :: Int)) ~?= (figura 1 /// figura 2) .-. (figura 3 /// figura 4),
    "cuarteto" ~: cuarteto (figura (2 :: Int)) (figura (3 :: Int)) (figura (4 :: Int)) (figura (5 :: Int)) ~?= (figura 2 /// figura 3) .-. (figura 4 /// figura 5)
    ]

-- Tests para la función ciclar

testCiclar :: Test
testCiclar = TestList [
    "ciclar" ~: ciclar (figura (1 :: Int)) ~?= cuarteto (figura 1) (r90 $ figura 1) (r180 $ figura 1) (r270 $ figura 1),
    "ciclar" ~: ciclar (figura (2 :: Int)) ~?= cuarteto (figura 2) (r90 $ figura 2) (r180 $ figura 2) (r270 $ figura 2)
    ]

-- Tests para la función encimar4

testEncimar4 :: Test
testEncimar4 = TestList [
    "encimar4" ~: encimar4 (figura (1 :: Int)) ~?= rotar (rotar (rotar (figura 1))) ^^^ (rotar (rotar (figura 1)) ^^^ (rotar (figura 1) ^^^ (figura 1))),
    "encimar4" ~: encimar4 (figura (2 :: Int)) ~?= rotar (rotar (rotar (figura 2))) ^^^ (rotar (rotar (figura 2)) ^^^ (rotar (figura 2) ^^^ (figura 2)))
    ]

-- Tests para la función r90

testR90 :: Test
testR90 = TestList [
    "r90" ~: r90 (figura (1 :: Int)) ~?= rotar (figura 1),
    "r90" ~: r90 (figura (2 :: Int)) ~?= rotar (figura 2)
    ]

-- Tests para la función r180

testR180 :: Test
testR180 = TestList [
    "r180" ~: r180 (figura (1 :: Int)) ~?= rotar (rotar (figura 1)),
    "r180" ~: r180 (figura (2 :: Int)) ~?= rotar (rotar (figura 2))
    ]

-- Tests para la función r270

testR270 :: Test
testR270 = TestList [
    "r270" ~: r270 (figura (1 :: Int)) ~?= rotar (rotar (rotar (figura 1))),
    "r270" ~: r270 (figura (2 :: Int)) ~?= rotar (rotar (rotar (figura 2)))
    ]


-- Corre los tests de Dibujo.hs
main :: IO Counts
main = runTestTT $ TestList [testFiguras, testFoldDib, testMapDib, testChange, testFigurasGen, testCiclar, testCuarteto, 
                            testR90, testR180, testR270, testEncimar4]