-- Serena Olivera


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
                {-Ejerc2.a-} deriving (Show, Ord, Eq)

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
contar_futbolistas (Futbolista Arco n p a : gs) Arco = 1 + contar_futbolistas gs Arco
contar_futbolistas (Futbolista Defensa n p a : gs) Defensa = 1 + contar_futbolistas gs Defensa
contar_futbolistas (Futbolista Mediocampo n p a : gs) Mediocampo = 1 + contar_futbolistas gs Mediocampo
contar_futbolistas (Futbolista Delantera n p a : gs) Delantera = 1 + contar_futbolistas gs Delantera
contar_futbolistas ( _ : gs) z = contar_futbolistas gs z

{-Ejemplos
ghci> contar_futbolistas [(Futbolista  Defensa 5 Derecha  7), (Futbolista Arco 6 Izquierda 76), (Ajedrecista)] Arco       
1
ghci> contar_futbolistas [(Futbolista  Arco 5 Derecha  7), (Futbolista Arco 6 Izquierda 76), (Ajedrecista)] Arco   
2
-}

--e) mi funcion no usa filter 

zonaFiltrada :: Zona -> Deportista -> Bool
zonaFiltrada z (Futbolista s n p a)  | s == z = True
                                     | s /= z = False
zonaFiltrada  z _  = False 

{-Ejemplos:
ghci> zonaFiltrada Ajedrecista Mediocampo
False
ghci> zonaFiltrada (Futbolista Delantera 5 Derecha 120) Mediocampo 
False
ghci> zonaFiltrada (Futbolista Mediocampo 5 Derecha 120) Mediocampo 
True
-}


contarFutbolistas' :: [Deportista] -> Zona -> Int
contarFutbolistas' [] z = 0
contarFutbolistas' (g:gs) z = length (filter (zonaFiltrada z) (g:gs))

{- Ejemplos:
ghci> contarFutbolistas'[(Futbolista  Defensa 5 Derecha  7), (Futbolista Arco 6 Izquierda 76), (Ajedrecista)] Arco 
1
ghci> contarFutbolistas' [(Futbolista  Arco 5 Derecha  7), (Futbolista Arco 6 Izquierda 76), (Ajedrecista)] Arco   
2
-}

-- Ejercicio 5
{-a) Implementa la funcion sonidoNatural como esta definida arriba.
b) Definir el tipo enumerado Alteracion que consta de los constructores Bemol, Natural
y Sostenido.
c) Definir el tipo algebraico NotaMusical que debe tener un solo un constructor que llamaremos Nota el cual toma
dos parametros. El primer parametro es de tipo NotaBasica
y el segundo de tipo Alteracion. De esta manera cuando se quiera representar una
nota alterada se puede usar como segundo parametro del constructor un Bemol o
Sostenido y si se quiere representar una nota sin alteraciones se usa Natural como
segundo parametro.
d) Definı la funcion sonidoCromatico :: NotaMusical -> Int que devuelve el sonido
de una nota, incrementando en uno su valor si tiene la alteracion Sostenido,
decrementando en uno si tiene la alteracion Bemol y dejando su valor intacto si la alteracion
es Natural
e) Incluı el tipo NotaMusical a la clase Eq de manera tal que dos notas que tengan el
mismo valor de sonidoCromatico se consideren iguales.
f ) Incluı el tipo NotaMusical a la clase Ord definiendo el operador <=. Se debe definir
que una nota es menor o igual a otra si y solo si el valor de sonidoCromatico para la
primera es menor o igual al valor de sonidoCromatico para la segunda
-}

-- a)
sonidoNatural :: NotaBasica -> Int
sonidoNatural Do = 0
sonidoNatural Re = 2
sonidoNatural Mi = 4
sonidoNatural Fa = 5
sonidoNatural Sol = 7
sonidoNatural La = 9
sonidoNatural Si = 11

-- b) 
data Alteracion = Bemol | Natural | Sostenido deriving (Eq, Ord)


-- c) 
data NotaMusical = Nota  NotaBasica Alteracion  

-- d)
sonidoAlteracion :: Alteracion -> Int
sonidoAlteracion Bemol = (-1)
sonidoAlteracion Natural = 0
sonidoAlteracion Sostenido = 1


sonidoCromatico :: NotaMusical -> Int
sonidoCromatico (Nota n a) = sonidoNatural n + sonidoAlteracion a

{- Ejemplos:
ghci> sonidoCromatico (Nota Do Bemol)
-1
ghci> sonidoCromatico (Nota Do Sostenido)
1
ghci> sonidoCromatico (Nota Fa Sostenido)
6
ghci> sonidoCromatico (Nota Fa Bemol)    
4
-}

-- e)

instance Eq NotaMusical
 where
  (Nota b q) == (Nota a j) = sonidoCromatico (Nota b q) == sonidoCromatico (Nota a j)


