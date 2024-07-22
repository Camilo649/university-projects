-- Ejercicio 1)

--a)
esCero :: Int -> Bool

esCero a = a == 0

--b)

esPositivo :: Int -> Bool

esPositivo a = a > 0

--c)

esVocal :: Char -> Bool

esVocal a = a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u'

--esVocalBis :: Char -> Bool
--esVocalBis a = elem a "aeiou"

-- Ejercicio 2)

--a)

paratodo :: [Bool] -> Bool

paratodo [] = True
paratodo (x:xs) | x == True = paratodo xs
                | otherwise = False
                
--b)

sumatoria :: [Int] -> Int

sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria xs

--c) 

productoria :: [Int] -> Int

productoria [] = 1
productoria (x:xs) = x * productoria xs

--d)

factorial :: Int -> Int

factorial 0 = 1
factorial n = n * factorial (n-1) 

--e)

promedio :: [Int] -> Int

promedio [] = 0
promedio xs = div (sumatoria xs) (length xs)

-- Ejercicio 3)

pertenece :: Int -> [Int] -> Bool

pertenece n [] = False
pertenece n (x:xs) | x == n = True
                   | x /= n = pertenece n xs 

--pertenece n xs | elem n xs = True
--	           | otherwise = False 

-- Ejercicio 4)

-- a)

paratodo' :: [a] -> (a -> Bool) -> Bool

paratodo' [] t = True
paratodo' (x:xs) t = t x && paratodo' xs t

-- b) 

existe' :: [a] -> (a -> Bool) -> Bool

existe' [] t = False
existe' (x:xs) t = t x || existe' xs t

-- c)

sumatoria' :: [a] -> (a -> Int) -> Int

sumatoria' [] t = 0
sumatoria' (x:xs) t = t x + sumatoria' xs t

-- d)
productoria' :: [a] -> (a -> Int) -> Int

productoria' [] t = 1
productoria' (x:xs) t = t x * productoria' xs t

-- Ejercicio 5)

paratodo'' :: [Bool] -> Bool

paratodo'' xs = paratodo' xs id

-- Ejercicio 6)

-- a)

todosPares :: [Int] -> Bool

todosPares xs = paratodo' xs even

-- b)

mult n x = mod x n == 0


hayMultiplo :: Int -> [Int] -> Bool

hayMultiplo n xs = existe' xs (mult n)

-- c)

sumaCuadrados :: Int -> Int

sumaCuadrados n = sumatoria' [0..n] (^2)

--d)

factorial' :: Int -> Int

factorial' n = productoria [n,n-1..1]

--e) 

-- FUNCION AUXILIAR
sacaPares :: [Int] -> [Int]
sacaPares [] = []
sacaPares (x:xs) | (mod x 2) == 0 = x: sacaPares xs 
                 | otherwise = sacaPares xs 
                 
multiplicaPares :: [Int] -> Int

multiplicaPares xs = productoria' (sacaPares xs) id

-- Ejercicio 7)

-- ¿Qué hacen estas funciones?
--map es una función que toma dos argumentos. El primero de esos argumentos es una función que se aplica al segundo argumento el cual es una lista. Finalmente, nos devuelve una lista con los elementos una vez aplicada la función de manera ordenada
--filter es una función que toma dos argumentos. El primero es un predicado, osea una función del tipo (a -> Bool), que se encarga de verificar que los elementos del segundo argumento, el cual es una lista, cumplan con una determinada condición. Finalmente, devuelve una lista con los elementos que cumlieron con e dicha condición.

-- ¿A qué equivale la expresión map succ [1, -4, 6, 2, -8], donde succ n = n+1?
--[2, -3, 7, 3, -7]

-- ¿Y la expresión filter esPositivo [1, -4, 6, 2, -8]?
-- [1, 6, 2]

-- Ejercicio 8)

--a)

duplicar :: [Int] -> [Int]

duplicar [] = []
duplicar (x:xs) = 2*x : duplicar xs

--b)

duplicar' :: [Int] -> [Int]

duplicar' xs = map (2*) xs

--Ejercicio 9)

-- a)

soloPares :: [Int] -> [Int]

soloPares [] = []
soloPares (x:xs) | (mod x 2) == 0 = x: soloPares xs
                 | (mod x 2) /= 0 = soloPares xs
                
--b) 

soloPares' :: [Int] -> [Int]

soloPares' xs = filter even xs

--c)

multiplicaPares' :: [Int] -> Int

