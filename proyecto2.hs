{-Preguntar:
Ejercicio 3 c ¿Como defino a Show para que me ande?
-}

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
titulo Computacion = "Licenciatura en Ciencias de la Computacion"
titulo Astronomia = "Licenciatura en Astronomia"

{- Ejemplos:
ghci> titulo Computacion
"Licenciatura en Ciencias de la Computacion"
ghci> titulo Matematica 
"Licenciatura en Matematica"
ghci> titulo Fisica     
"Licenciatura en Fisica"
-}
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

{-Ejemplos :
ghci> cifradoAmericano Do
'A'
ghci> cifradoAmericano Sol
'E'
ghci> cifradoAmericano La 
'F'
-}

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

{-Ejemplos :
ghci> minimoElemento [2,5,3,8,9,1,6,4] 
1
ghci> minimoElemento [6,63,56,23,6,0,(-5)] 
-5
ghci> minimoElemento [6,63,56,23,6,0]     
0
-}

--b)
minimoElemento' :: (Bounded (a), Eq (a), Ord (a) , Show (a)) => [a] -> a
minimoElemento' [] = minBound 
minimoElemento' (g:gs)  = g `min` minimoElemento' gs

--c)
graveNota :: [NotaBasica] -> NotaBasica
graveNota [g] = g  
graveNota (g:gs) = g `min` graveNota gs  

{-Ejemplos :
ghci> graveNota [Do, Re, Mi, Fa, Sol]
Do
ghci> graveNota [ Fa, Sol]
Fa
ghci> graveNota [Fa, La, Re]
-}

{- Ejercicio 4
a) Implementa el tipo Deportista y todos sus tipos accesorios (NumCamiseta, Altura,
Zona, etc) tal como estan definidos arriba.
b) ¿Cual es el tipo del constructor Ciclista?
c) Programa la funcion contar_velocistas :: [Deportista] -> Int que dada una
lista de deportistas xs, devuelve la cantidad de velocistas que hay dentro de xs.
Programar contar_velocistas sin usar igualdad, utilizando pattern matching.
d) Programa la funcion contar_futbolistas :: [Deportista] -> Zona -> Int que
dada una lista de deportistas xs, y una zona z, devuelve la cantidad de futbolistas
incluidos en xs que juegan en la zona z. No usar igualdad, solo pattern matching.
e) ¿La funcion anterior usa filter? Si no es ası, reprogramala para usarla.
-}

--a)
type Altura = Int
type NumCamiseta = Int


data Zona = Arco | Defensa | Mediocampo | Delantera
         deriving (Eq, Show)
data TipoReves = DosManos | UnaMano
         deriving (Eq, Show)
data Modalidad = Carretera | Pista | Monte | BMX
         deriving (Eq, Show)
data PiernaHabil = Izquierda | Derecha
         deriving (Eq, Show)

type ManoHabil = PiernaHabil

data Deportista = Ajedrecista 
                | Ciclista Modalidad 
                | Velocista Altura 
                | Tenista TipoReves ManoHabil Altura 
                | Futbolista Zona NumCamiseta PiernaHabil Altura 
        deriving (Eq, Show)      
-- b)
{- El tipo del constructor Ciclista es Modalidad 
(dentro de este estan definidos los constructores: Carretera, 
Pista, Monte y BMX
-}

-- c}

contarVelocistas :: [Deportista] -> Int 
contarVelocistas [] = 0
contarVelocistas (Velocista a :gs) =  1 + contarVelocistas gs
contarVelocistas ( _ : gs) = contarVelocistas gs

{- Ejemplos
ghci> contarVelocistas [Ajedrecista, Ciclista Monte, Tenista UnaMano Derecha 40]
0
ghci> contarVelocistas [Ajedrecista, Ciclista Monte, Tenista UnaMano Derecha 40, Velocista 50]
1
ghci> contarVelocistas [Velocista 20, Velocista 40, Ajedrecista]
2
ghci> contarVelocistas []
0
-}

-- d)

contar_futbolistas :: [Deportista] -> Zona -> Int
contar_futbolistas [] z = 0

{-
contar_futbolistas (g:gs) z = case g of 
                                Futbolista z _ _ _ -> 1 + contar_futbolistas gs z
                                _  -> contar_futbolistas gs z
-}
                               
contar_futbolistas (Futbolista Arco n p a : gs) Arco = 1 + contar_futbolistas gs Arco
contar_futbolistas (Futbolista Defensa n p a : gs) Defensa = 1 + contar_futbolistas gs Defensa
contar_futbolistas (Futbolista Mediocampo n p a : gs) Mediocampo = 1 + contar_futbolistas gs Mediocampo
contar_futbolistas (Futbolista Delantera n p a : gs) Delantera = 1 + contar_futbolistas gs Delantera
contar_futbolistas ( _ : gs) z = contar_futbolistas gs z

--e) mi funcion no usa filter 

zonaFiltrada :: Deportista -> Zona -> Bool
zonaFiltrada (Futbolista s n p a) z | s == z = True
                                    | s /= z = False
zonaFiltrada ( _ ) z = False 


{-
contar_futbolistas' :: [Deportista] -> Zona -> Int
contar_futbolistas' [] z = 0
contar_futbolistas' 
-}
 