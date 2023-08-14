--Ejercicio 1 
-- a)
esCero :: Int -> Bool
esCero x | x == 0 = True
         | x /= 0 = False

--Ejemplos con los que intenté
-- esCero 0
-- True
-- esCero 7
-- False

--b)
esPositivo :: Int -> Bool
esPositivo x | x > 0 = True
             | x <= 0 = False

--Ejemplos 
--ghci> esPositivo (-6)
--False
--ghci> esPositivo 4
--True


--c)
esMinuscula :: Char -> Bool
esMinuscula j = j == 'a' || j == 'e' || j== 'i' || j=='o' || j=='u'

-- Ejemplos
-- esMinuscula 'j'
-- False
--ghci> esMinuscula 'A'
--False
--ghci> esMinuscula 'i'
--True 