multiplicaPares' xs = productoria' (filter even xs) id

-- Ejercicio 10)

--a)

primIgualesA :: Eq (a) => a -> [a] -> [a]

primIgualesA n [] = []
primIgualesA n (x:xs) | (n == x) = x : primIgualesA n xs
                      | otherwise = [] 

--b)

primIgualesA' :: Eq (a) => a -> [a] -> [a]

primIgualesA' n xs = takeWhile (n ==) xs

--Ejercicio 11)

--a)

primIguales :: Eq (a) => [a] -> [a]

primIguales [] = []
primIguales (y:x:xs) | (y == x) = x : primIguales (x:xs)
                     | otherwise = [y]   

--b)

primIguales' :: Eq (a) => [a] -> [a]

primIguales' [] = []
primIguales' (x:xs) | (x == x) = primIgualesA' x (x:xs)
                    | (x /= x) = []
                      
--Ejercicio 12 (*)

cuantGen :: (b -> b -> b) -> b -> [a] -> (a -> b) -> b

cuantGen op z [] t = z
cuantGen op z (x:xs) t = op(t x) (cuantGen op z xs t)

paratodo''' :: [a] -> (a -> Bool) -> Bool

paratodo''' xs t = cuantGen (&&) True xs t

existe''' :: [a] -> (a -> Bool) -> Bool

existe''' xs t = cuantGen (||) False xs t

sumatoria''' :: [a] -> (a -> Int) -> Int

sumatoria''' xs t = cuantGen (+) 0 xs t

productoria''' :: [a] -> (a -> Int) -> Int

productoria''' xs t = cuantGen (*) 1 xs t

-- EJERCICIO 13 (*)

--a)
--f :: (a, b) ->  a
--f (x , y) =  x

-- Si esta bien tipado. Tipo : tupla. Cubre todos los casos.

--b)
--f :: [(a, b)] -> ...
--f (a , b) = ...

-- Esta mal tipado. Toma una lista de tuplas y no una tupla.

--c)
--f :: [(a, b)] -> [(a, b)]
--f (x:xs) = [x]


-- Esta bien tipado. Tipo: lista de tuplas. No cubre el caso de lista vacia.

--d)
--f :: [(a, b)] ->  [(a, b)]
--f ((x, y) : ((a, b) : xs)) = [(x, y)]

-- Esta bien tipado. Tipo: lista de tuplas con al mneos dos elementos. No cubre el caso de la lista vacia ni de la lista que tiene solo una tupla.

--e)
--f :: [(Int, a)] -> (Int, a)
--f [(0, a)] = (0, a) 

-- Esta bien tipado. Tipo: lista de tuplas donde el primer elemento es un entero. Unicamente cubre el caso donde el entero es 0 y donde la lista tiene una sola tupla.

--f) 
--f :: [(Int, a)] -> ...
--f ((x, 1) : xs) =  ...

-- Esta mal tipado. Liga al segundo elemento a ser entero (1) cuando puede ser de cualquier otro tipo.

--g)
--f :: (Int -> Int) -> Int -> Int
--f a b =  a b

-- Esta bien tipado. Tipo: una funcion que toma y devuelve un entero, y un entero. Cubre todos los casos.

--h)
--f :: (Int -> Int) -> Int -> Int
--f a 3 = (a 3) + 3

-- Esta bien tipado. Tipo: una funcion que toma y devuelve un entero, y un entero. Cubre unicamente el caso donde el entero es 3.

-- i)
--f :: (Int -> Int) -> Int -> ...
--f 0 1 2 = ...

-- Esta mal tipado. Tendría que tomar una función en el primer término y toma un entero (0.

-- EJERCICIO 14 (*)

--a)

funcionA :: (a, b) -> b

funcionA (x,y) = y

--b)

--funcionB :: (a, b) -> c

-- Es imposible dar una definicion que tome una tupla de dos elementos distintos y devuelva algo de otro tipo ya que no hay un operador generico.

--c)

funcionC :: (a -> b) -> a -> b

funcionC t x = t x

--d) 

funcionD :: (a -> b) -> [a] -> [b]

funcionD t xs = map t xs

--FORMA ALTERNATIVA

funcionD' :: (a -> b) -> [a] -> [b]

funcionD' t [] = []
funcionD' t (x:xs) = (t x) : funcionD' t xs

--e)

funcionE :: (a -> b) -> (b -> c) -> a -> c

funcionE t p x = p (t x) 