{-Ejemplos
ghci> sonidoCromatico (Nota Fa Sostenido) == sonidoCromatico (Nota Sol Bemol)    
True
ghci> sonidoCromatico (Nota Si Bemol) == sonidoCromatico (Nota La Sostenido) 
True
-}

-- f)
--Incluı el tipo NotaMusical a la clase Ord definiendo el operador <=. Se debe definir
--que una nota es menor o igual a otra si y solo si el valor de sonidoCromatico para la
--primera es menor o igual al valor de sonidoCromatico para la segunda

instance Ord NotaMusical
 where
      (Nota b q) <= (Nota a j) = sonidoCromatico (Nota b q) <= sonidoCromatico (Nota a j)

{-Ejemplos:
ghci> (Nota Do Bemol) <= (Nota Do Natural) 
True
ghci> (Nota Do Bemol) <= (Nota Fa Natural) 
True
ghci> (Nota Si Bemol) <= (Nota Fa Natural) 
False
ghci> sonidoCromatico (Nota Si Bemol) <= sonidoCromatico (Nota Fa Natural)
False
ghci> sonidoCromatico (Nota Do Bemol) <= sonidoCromatico (Nota Do Natural) 
True
-}

-- Ejercicio 6 
{-a) Definir la funcion primerElemento que devuelve el primer elemento de una lista no
vacıa, o Nothing si la lista es vacıa.
primerElemento : : [ a ] −> Maybe a
-}

-- a)
primerElemento :: [a] -> Maybe a
primerElemento [] = Nothing
primerElemento (g:gs) = Just g 

{- Ejemplos:
ghci> primerElemento []
Nothing
ghci> primerElemento [1,2,3,4] 
Just 1
ghci> primerElemento [True, False, True, False]
Just True
-}

-- Ejercicio 7

{- a) Programa las siguientes funciones:
1) atender :: Cola -> Maybe Cola, que elimina de la cola a la persona que esta
en la primer posicion de una cola, por haber sido atendida. Si la cola esta vacıa,
devuelve Nothing.
2) encolar :: Deportista -> Cola -> Cola, que agrega una persona a una cola
de deportistas, en la ultima posicion.
3) busca :: Cola -> Zona -> Maybe Deportista, que devuelve el/la primera
futbolista dentro de la cola que juega en la zona que se corresponde con el segundo
parametro. Si no hay futbolistas jugando en esa zona devuelve Nothing.
b) ¿A que otro tipo se parece Cola?.
-}

data Cola = VaciaC | Encolada Deportista Cola deriving Show

-- a)
-- 1.
atender :: Cola -> Maybe Cola
atender g = case g of
                VaciaC -> Nothing
                Encolada d c -> Just c 

{-Ejemplos:
ghci> atender (Encolada Ajedrecista (Encolada (Velocista 120) (VaciaC)))
Just (Encolada (Velocista 120) VaciaC)
ghci> atender (Encolada Ajedrecista (Encolada (Velocista 40) (Encolada (Ciclista Monte) VaciaC)))
Just (Encolada (Velocista 40) (Encolada (Ciclista Monte) VaciaC))
-}

-- 2.
encolar :: Deportista -> Cola -> Cola
encolar d VaciaC = Encolada d VaciaC
encolar d (Encolada d' c) = Encolada d' (encolar d c)

{-Ejemplos:
ghci> encolar Ajedrecista (Encolada (Velocista 40) VaciaC)
Encolada (Velocista 40) (Encolada Ajedrecista VaciaC)
ghci> encolar (Ciclista Monte) (Encolada Ajedrecista (Encolada (Velocista 40) VaciaC))
Encolada Ajedrecista (Encolada (Velocista 40) (Encolada (Ciclista Monte) VaciaC))
-}

-- 3.

busca :: Cola -> Zona -> Maybe Deportista
busca VaciaC z = Nothing
busca (Encolada d c) z = case d of
                         (Futbolista z' _ _ _) -> if z == z' then Just d else busca c z
                         _ -> busca c z


{- Ejemplos :
ghci> busca (Encolada (Futbolista Defensa 5 Derecha 170) VaciaC) Arco
Nothing
ghci> busca (Encolada (Futbolista Defensa 5 Derecha 170) VaciaC) Defensa
Just (Futbolista Defensa 5 Derecha 170)
ghci> busca (Encolada (Futbolista Defensa 5 Derecha 170) (Encolada (Futbolista Arco 6 Izquierda 180) VaciaC)) Defensa
Just (Futbolista Defensa 5 Derecha 170)
-}

-- b)
{-Cola se parece al tipo de lista, que es lista = Vacía | Agregar Int lista-}

-- Ejercicio 8 
data ListaAsoc a b = Vacia | Nodo a b (ListaAsoc a b) deriving Show

-- a
{-¿Como se debe instanciar el tipo ListaAsoc para representar la informacion almacenada
en una guıa telefonica?
-}
type GuiaTelefonica =  ListaAsoc String Int 

-- b)
{-Programa las siguientes funciones:
1) la_long :: ListaAsoc a b -> Int que devuelve la cantidad de datos en una
lista.
2) la_concat :: ListaAsoc a b -> ListaAsoc a b -> ListaAsoc a b, que devuelve la concatenacion de 
dos listas de asociaciones.
3) la_agregar :: Eq a => ListaAsoc a b -> a -> b -> ListaAsoc a b, que
agrega un nodo a la lista de asociaciones si la clave no esta en la lista, o actualiza
el valor si la clave ya se encontraba.
4) la_pares :: ListaAsoc a b -> [(a, b)] que transforma una lista de asociaciones en una lista de pares clave-dato.
5) la_busca :: Eq a => ListaAsoc a b -> a -> Maybe b que dada una lista
y una clave devuelve el dato asociado, si es que existe. En caso contrario devuelve
Nothing.
6) la_borrar :: Eq a => a -> ListaAsoc a b -> ListaAsoc a b que dada
una clave a elimina la entrada en la lista.
-}

