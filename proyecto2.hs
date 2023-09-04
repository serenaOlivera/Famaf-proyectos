{- Ejercicio 1
data Carrera = Matematica | Fisica | Computacion | Astronomia
a) Implementa el tipo Carrera como esta definido arriba
b) Definı la siguiente funcion, usando pattern matching : titulo :: Carrera -> String
que devuelve el nombre completo de la carrera en forma de string. Por ejemplo, para el
constructor Matematica, debe devolver ”Licenciatura en Matematica”.
c) Para escribir musica se utiliza la denominada notacion musical, la cual consta de
notas (do, re, mi, ...). Ademas, estas notas pueden presentar algun modificador ]
(sostenido) o [ (bemol), por ejemplo do], si[, etc. Por ahora nos vamos a olvidar de
estos modificadores (llamados alteraciones) y vamos a representar las notas basicas.
Definir el tipo NotaBasica con constructores Do, Re, Mi, Fa, Sol, La y Si
d) El sistema de notacion musical anglosajon, tambien conocido como notacion o cifrado
americano, relaciona las notas basicas con letras de la A a la G. Este sistema se usa por
ejemplo para las tablaturas de guitarra. Programar usando pattern matching la funcion:
cifradoAmericano :: NotaBasica -> Char
que relaciona las notas Do, Re, Mi, Fa, Sol, La y Si con los caracteres ’C’ , ’D’, ’E’,
’F’, ’G’, ’A’ y ’B’ respectivamente.
-}

--a)
data Carrera = Matematica | Fisica | Computacion | Astronomia

--b)
titulo :: Carrera -> String
titulo Matematica = "Licenciatura en Matematica"
titulo Fisica = "Licenciatura en Fisica"
titulo Computacion = "Licenciatura en Computacion"
titulo Astronomia = "Licenciatura en Astronomia"

--c)
data NotaBasica = Do | Re | Mi 
                | Fa | Sol | La | Si 
                {-Ejerc2.a-} deriving (Eq, Ord, Show)

--d)
cifradoAmericano :: NotaBasica -> Char
cifradoAmericano Do = 'A'
cifradoAmericano Re = 'B'
cifradoAmericano Mi = 'C'
cifradoAmericano Fa = 'D'
cifradoAmericano Sol = 'E'
cifradoAmericano La = 'F'
cifradoAmericano Si = 'G'

{-Ejercicio 2
a) Completar la definicion del tipo NotaBasica para que las expresiones
*Main> Do <= Re
*Main> Fa `min` Sol
sean validas y no generen error. Ayuda: usar deriving con multiples clases.
-}

{-Ejercicio 3
a) Definir usando polimorfismo ad hoc la funcion minimoElemento que calcula (de manera
recursiva) cual es el menor valor de una lista de tipo [a]. Asegurarse que solo este
definida para listas no vacıas.
b) Definir la funcion minimoElemento’ de manera tal que el caso base de la recursion
sea el de la lista vacıa. Para ello revisar la clase Bounded.
Ayuda: Para probar esta funcion dentro de ghci con listas vacıas, indicar el tipo concre-
to con tipos de la clase Bounded, por ejemplo: ([1,5,10]::[Int]), ([]::[Bool]),
etc.
c) Usar la funcion minimoElemento para determinar la nota mas grave de la melodıa:
[Fa, La, Sol, Re, Fa]
-}

--a)
minimoElemento :: (Eq (a), Ord (a), Show (a)) => [a] -> a 
minimoElemento [g] = g
minimoElemento (g:h:gs) =  g `min` minimoElemento (h:gs)  

--b)
minimoElemento' :: (Eq (a), Ord (a), Show (a), Bounded (a)) => [a] -> a
minimoElemento' [] = minBound 
minimoElemento' (g:gs)  = g `min` minimoElemento' gs

--c)
graveNota :: [NotaBasica] -> NotaBasica
graveNota [g] = g  
graveNota (g:gs) = g `min` graveNota gs  




