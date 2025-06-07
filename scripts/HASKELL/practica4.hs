data LProp = PTrue | PFalse | Var Nombre | Neg LProp |
            Conj LProp LProp | Disy LProp LProp |
            Impl LProp LProp | Syss LProp LProp

type Nombre = String -- Nombre es un sinonimo para String.
type Asignacion = [(Nombre, Int)] -- Una asignación es una lista de tuplas.


--Crea la instancia de la clase show para LProp utilizando los símbolos adecuados.
instance Show LProp where
    show (PTrue)    = "True"
    show (PFalse)   = "False"
    show (Var p)    = show p
    show (Neg p)    = "¬" ++ show p
    show (Conj p q) = "(" ++ show p ++ " ^ " ++ show q ++ ")"
    show (Disy p q) = "(" ++ show p ++ " v " ++ show q ++ ")"
    show (Impl p q) = "(" ++ show p ++ " -> " ++ show q ++ ")"
    show (Syss p q) = "(" ++ show p ++ " <-> " ++ show q ++ ")"

--Función que elimina elementos duplicados de una lista
deleteDuplicate :: (Eq a) => [a] -> [a]
deleteDuplicate [] = []
deleteDuplicate (x:xs) = x : deleteDuplicate (filter (/= x) xs)
--Función que regresa la lista con todas las variables que aparecen en la expresión.
vars :: LProp -> [Nombre]
vars (Var p)    = [p]
vars (Neg p)    = vars p
vars (Conj p q) = deleteDuplicate (vars p ++ vars q)
vars (Disy p q) = deleteDuplicate (vars p ++ vars q)
vars (Impl p q) = deleteDuplicate (vars p ++ vars q)
vars (Syss p q) = deleteDuplicate (vars p ++ vars q)

--Función que aplica la ley de la asociatividad hacia la derecha sobre los elementos de la expresión.
asocia_der :: LProp -> LProp
asocia_der (Conj (Conj a b) c) = Conj a (Conj b c)
asocia_der (Conj p q)          = Conj p q
asocia_der (Disy (Disy a b) c) = Disy a (Conj b c)
asocia_der (Disy p q)          = Disy p q

--Lo mismo que asocia_der pero para el otro lado.
asocia_izq :: LProp -> LProp
asocia_izq (Conj a (Conj b c)) = Conj (Conj a b) c
asocia_izq (Conj p q)          = Conj p q
asocia_izq (Disy (Disy a b) c) = Disy (Conj a b) c
asocia_izq (Disy p q)          = Disy p q

--Función que aplica la ley de la conmutatividad de forma exhaustiva sobre los elementos de la expresión cuyo operador lógico sea conjunción o disyunción.
conm :: LProp -> LProp
conm (PTrue)    = PTrue
conm (PFalse)   = PFalse
conm (Var p)    = Var p
conm (Neg p)    = Neg (conm p)
conm (Conj p q) = Conj (conm q) (conm p)
conm (Disy p q) = Disy (conm q) (conm p)
conm (Impl p q) = Impl (conm p) (conm q)
conm (Syss p q) = Syss (conm p) (conm q)

--Función que aplica la ley de distributividad de forma exhaustiva sobre toda la expresión.
dist :: LProp -> LProp
dist (Conj a (Disy b c)) = Disy (Conj a b) (Conj a c)
dist (Conj p q)          = conm (Conj p q)
dist (Disy a (Conj b c)) = Conj (Disy a b) (Disy a c)
dist (Disy p q)          = conm (Disy p q)

--Función que le aplica a una LProp las leyes de De morgan.
deMorgan :: LProp -> LProp
deMorgan (PTrue)          = PTrue
deMorgan (PFalse)         = PFalse
deMorgan (Var p)          = Var p
deMorgan (Neg (Conj p q)) = Conj (Neg p) (Neg q)
deMorgan (Neg (Disy p q)) = Disy (Neg p) (Neg q)
deMorgan (Neg p)          = Neg p
deMorgan (Impl p q)       = Impl (deMorgan p) (deMorgan q)
deMorgan (Syss p q)       = Syss (deMorgan p) (deMorgan q)

