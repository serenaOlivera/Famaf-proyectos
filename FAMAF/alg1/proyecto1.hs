import Data.List (iterate')
--Preguntas:
-- Ejercicio 6 e, porque el 2 no es primo?
-- Pregunar si aunque en las funciones que tenemos que definir no se puede usar recursion ni casos, ¿podemos usarlos en las funciones que definimos para que ande?

--Ejercicio 1 

-- a)
esCero :: Int -> Bool
esCero x | x == 0 = True
         | x /= 0 = False

--Ejemplos
-- esCero 0
-- True
-- esCero 7
-- False


-- b)
esPositivo :: Int -> Bool
esPositivo x | x > 0 = True 
             |x <= 0 = False

-- Ejemplos 
-- ghci> esPositivo (-6)
-- False
-- ghci> esPositivo 4
-- True


-- c)
esMinuscula :: Char -> Bool
esMinuscula j = j == 'a' || j == 'e' || j== 'i' || j=='o' || j=='u'

-- Ejemplos
-- esMinuscula 'j'
-- False
-- ghci> esMinuscula 'A'
-- False
-- ghci> esMinuscula 'i'
-- True 


--d)
valorAbsoluto :: Int -> Int
valorAbsoluto t | t >= 0 = t 
                | t < 0 = -t

--Ejemplos
--ghci> valorAbsoluto 5
--5
--ghci> valorAbsoluto (-5)
--5


--Ejercicio 2

--a)
paraTodo :: [Bool] -> Bool
paraTodo [] = True
paraTodo (x:xs) = x==True && paraTodo xs 

--Ejemplos
--ghci> paraTodo [True, False, True]
--False
--ghci> paraTodo [True, True, True]
--True


--b)
sumatoria :: [Int] -> Int
sumatoria [] = 0
sumatoria (x:xs) = x + sumatoria xs

--Ejemplo
--ghci> sumatoria [4,6]
--10
--ghci> sumatoria [9,10]
--19
--ghci> sumatoria [9,(-10)]
-- -1


--c)
productoria :: [Int] -> Int
productoria [] = 1
productoria (g:gs) = g * productoria gs

-- Ejemplos
--ghci> productoria [10,10]
--100
--ghci> productoria [10, (-8)]
-- -80


--d)
factorial :: Int -> Int
factorial 0 = 1
factorial g = g * factorial (g-1)

-- Ejemplos con los que probé
--ghci> factorial 6
--720
--ghci> factorial 3
--6


promedio :: [Int] -> Int
promedio [] = 0
promedio (g:gs) = div (g + sumatoria gs) (length gs + 1)

-- Ejemplos con los que probé
-- ghci> promedio [1,7]
-- 4
-- ghci> promedio [2,4]
-- 3
-- promedio [5,6,7]
-- 6


-- Ejercicio 3

-- Programa la funcion pertenece :: Int -> [Int] -> Bool, que verifica si un numero se encuentra en una lista.

pertenece :: Int -> [Int] -> Bool
pertenece g [] = False 
pertenece g (m:ms) |  g == m = True 
                   | (g /= m) = pertenece g ms

--Ejemplos con los que probé
--ghci> pertenece 8 [1,6,5,0]
--False
--ghci> pertenece 5 [1,6,5]
--True


-- Ejercicio 4

--Programa las siguientes fuque implementan los cuantificadores generales. Nota que
--el segundo parametro de cada funcinciones on, es otra funcion!

--a)
--paratodo’ :: [a] -> (a -> Bool) -> Bool, dada una lista xs de tipo [a] y un
--predicado t :: a -> Bool, determina si todos los elementos de xs satisfacen el
--predicado t.

paraTodo' :: [a] -> (a -> Bool) -> Bool
paraTodo' [] predicado = True
paraTodo' (g:gs) predicado = predicado g  && paraTodo' gs predicado

--Ejemplos con los que probé
--ghci> paraTodo' ['a', 'g', 'v', 'h'] esMinuscula
--False
--ghci> paraTodo' ['a', 'u', 'e', 'i'] esMinuscula
--True
--ghci> paraTodo' [1, (-8), 7, 6] esPositivo
--False
--ghci> paraTodo' [1, 8, 7, 6] esPositivo   
--True

--b)
-- existe’ :: [a] -> (a -> Bool) -> Bool, dada una lista xs de tipo [a] y un
--predicado t :: a -> Bool, determina si algun elemento de xs satisface el predicado t.

existe' :: [a] -> (a -> Bool) -> Bool
existe' [] pred = False
existe' (g:gs) pred = pred g  || existe' gs pred

--Ejemplos que probé
--ghci> existe' [1,5,4,9] esCero
--False
--ghci> existe' [1,5,0,9] esCero
--True
--ghci> existe' ['k','j','o','l'] esMinuscula
--True
--ghci> existe' ['k','j','v','l'] esMinuscula
--False

--c)
--sumatoria’ :: [a] -> (a -> Int) -> Int, dada una lista xs de tipo [a] y una
--funcion t :: a -> Int (toma elementos de tipo a y devuelve enteros), calcula la
--suma de los valores que resultan de la aplicacion de t a los elementos de xs.

sumatoria' :: [a] -> (a -> Int) -> Int
sumatoria' [] predicado = 0
sumatoria' (g:gs) predicado = predicado g + sumatoria' gs predicado 

--Ejemplos
-- ghci> sumatoria' [3,2,4] factorial
--32
--ghci> sumatoria' [3,0,4] factorial
--31
--ghci> sumatoria' [1, 5,(-5), (-9), 6] valorAbsoluto
--26


