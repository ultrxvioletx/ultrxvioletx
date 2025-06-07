type EList a = [(a,a)]

--- Dada una EList obtiene su número de elementos.
longP :: EList a -> Int
longP [] = 0 --caso base
longP ((x,y):xs) = 2 + longP xs --caso recursivo

--- Dado elemento e y una Elist l, verifica si e pertenece a l.
elemP :: Eq a => a -> EList a -> Bool
elemP x [] = False --caso base
elemP x ((y,z):ys) = (x == y) || (x == z) || (elemP x ys) --caso recursivo

--- Dados dos elementos y una EList, los agrega al principio de la Elist.
consP :: (a,a) -> EList a -> EList a
consP (x,y) xs = (x,y) : xs

--- Función que realiza la concatenación de dos EList.
appendP :: EList a -> EList a -> EList a
appendP [] l = l  --caso base
appendP ((x,y):xs) l = (x,y) : (appendP xs l) --caso recursivo

--- Función que agrega dos elementos al final de una EList.
snocP :: (a,a) -> EList a -> EList a
snocP (x,y) xs = xs ++ [(x,y)]

--- Dada una EList l y un entero n, regresa el n-ésimo elemento de l.
atP :: EList a -> Int -> a
atP ((x,y):xs) 1 = x --caso base
atP ((x,y):xs) 2 = y --caso base
atP ((x,y):xs) n = atP xs (n-2) --caso recursivo

--- Dada una EList l, un número n y un elemento e, cambia el n-ésimo elemento de l por e.
updateP :: EList a -> Int -> a -> EList a
updateP ((x,y):xs) 1 e = appendP [(e,y)] xs --caso base
updateP ((x,y):xs) 2 e = appendP [(x,e)] xs --caso base
updateP ((x,y):xs) n e = appendP [(x,y)] (updateP xs (n-2) e) --caso recursivo

--- Función que recibe una EList l y regresa la misma pero aplanada.
aplanaP :: EList a -> [a]
aplanaP [] = [] --caso base
aplanaP ((x,y):xs) = [x] ++ [y] ++ (aplanaP xs) --caso recursivo

--- Función que convierte una lista común en una EList.
toEL :: [a] -> EList a
toEL [] = [] --caso base
toEL [x] = [] --caso base
toEL (x:y:xs) = [(x,y)] ++ (toEL xs) --caso recursivo

--- Dado un entero n y una EList l, borra los n primeros elementos de l, donde n es par.
dropP :: Int -> EList a -> EList a
dropP 0 xs = xs --caso base
dropP n ((x,y):xs) = if (mod n 2 == 0) then dropP (n-2) xs else error "No es un numero par" --caso recursivo

--- Borra los n primeros elementos de l y regresa una lista común.
dropn :: Int -> [a] -> [a] --función auxiliar
dropn 0 xs = xs --caso base
dropn n (x:xs) = dropn (n-1) xs --caso recursivo

dropN :: Int -> EList a -> [a]
dropN n xs = dropn n (aplanaP xs)

--- Dado un entero n y una EList l, toma los n primeros elementos l, n debe ser par.
takeP :: Int -> EList a -> EList a
takeP 0 xs = [] --caso base
takeP n ((x,y):xs) = [(x,y)] ++ takeP (n-2) xs --caso recursivo

--- Toma los primeros n elementos de una EList y regresa una lista común.
taken :: Int -> [a] -> [a] --función auxiliar
taken 0 xs = [] --caso base
taken n (x:xs) = [x] ++ taken (n-1) xs --caso recursivo

takeN :: Int -> EList a -> [a]
takeN n xs = taken n (aplanaP xs)

--- Elabora una función que haga la reversa de una EList.
reversaP :: EList a -> EList a
reversaP [] = [] --caso base
reversaP ((x,y):xs) = reversaP xs ++ [(y,x)] --caso recursivo

--- Función map para esta estructura.
mapP :: (EList a -> EList a) -> EList a -> EList a
mapP f [] = [] --caso base
mapP f ((x,y):xs) = appendP (f [(x,y)]) (mapP f xs) --caso recursivo