--Función que aplica la equivalencia de operadores.
equiv_op :: LProp -> LProp
equiv_op (PTrue)    = PTrue
equiv_op (PFalse)   = PFalse
equiv_op (Var p)    = Var p
equiv_op (Neg p)    = Neg p
equiv_op (Conj p q) = Conj (equiv_op p) (equiv_op q)
equiv_op (Disy p q) = Disy (equiv_op p) (equiv_op q)
equiv_op (Impl p q) = Disy (Neg (equiv_op p)) (equiv_op q)
equiv_op (Syss p q) = Conj (Disy (Neg (equiv_op p)) (equiv_op q)) (Disy (Neg (equiv_op q)) (equiv_op p))

--Función que quita las dobles negaciones de una LProp.
dobleNeg :: LProp -> LProp
dobleNeg (Var p)       = Var p
dobleNeg (Neg (Neg p)) = dobleNeg p
dobleNeg (Neg p)       = Neg (dobleNeg p)
dobleNeg (Conj p q)    = Conj (dobleNeg p) (dobleNeg q)
dobleNeg (Disy p q)    = Disy (dobleNeg p) (dobleNeg q)
dobleNeg (Impl p q)    = Impl (dobleNeg p) (dobleNeg q)
dobleNeg (Syss p q)    = Syss (dobleNeg p) (dobleNeg q)

--Función que contesta con el número de conectivos lógicos en la expresión.
num_conectivos :: LProp -> Int
num_conectivos (PTrue)    = 0
num_conectivos (PFalse)   = 0
num_conectivos (Var p)    = 0
num_conectivos (Neg p)    = (num_conectivos p) + 1
num_conectivos (Conj p q) = (num_conectivos p) + (num_conectivos q) + 1
num_conectivos (Disy p q) = (num_conectivos p) + (num_conectivos q) + 1
num_conectivos (Impl p q) = (num_conectivos p) + (num_conectivos q) + 1
num_conectivos (Syss p q) = (num_conectivos p) + (num_conectivos q) + 1

--Esta función va a tomar una LProp ψ y una asignación para regresar la interpretacion de ψ a partir los valores de la asignación.
interpretacion :: LProp -> Asignacion -> Int
interpretacion (PTrue) _          = 1
interpretacion (PFalse) _         = 0
interpretacion (Var p) []         = error "No es posible calcular esta interpretación"
interpretacion (Var p) ((x,y):xs) = if p == x then y else interpretacion (Var p) xs
interpretacion (Neg p) xs         = if (interpretacion p xs) == 1 then 0 else 1
interpretacion (Conj p q) xs      = if ((interpretacion p xs) == 1 && (interpretacion q xs) == 1) then 1 else 0
interpretacion (Disy p q) xs      = if ((interpretacion p xs) == 0 && (interpretacion q xs) == 0) then 0 else 1
interpretacion (Impl p q) xs      = if ((interpretacion p xs) == 1 && (interpretacion q xs) == 0) then 0 else 1
interpretacion (Syss p q) xs      = if (interpretacion p xs) == (interpretacion q xs) then 1 else 0



----------ES ANAGRAMA----------
--Función que establece la posición de un char en el alfabeto
aux :: Char -> Int -> Int
aux c n = if alfabeto !! n == c then n else aux c (n+1) --caso recursivo
          where alfabeto = "abcdefghijklmnñopqrstuvwxyz"
aux1 :: Char -> Int
aux1 c = aux c 0
--Función que convierte una cadena en un arreglo de enteros con las posiciones de cada letra en el alfabeto
toList :: String -> [Int]
toList s = map aux1 s 
--Función que ordena una lista
sort :: [Int] -> [Int]
sort [] = [] --caso base
sort (x:xs) = (sort menores) ++ [x] ++ (sort mayores) --caso recursivo
              where 
                menores = filter (<x) xs
                mayores = filter (>=x) xs
--Función que dice si dos palabras son un anagrama
--ordena ambas cadenas como su posición en el alfabeto y estima si son iguales
isAnagrama :: String -> String -> Bool
isAnagrama s1 s2 = (sort (toList s1)) == (sort (toList s2))