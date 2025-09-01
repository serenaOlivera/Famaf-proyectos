-- OLivera Serena
-- 45887190
-- Comision 2
-- Lab 28

-- Ejercicio 1

f :: (Eq a, Ord a) => a -> a -> a
f x y | x < y = x
      | otherwise = y

data TipoEnum = Val1 | Val2 | Val3 deriving (Eq, Ord, Show)

-- Ejercicio 2
data Categoria = Literatura | Infantiles | Autoayuda | Comics deriving Show
data Editorial = Altea | Minotauro | Panini deriving Show-- no eq ni ord
type Titulo = String
type Precio = Int 



data Marca = Monoblock | Paprika  deriving Show -- no eq ni ord
type AnioAgenda = Int
type PrecioAg = Precio 


type PrecioCuad = Precio 
  
type MarcaCuad = Marca




-- a)

data ArticulosLibreria = Libro Categoria Editorial Titulo Precio
                       | Agenda Marca AnioAgenda PrecioAg
                       | Cuaderno PrecioCuad MarcaCuad  deriving Show
-- no puede tener eq ni ord

-- b)
librosBaratos :: [ArticulosLibreria] -> Precio -> [ArticulosLibreria]
librosBaratos [] p = []
librosBaratos (g:gs) p = case g of
                         (Libro _ _ _ p') -> if p' <= p then g : librosBaratos gs p else librosBaratos gs p
                         (Agenda _ _ j) -> if j <= p then g : librosBaratos gs p else librosBaratos gs p
                         (Cuaderno k _) -> if k <= p then g : librosBaratos gs p else librosBaratos gs p
                         _ -> librosBaratos [] p

{- Ejemplos
ghci> librosBaratos [(Libro Infantiles Panini "chamarro" 250), (Agenda Paprika 2016 100), (Cuaderno 120 Monoblock)] 200 
[Agenda Paprika 2016 100,Cuaderno 120 Monoblock]
ghci> librosBaratos [(Libro Infantiles Panini "chamarro" 250), (Agenda Paprika 2016 100), (Cuaderno 120 Monoblock)] 50
[]
ghci> librosBaratos [(Libro Infantiles Panini "chamarro" 250), (Agenda Paprika 2016 100), (Cuaderno 120 Monoblock)] 300
[Libro Infantiles Panini "chamarro" 250,Agenda Paprika 2016 100,Cuaderno 120 Monoblock]

-}

-- c)
-- como no puedo derivar la igualdad en la editorial, primero voy a instanciarla

instance Eq Editorial
 where
  p == q = Altea == Altea
  p == q = Minotauro == Minotauro
  p == q = Panini == Panini 
  
   
instance Eq ArticulosLibreria
 where
    (Libro a b c d ) == (Libro e f g h) =  b == f  && d == h
    (Agenda a b c) == (Agenda d e f) =  b == e && c == f
    (Cuaderno a b) == (Cuaderno c d) = a == c 


{-Ejemplos:
(Libro Autoayuda Panini "aa" 120) == (Libro Comics Panini "bb" 120)

-}

-- EJercicio 3 
type Nombre = String
data Nivel = Uno | Dos | Tres 
data Parcial1 = 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 
type Parcial2 = Parcial1
type FInal = Parcial1
NotasDeIngles = NoHayEstudiantes 
              | EvolucionDelEstudiante Nombre Nivel Parcial1 Parcial2 Final NotasDeIngles
