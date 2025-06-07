--------------Por qué? porque sí.--------------
--SOBRE NÚMEROS...
--Función que recibe dos números y devuelve la potencia
potencia :: Int -> Int -> Int
potencia b 0 = 1 --caso base
potencia b p = b * (potencia b (p-1)) --caso recursivo

--Funcion que devuelve la suma de números pares de un número par
suma_pares :: Int -> Int
suma_pares 0 = 0 --caso base
suma_pares n = n + suma_pares(n-2) --caso recursivo

--Función que devuelve el n-ésimo número triangular
triangular :: Int -> Int
triangular 1 = 1 --caso base
triangular n = n + triangular(n-1) --caso recursivo

--Función que devuelve el número correspondiente en la serie fibonacci dado un n
fibo :: Int -> Int
fibo 0 = 0 --caso base
fibo 1 = 1 --caso base
fibo n = fibo (n-1) + fibo (n-2) --caso recursivo

--SOBRE LISTAS...
--Función que devuelve el último elemento de una lista
ultimo :: [a] -> a
ultimo [a] = a --caso base
ultimo (x:xs) = ultimo xs --caso recursivo

--Función que devuelve el reverso de una lista dada
reversa :: [a] -> [a]
reversa [] = [] --caso base
reversa (x:xs) = (reversa xs) ++ [x] --caso recursivo

--Función que te dice si un elemento pertenece o no a una lista
elemento :: Eq a => a -> [a] -> Bool
elemento x [] = False --caso base
elemento x (y:ys) = (x == y) || (elemento x ys) --caso recursivo


--------------Pensar correcto es lo que hago--------------
--Perfecto, abundante o deficiente
data Categoria = Perfecto | Deficiente | Abundante deriving Show

--Función que devuelve una lista con los factores de un número n
factores :: Int -> Int -> [Int]
factores n 0 = []
factores n i = if ((mod n i) == 0) then i:factores n (i-1) else factores n (i-1)

--Función que te dice si un número n es perfecto, deficiente o abundante
nicomaco :: Int -> Categoria
nicomaco n = if sum (factores n (n-1)) == n then
                Perfecto
            else
                if sum (factores n (n-1)) < n then
                    Deficiente
                else
                    Abundante

--Luhn

--Función que multiplica por dos un elemento sí y otro no en una lista
doble :: [Int] -> [Int]
doble [] = []
doble [x] = [x]
doble (x:y:zs) = 2*x : y : doble zs

--Función que resta 9 a cada entrada de una lista si su valor es mayor que 9
resta :: [Int] -> [Int]
resta [] = []
resta (x:xs) = if x>9 then x-9 : resta xs else x : resta xs

--Función que te dice si un número es válido de acuerdo al algoritmo de Luhn
luhn :: [Int] -> Bool
luhn (xs) = mod (sum (resta (doble xs))) 10 == 0

--Conjetura de Collatz
--Función que devuelve una lista con las transformaciones de un número n al aplicar los pasos de la conjetura de Collatz
listaCollatz :: Int -> [Int]
listaCollatz 1 = [1]
listaCollatz n = if mod n 2 == 0 then n : listaCollatz (div n 2) else n : listaCollatz (3*n + 1)

--Función que devuelve el número de pasos que deben darse para convertir un número a 1
pasosCollatz :: Int -> Int
pasosCollatz n = length (listaCollatz n) - 1


--------------Expresiones ariméticas--------------
data EA = N Int | Positivo EA | Negativo EA | Suma EA EA | Resta EA EA | Mult EA EA | Div EA EA | Mod EA EA | Pot EA EA

negativoEA :: Int -> EA
negativoEA n = if n<0 then Negativo (N n) else (N n)

creaSumaEA :: Int -> Int -> EA
creaSumaEA a b = Suma (negativoEA a) (negativoEA b)

creaResta :: Int -> Int -> EA
creaResta a b = Resta (negativoEA a) (negativoEA b)

creaMultEA :: Int -> Int -> EA
creaMultEA a b = Mult (negativoEA a) (negativoEA b)

creaDivEA :: Int -> Int -> EA
creaDivEA a b = Div (negativoEA a) (negativoEA b)

creaModEA :: Int -> Int -> EA
creaModEA a b = Mod (negativoEA a) (negativoEA b)

creaPotEA :: Int -> Int -> EA
creaPotEA a b = Pot (negativoEA a) (negativoEA b)

--Instancias show para mostrar las expresiones aritméticas
instance Show EA where
    show (N n) = show n
    show (Positivo a) = show a
    show (Negativo a) = "(" ++ show a ++ ")"
    show (Suma a b) = show a ++ " + " ++ show b
    show (Resta a b) = show a ++ " - " ++ show b
    show (Mult a b) = show a ++ " x " ++ show b
    show (Div a b) = show a ++ " / " ++ show b
    show (Mod a b) = show a ++ " % " ++ show b
    show (Pot a b) = show a ++ " ^ " ++ show b

instance Eq EA where
    (N a) == (N b) = a == b

instance Ord EA where
    compare (N a) (N b) = compare a b

menorque :: EA -> EA -> Bool
menorque a b = a < b

mayorque :: EA -> EA -> Bool
mayorque a b = a > b