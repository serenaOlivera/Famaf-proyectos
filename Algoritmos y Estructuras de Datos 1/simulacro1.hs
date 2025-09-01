
data Deportes =  Futbol  | Basquet | Tenis | Valorant | Dota2 deriving (Eq)

type MinJugadores = Int

minimaCantidad :: Deportes -> MinJugadores
minimaCantidad d = case d of
                   Tenis -> 2
                   Futbol -> 7
                   Dota2 -> 9
                   _ -> 0

{- Ejemplo:
ghci> minimaCantidad (Tenis)
2
ghci> minimaCantidad Futbol 
7
-}

type NombrePersona = String 

data PracticoDeporte = Ninguna | AgregaDeporte Deportes NombrePersona PracticoDeporte  deriving (Eq)

deporte :: PracticoDeporte -> Deportes -> NombrePersona -> Bool
deporte Ninguna _ _  = False 
deporte (AgregaDeporte d n p) d' n' | d == d' && n == n' = True
                                    | otherwise = False

{- Ejemplo
ghci> deporte (AgregaDeporte Futbol "pepe" (Ninguna) ) Futbol "pepe"
True
ghci> deporte (AgregaDeporte Futbol "pepe" (Ninguna) ) Futbol "mariela"
False
ghci> deporte (AgregaDeporte Futbol "pepe" (Ninguna) ) Valorant "pepe" 
False
-}
--tu vieja en tanga hs