-- 1)
laLong :: ListaAsoc a b -> Int
laLong Vacia = 0 
laLong (Nodo a b c) = 1 + (laLong c)

{-
ghci> laLong (Nodo 1 3 (Nodo  5 6 Vacia))   
2
ghci> laLong (Nodo "amen" "abril" (Nodo "h" "o" Vacia))
2
ghci> laLong (Vacia)
0
-}

-- 2)

laConcat :: ListaAsoc a b -> ListaAsoc a b -> ListaAsoc a b
laConcat Vacia Vacia = Vacia
laConcat Vacia (Nodo a b c) = Nodo a b c
laConcat (Nodo a b c) Vacia = Nodo a b c
laConcat (Nodo a b c) (Nodo a' b' c') = Nodo a b (laConcat c (Nodo a' b' c'))

{-Ejemplos
ghci> laConcat (Nodo 1 3 (Nodo  5 6 Vacia)) (Nodo 85 74 Vacia)
Nodo 1 3 (Nodo 5 6 (Nodo 85 74 Vacia))
ghci> laConcat (Nodo 1 3 (Nodo  5 6 Vacia))  (Nodo 5467 7687 (Nodo 548 5486 Vacia))
Nodo 1 3 (Nodo 5 6 (Nodo 5467 7687 (Nodo 548 5486 Vacia)))
-}


-- 3)
laAgregar :: (Eq a) => ListaAsoc a b -> a -> b -> ListaAsoc a b 
laAgregar Vacia a' b' =  Nodo a' b' Vacia
laAgregar (Nodo a b c) a' b' | a == a' = Nodo a b' c
                             | a /= a' =  Nodo a b (laAgregar c a' b')

{- Ejemplos:
ghci> laAgregar (Nodo 1 2 Vacia) 1 5           
Nodo 1 5 Vacia
ghci> laAgregar (Nodo 1 2 (Nodo 5 6 Vacia)) 1 5
Nodo 1 5 (Nodo 5 6 Vacia)
ghci> laAgregar (Nodo 1 2 (Nodo 5 6 Vacia)) 5 5
Nodo 1 2 (Nodo 5 5 Vacia)
ghci> laAgregar (Nodo 1 2 (Nodo 5 6 Vacia)) 6 5
Nodo 1 2 (Nodo 5 6 (Nodo 6 5 Vacia))
-}

-- 4)
laPares :: ListaAsoc a b -> [(a, b)]
laPares Vacia = []
laPares (Nodo a b c) = (a, b) : laPares c 

{- Ejemplos 
ghci> laPares Vacia
[]
ghci> laPares (Nodo 5 6 (Nodo 3 4 Vacia))
[(5,6),(3,4)]
-}

-- 5) 

laBusca :: (Eq a) => ListaAsoc a b -> a -> Maybe b 
laBusca Vacia a' = Nothing
laBusca (Nodo a b c) a' = if a' == a then Just b 
                          else laBusca c a'

{-Ejemplos 
ghci> laBusca (Nodo 1 3 (Nodo 5 6 Vacia)) 5
Just 6
ghci> laBusca (Nodo 1 3 (Nodo 5 6 Vacia)) 1
Just 3
ghci> laBusca (Nodo 6 3 (Nodo 5 6 Vacia)) 1
Nothing
-}

-- 6)

laBorrar :: Eq a => a -> ListaAsoc a b -> ListaAsoc a b
laBorrar a' Vacia = Vacia
laBorrar a' (Nodo a b c) | a == a' = laBorrar a' c
                         | a /= a' = Nodo a b (laBorrar a' c)

{-Ejemplos:
ghci> laBorrar 1 (Nodo 5 6 (Nodo 1 3 Vacia))
Nodo 5 6 Vacia
ghci> laBorrar 7 (Nodo 5 6 (Nodo 1 3 Vacia))
Nodo 5 6 (Nodo 1 3 Vacia)
ghci> laBorrar 7  Vacia                     
Vacia
-}