--d)
--productoria’ :: [a] -> (a -> Int) -> Int, dada una lista de xs de tipo [a]
--y una funcion t :: a -> Int, calcula el producto de los valores que resultan de la
--aplicacion de t a los elementos de xs.

productoria' :: [a] -> (a -> Int) -> Int
productoria' [] predicado = 1
productoria' (g:gs) predicado = predicado g * productoria' gs predicado

--Ejemplos 
--ghci> productoria' [3,2,0] valorAbsoluto
--0     
--ghci> productoria' [3,2,0] factorial    
--12    
--ghci> productoria' [3,(-5)] valorAbsoluto  
--15

--Ejercicio 5

--Definı nuevamente la funcion paratodo, pero esta vez usando la funcion paratodo’ (sin
--recursion ni analisis por casos!).
-- paratodo :: [Bool] -> Bool, que verifica que todos los elementos de una lista
--sean True.
--paratodo’ :: [a] -> (a -> Bool) -> Bool, dada una lista xs de tipo [a] y un
--predicado t :: a -> Bool, determina si todos los elementos de xs satisfacen el
--predicado t.

paraTodo2 :: [Bool] -> Bool
paraTodo2 (g:gs) = paraTodo' gs id

--Ejercicio 6
--Utilizando las funciones del ejercicio 4, programa las siguientes funciones por composicion,
--sin usar recursion ni an ́alisis por casos.

--a) 
--todosPares :: [Int] -> Bool verifica que todos los numeros de una lista sean
--pares.

--primero, creo una funcion que me diga si un numero es par o no
pares :: Int-> Bool
pares x = mod x 2 == 0

-- ahora, lo utilizo en la funcion todosPares
todosPares :: [Int] -> Bool
todosPares (g:gs) = paraTodo' (g:gs) (pares)

--Ejemplos
--ghci> todosPares [2,4,6,8]
--True
--ghci> todosPares [2,4,6,7]
--False
--ghci> todosPares [2,1,6,8]
--False

--b)
--hayMultiplo :: Int -> [Int] -> Bool verifica si existe algun numero dentro del
--segundo parametro que sea multiplo del primer parametro.

esMulti ::Int -> Int -> Bool
esMulti n g = mod g n == 0 

hayMultiplo :: Int -> [Int] -> Bool
hayMultiplo n (g:gs) = existe' (g:gs) (esMulti n) 

--Ejemplos
--ghci> hayMultiplo 5 [15, 10, 20]
--True
--ghci> hayMultiplo 4 [15, 10, 20]
--True
--ghci> hayMultiplo 7 [15, 10, 20]
--False


--c)
--sumaCuadrados :: Int -> Int, dado un numero no negativo n, calcula la suma de
--los primeros n cuadrados
--Ayuda: En Haskell se puede escribir la lista que contiene el rango de numeros entre n y m como [n..m]. 

cuadrados :: Int -> Int
cuadrados i = i*i

sumaCuadrados :: Int -> Int
sumaCuadrados m = sumatoria' [0..m] cuadrados

--Ejemplos
--ghci> sumaCuadrados 3
--14
--ghci> sumaCuadrados 5
--55

--d)
--Programar la fucion existeDivisor::Int-> [Int] -> Bool, que dado en entero n
--y una lista ls , devuelve True si y solo si, existe algun elemento en ls que divida a n.

divisor :: Int -> Int -> Bool
divisor m r = mod m r == 0 

existeDivisor :: Int -> [Int] -> Bool
existeDivisor z (l:ls) = existe' (l:ls) (divisor z)

--Ejemplo 
--ghci> existeDivisor 14 [3,9,2]
--True
--ghci> existeDivisor 2 [3,9,14]
--False


--e)
--Utilizando la funcion del apartado anterior, definı la funcion esPrimo:: Int -> Bool,
--que dado un entero n, devuelve True si y solo si n es primo.
--Ayuda: En Haskell se puede escribir la lista que contiene el rango de numeros entre n y m como [n..m]

esPrimo :: Int -> Bool
esPrimo g = not (existeDivisor g [2..g-1])

--Ejemplos
--ghci> esPrimo 3
--True
--ghci> esPrimo 4
--False


--f)
-- ¿Se te ocurre como redefinir factorial (ej. 2d) para evitar usar recursion?

factorial2 :: Int -> Int
factorial2 0 = 1
factorial2 g = productoria [1..g] 

--Ejemplos
--ghci> factorial2 3
--6
--ghci> factorial2 0
--1
--ghci> factorial2 6
--720


--g)
--g) Programar la funcion multiplicaPrimos :: [Int] -> Int que calcula el producto
--de todos los numeros primos de una lista.




--h)
--h) Programar la funci ́on esFib :: Int -> Bool, que dado un entero n, devuelve True
--si y solo si n esta en la sucesion de Fibonacci.

--fibonacci es la suma de los 2 ultimos numeros, entonces defino el 0, y defino el 1 y luego la suma de los n
-- fiajte de usar elem y iterate o zipwith 
-- zipwith (+) suma los elementos que le des, como yo puse el 0 y el 1 concatenados, entonces se van a ir sumando a medida que me de mas numeros
-- el tail
 
fibo ::Int -> Int
fibo 0 = 0 
fibo 1 = 1
fibo 2 = 2
fibo n =  (n-1) + (n-2)

--usar elem en esFib