import Data.List (iterate')


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
--Escribo una función auxiliar que me dice si mi g es multiplo de mi n
esMulti ::Int -> Int -> Bool
esMulti n g = mod g n == 0 

{-Ejemplos
ghci> esMulti 10 5
False
ghci> esMulti 5 10
True
ghci> esMulti 7 14
True
-}

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
--Creo una función auxiliar que me calcule el cuadrado de un número

cuadrados :: Int -> Int
cuadrados i = i*i

{-Ejemplos:
ghci> esMulti 10 5
False
ghci> esMulti 5 10
True
ghci> esMulti 7 14
True
-}

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
--Creo una función auxiliar que me diga si m es divisor de r

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
esPrimo 0 = False
esPrimo 1 = False
esPrimo 2 = True
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
--Hago una función auxiliar que me diga si un g es primo 
lesPremes :: Int -> Int
lesPremes g | esPrimo g = g
            | not (esPrimo g) = 1

multiplicaPrimos :: [Int] -> Int
multiplicaPrimos (g:gs) = productoria' (g:gs) lesPremes

{- Ejemplos
ghci> multiplicaPrimos [2,4,3,6,5]
30
ghci> multiplicaPrimos [9,7,10,11]     
77
-}


--h) Programar la funcion esFib :: Int -> Bool, que dado un entero n, devuelve True
--si y solo si n esta en la sucesion de Fibonacci.

{-fibonacci es la suma de los 2 ultimos numeros, entonces defino el 0, y defino el 1 y luego la suma de los n
fiajte de usar elem y zipwith 
-}
 
-- Creo una función que me de el elemento en la sucesión de fibonacci en la g-ésima posición
suceFib :: Int -> Int
suceFib 0 = 1
suceFib 1 = 1
suceFib 2 = 2   
suceFib g = suceFib (g-1) + suceFib (g-2)   
      
{-Ejemplos:
ghci> suceFib 3
3
ghci> suceFib 4
5
ghci> suceFib 5
8
-}

listaFib :: Int -> [Int] 
listaFib 0 = []
listaFib g = suceFib g : listaFib (g-1)  

{- Ejemplos:
ghci> listaFib 6 
[13,8,5,3,2,1]
ghci> listaFib 25
[121393,75025,46368,28657,17711,10946,6765,4181,2584,1597,987,610,377,233,144,89,55,34,21,13,8,5,3,2,1]
-}

esFib :: Int -> Bool
esFib n = n `elem` listaFib n

{-Ejemplos
ghci> esFib 7
False
ghci> esFib 0
False
ghci> esFib 8
True
ghci> esFib 13
True
ghci> esFib 15
False
-}


{-i)
 Utilizando la funcion del apartado anterior, definı la funcion todosFib :: [Int] -> Bool
que dada una lista xs de enteros, devuelva si todos los elementos de la lista pertenecen
(o no) a la sucesion de Fibonacci.
-}

todosFib :: [Int] -> Bool
todosFib (g:gs) = paraTodo' (g:gs) esFib

{-Ejemplos:
ghci> todosFib [2,3,5,7]
False
ghci> todosFib [6,7,13,8]
False
ghci> todosFib [2,3,5,7] 
False
ghci> todosFib [2,3,5,8] 
True
-}


--Ejercicio 7
--Indaga en Hoogle sobre las funciones map y filter. Tambien podes consultar su tipo en
--ghci con el comando :t.

{- a)
¿Que hacen estas funciones?

map es del tipo (a -> b) -> [a] -> [b]. Lo que hace es tomar una función f y una lista y devuelve otra lista,
con la función f aplicada
filter, por otro lado, toma una función f y una lista (como map) pero devuelve una lista con los elementos
que cumplen f

b)
¿A que equivale la expresion map succ [1, -4, 6, 2, -8], donde succ n = n+1?

lo que va a hacer esta expresión es sumarle uno, a cada elemento de la lista. Es decir:
[2, -3, 7, 3, -7]

c)
¿Y la expresion filter esPositivo [1, -4, 6, 2, -8]?

Esta función va a devolver solo los números positivos de la lista, es decir:
[1, 6, 2]
-}

{- Ejercicio 8
Programa una funcion que dada una lista de numeros xs, devuelve la lista que resulta de
duplicar cada valor de xs.
a) Definila usando recursion.
b) Definila utilizando la funcion map.
-}


--a)
duplicaCursed :: [Int] -> [Int]
duplicaCursed [] = []
duplicaCursed (g:gs) = (g * 2) : duplicaCursed gs

{-Ejemplillos:
ghci> duplicaCursed [1,3,4,7]
[2,6,8,14]
ghci> duplicaCursed [6,9,3,2]
[12,18,6,4]
-}

