--Alias para variables
type Nombre = String
--Tipo para las proposiciones
data LProp = T | F | VarP Nombre | Conj LProp LProp | Disy LProp LProp |
                Impl LProp LProp | Syss LProp LProp | Neg LProp deriving (Eq)

--Tipo para el Tableaux
data Tableaux = Hoja [LProp] | Alpha [LProp] Tableaux |
                Beta [LProp] Tableaux Tableaux deriving (Show, Eq)


--Crea la instancia de la clase show para LProp utilizando los símbolos adecuados.
instance Show LProp where
    show (T)   = "True"
    show (F)   = "False"
    show (VarP p)    = show p
    show (Neg p)    = "!" ++ show p
    show (Conj p q) = "(" ++ show p ++ " ^ " ++ show q ++ ")"
    show (Disy p q) = "(" ++ show p ++ " v " ++ show q ++ ")"
    show (Impl p q) = "(" ++ show p ++ " -> " ++ show q ++ ")"
    show (Syss p q) = "(" ++ show p ++ " <-> " ++ show q ++ ")"
-----------------------------------------------------------------------------------


-- Función que nos dice si en una lista de fórmulas, todas son literales.
literales :: [LProp] -> Bool
literales [VarP p] = True
literales [Neg p] = literales [p]
literales [Conj p q] = False
literales [Disy p q] = False
literales [Impl p q] = False
literales [Syss p q] = False
literales (x:xs) = if (literales [x]) then (literales xs) else False

-- Función que regresa la primera fórmula que no es literal de una lista de fórmulas.
nextF :: [LProp] -> LProp
nextF [x] = if not (literales [x]) then x else error "No hay fórmulas"
nextF (x:xs) = if not (literales [x]) then x else (nextF xs)

-- Nos dice si una fórmula f es una fórmula α
alpha :: LProp -> Bool
alpha (Conj p q) = True
alpha (Neg (Disy p q)) = True
alpha (Neg (Impl p q)) = True
alpha _ = False

-- Nos dice si una fórmula f es una fórmula β
beta :: LProp -> Bool
beta (Disy p q) = True
beta (Neg (Conj p q)) = True
beta (Impl p q) = True
beta _ = False

-- Nos dice si una fórmula f es una fórmula σ
sigma :: LProp -> Bool
sigma (Neg (Neg p)) = True
sigma (Neg T) = True
sigma (Neg F) = True
sigma _ = False

-- Dada una lista de fórmulas l y una fórmula f realiza la expansión alpha de f dentro la lista l.
expAlpha :: [LProp] -> LProp -> [LProp]
expAlpha [] _ = []
expAlpha [(Conj p q)] _ = [p,q]
expAlpha [(Neg (Disy p q))] _ = [Neg p, Neg q]
expAlpha [(Neg (Impl p q))] _ = [p, Neg q]
--si f es una fórmula α entonces aplica la expansión alpha y concatena el resto de fórmulas a la lista
--si no lo es, guarda su valor y evalúa la siguiente fórmula
expAlpha (x:xs) f = if (alpha x) && (f == x) then (expAlpha [x] f) ++ xs else [x] ++ (expAlpha xs f)


-- Dada una lista de fórmulas l y una fórmula f realiza la expansión beta de f sobre la lista l.
expBeta0 :: [LProp] -> LProp -> ([LProp], [LProp])
expBeta0 xs (Disy p q) = (p:xs, q:xs)
expBeta0 xs (Neg (Conj p q)) = ((Neg p):xs, (Neg q):xs)
expBeta0 xs (Impl p q) = ((Neg p):xs, q:xs)
--si f es una fórmula β, divide la fórmula en un tupla de listas siguiendo las reglas beta
--si no lo es, la pasa al final de la lista y evalúa la siguiente fórmula hasta dar con la correcta y llegar a la división
expBeta :: [LProp] -> LProp -> ([LProp], [LProp])
expBeta (x:xs) f = if (beta x) && (f == x) then (expBeta0 xs x) else (expBeta (xs ++ [x]) f)

-- Dada una lista de fórmulas l y una fórmula f, realiza la expansión sigma de f sobre la lista l.
expSigma :: [LProp] -> LProp -> [LProp]
expSigma [] _ = []
expSigma [Neg (Neg p)] _ = [p]
expSigma [(Neg T)] _ = [F]
expSigma [(Neg F)] _ = [T]
--si f es una fórmula σ entonces aplica la expansión sigma y concatena el resto de fórmulas a la lista
--si no lo es, guarda su valor y evalúa la siguiente fórmula
expSigma (x:xs) f = if (sigma x) && (f==x) then (expSigma [x] f) ++ xs else [x] ++ (expSigma xs f)

-- Construye el tableau a partir de una fórmula.
consTableaux :: LProp -> Tableaux
--establece si es Hoja, Alpha o Beta y usa recursividad para evaluar cada una de las fórmulas y sus ramas
consTableaux f = if (alpha f) then Alpha [f] (consTableaux (head (expAlpha [f] f)))
                  else if (beta f) then Beta [f] (consTableaux (head (fst (expBeta [f] f)))) (consTableaux (head (snd (expBeta [f] f))))
                  else if (sigma f) then consTableaux (head (expSigma [f] f))
                  else if (literales [f]) then Hoja [f]
                  else error "Formula no válida"



--------------CIFRADO CAESAR----------------
--Función que establece la posición de un char en el alfabeto
toNumber0 :: Char -> Int -> Int
toNumber0 c i = if (alfabeto !! (mod i 27)) == c then (mod i 27) else toNumber0 c (i+1) --caso recursivo
          where alfabeto = "abcdefghijklmnñopqrstuvwxyz"
toNumber :: Char -> Int
toNumber c = toNumber0 c 0
--Función que devuelve un char de acuerdo a su posición en el alfabeto
toChar :: Int -> Char
toChar n = alfabeto !! (mod n 27) where alfabeto = "abcdefghijklmnñopqrstuvwxyz"
--Función que convierte una cadena en un arreglo de enteros con las posiciones de cada letra en el alfabeto
toList :: String -> [Int]
toList s = map toNumber s


--Función que codifica una cadena aplicando el cifrado cesar sumando un llave, o la decodifica restando la llave
--convierte una cadena en lista de enteros, suma (o resta) la llave y convierte la lista resultante a cadena
cesar :: String -> Int -> String
cesar m k = map toChar (map (+(mod k 27)) (toList(m)))