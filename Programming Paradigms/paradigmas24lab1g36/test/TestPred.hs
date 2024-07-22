module Main (main) where
import Pred
import Dibujo
import Test.HUnit 

testPred :: Test
testPred = TestList [
    "cambiar" ~: cambiar (== 1) (2 :: Int) (figura (1 :: Int)) ~?= (figura (2 :: Int)),
    "anyDib" ~: anyDib (== 1) (figura (1 :: Int)) ~?= True,
    "allDib" ~: allDib (== 1) (figura (1 :: Int)) ~?= True,
    "andP" ~: andP (== 1) (== 1) (1 :: Int) ~?= True,
    "orP" ~: orP (== 1) (== 1) (1 :: Int) ~?= True,
    "falla" ~: falla ~?= True
    ]

-- Corre los tests de Pred.hs
main :: IO Counts
main = runTestTT testPred