-- b)
duplica :: Int -> Int
duplica n = n * 2

duplicaMapa :: [Int] -> [Int]
duplicaMapa (g:gs) = map duplica (g:gs)

{-Ejemplillos
ghci> duplicaMapa [1, 5, 6, 3]
[2,10,12,6]
ghci> duplicaMapa [(-5), 7, 12, 98]
[-10,14,24,196
-}

{-Ejercicio 9
Programa una funcion que dada una lista de numeros xs, calcula una lista que tiene como
elementos aquellos numeros de xs que son primos.
a) Definila usando recursion.
b) Definila utilizando la funcion filter.
c) Revisa tu definicion del ejercicio 6g. ¿Como podes mejorarla?
-}

--a)
primitos :: [Int] -> [Int]
primitos [] = []
primitos (g:gs) | esPrimo g = g : primitos gs
                | not (esPrimo g) = primitos gs 

{-Ejemplos:
ghci> primitos [2,4,6,7,5,18,3,32,65]
[2,7,5,3]
ghci> primitos [76,98,34,53,66,12,11,45]
[53,11]
-}
                
--b)
primitosFiltrados :: [Int] -> [Int]
primitosFiltrados (g:gs) = filter esPrimo (g:gs)

{-Ejemplos
ghci> primitosFiltrados [76,98,34,53,66,12,11,45]
[53,11]
ghci> primitosFiltrados [2,4,6,7,5,18,3,32,65]
[2,7,5,3]
ghci> primitosFiltrados [6,87,93,53,76,9]        
[53]
-}

--c)
multiplicaPrimos2 :: [Int] -> Int
multiplicaPrimos2 (g:gs) = productoria (filter esPrimo (g:gs)) 

{-Ejemplos
ghci> multiplicaPrimos [3,2,5,7,86,4]
210
ghci> multiplicaPrimos [45,765,13,65]
13
-}



{- Ejercicio 10
La funcion primIgualesA toma un valor y una lista, y calcula el tramo inicial mas largo de
la lista cuyos elementos son iguales a ese valor. Por ejemplo:
primIgualesA 3 [3,3,4,1] = [3,3]
primIgualesA 3 [4,3,3,4,1] = []
primIgualesA 3 [] = []
primIgualesA ’a’ "aaadaa" = "aaa"
a) Programa primIgualesA por recursion.
b) Programa nuevamente la funcion utilizando takeWhile.
-}

--a)

primIgualesA :: (Eq a) => a -> [a] -> [a]
primIgualesA n [] = []
primIgualesA n (g:gs) | (n == g) = g : primIgualesA n gs
                      | (n /= g)  = primIgualesA n []

{-Ejemplos
ghci> primIgualesA 5 [5,5,5,6,5,5]
[5,5,5]
ghci> primIgualesA 5 [5,6,5,5]    
[5]
ghci> primIgualesA (-5) [5,6,5,5]
[]
ghci> primIgualesA (-5) [(-5),(-5),6,5,5]
[-5,-5]
-}

--b)

primIgualesA2 ::(Eq a) => a -> [a] -> [a]
primIgualesA2 n (g:gs) = takeWhile (== n) (g:gs)

{-Ejemplos
-}

{- Ejercicio 11
La funcion primIguales toma una lista y devuelve el mayor tramo inicial de la lista cuyos
elementos son todos iguales entre sı. Por ejemplo:
primIguales [3,3,4,1] = [3,3]
primIguales [4,3,3,4,1] = [4]
primIguales [] = []
primIguales "aaadaa" = "aaa"
a) Programa primIguales por recursion.
b) Usa cualquier version de primIgualesA para programar primIguales. Esta permitido
dividir en casos, pero no usar recursion.
-}

--a)
primIguales :: (Eq a) => [a] -> [a]
primIguales [] = []
primIguales (g:h:gs) | (g /= h) = g : []
                     | (g == h) = g : primIguales (h:gs)

{-Ejemplos:
ghci> primIguales [3,3,4,1]
[3,3]
ghci> primIguales [4,3,3,4,1]
[4]
ghci> primIguales "hhola"    
"hh"
ghci> primIguales "ssssiuuu" 
"ssss"
-}  


--b)
primIguales2 :: (Eq a) => [a] -> [a]
primIguales2 (g:gs) = primIgualesA g (g:gs)

{- Ejemplos:
ghci> primIguales2 "ssssiuuu"
"ssss"
ghci> primIguales2  [4,3,3,4,1]
[4]
ghci> primIguales2  [7,7,7,4,7,7,7]
[7,7,7]
ghci> primIguales2  [7,8,9]        
[7]
ghci> primIguales2  "bbbuenas"
"bbb"
-}
          
                      
                      
