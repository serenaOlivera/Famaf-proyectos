module Dibujo where

-- Definicion  del lenguaje
data Dibujo a = Basica a 
              | Rotar (Dibujo a)
              | Apilar Int Int (Dibujo a) (Dibujo a)
              | Encimar (Dibujo a) (Dibujo a)
              | Resize Float (Dibujo a)
              deriving(Show, Eq)


-- Funcion Map (de Basicas) para nuestro sub-lenguaje.
mapDib :: (a -> b) -> Dibujo a -> Dibujo b
mapDib f (Basica x) = Basica (f x) 
mapDib f (Rotar d1) = Rotar (mapDib f d1)
mapDib f (Apilar n m d1 d2) = Apilar n m (mapDib f d1) (mapDib f d2)
mapDib f (Encimar d1 d2) = Encimar (mapDib f d1) (mapDib f d2)
mapDib f (Resize x d1) = Resize x (mapDib f d1)


-- Funcion Fold para nuestro sub-lenguaje.
foldDib :: (a -> b) -> (b -> b) ->
       (Int -> Int -> b -> b -> b) -> 
       (b -> b -> b) -> (Float -> b ->b)->
       Dibujo a -> b

foldDib sB sR sA sEn sRe d =
    let foldDibRecursiva = foldDib sB sR sA sEn sRe
    in case d of
        Basica x -> sB x
        Rotar d -> sR $ foldDibRecursiva d
        Apilar m n d1 d2 -> sA m n (foldDibRecursiva d1) (foldDibRecursiva d2)
        Encimar d1 d2 -> sEn (foldDibRecursiva d1) (foldDibRecursiva d2)
        Resize x d -> sRe x (foldDibRecursiva d)



--COMPLETAR (EJERCICIO 1-a)
toBool:: Dibujo (Int,Int) -> Dibujo Bool
toBool (Basica (x,y)) |  (mod x y) == 0 = Basica True
                      |  (mod y x) == 0 =  Basica True
                      | (((mod x y) /= 0) && ((mod y x) /= 0 )) = Basica False
toBool (dibu) = case dibu  of
              Rotar (d1) -> Rotar(toBool d1)
              Apilar x y d1 d2 -> Apilar x y (toBool d1) (toBool d2)
              Encimar d1 d2 -> Encimar (toBool d1) (toBool d2)
              Resize x d1 -> Resize x (toBool d1)

--COMPLETAR (EJERCICIO 1-b)
toBool2:: Dibujo (Int,Int) -> Dibujo Bool
toBool2 d1 = mapDib esMultiplo d1

--funcion auxiliar para aplicar map
esMultiplo :: (Int, Int) -> Bool
esMultiplo (x,y) = ((mod x y) == 0 || (mod y x) == 0)


--COMPLETAR (EJERCICIO 1-c)
profundidad:: Dibujo a -> Int
profundidad (Basica x) = 1
profundidad (Rotar d1) = 1 + profundidad d1
profundidad (Apilar x y d1 d2) =  profundidad d2
profundidad (Encimar d1 d2) = profundidad d1 + profundidad d2
profundidad (Resize x d1) = 1 + profundidad d1

--COMPLETAR (EJERCICIO 1-d)
profundidad2:: Dibujo a -> Int
profundidad2 dib =  foldDib (\x -> 1) (\x->1) (\i j k l -> 1) (\ i j -> 1) (\x i  -> 1) dib

