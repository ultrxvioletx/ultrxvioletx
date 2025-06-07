#=
Los números enteros se pueden acomodar en el plano siguiendo una espiral,
comenzando con 0 en el (0,0), siguiendo el 1 en (1,0), luego el 2 en el (1,1),
el 3 en el (0,1), 4 en en el (-1,1), etc... 
Este tipo de arreglos se ha usado (infructuosamente) para tratar de obtener información sobre cómo se distribuyen los números primos.

Se hace una matriz E de 1001x1001 donde cada elemento es un número entero entre 0 y 1002000
y de tal forma que el centro de la matriz tiene el 0, el resto de los elementos siga la espiral de números enteros.
Luego, se hace una segunda matriz P que tenga 0 si no es primo y 1 si lo es.
Finalmente, se utiliza la paquetería Colors para hacer una matriz cuyos elementos sean un RGB relacionado con P
(por ejemplo RGB(Pij,0,0)).
=#


using Colors
dim = 100
centro = isodd(dim) ? Int(dim/2 + 0.5) : Int(dim/2) # establece el centro de la matriz
numeros = [x for x in 1:dim*dim-1] # establece los números que contiene la matriz de acuerdo a su dimensión
E = zeros(dim,dim) # crea la matriz iniciandola en ceros

B = [-i*(-1)^j for i in 0:dim for j in 1:2][2:dim+1] # se crea un array que tiene valores i,-i desde 0 hasta dim/2

K(n) = [B[n]-(k)*(-1)^n + centro for k in 1:n]
N(n) = [B[n]-(n)*(-1)^n + centro for k in 1:n]
X = collect(Iterators.flatten((collect(Iterators.flatten(([[K(n), N(n)] for n in 1:dim]))))))

Y1(n) = [B[n] + centro for k in 1:n]
Y2(n) = [B[n]+(-k)*(-1)^n + centro for k in 1:n]
Y = collect(Iterators.flatten((collect(Iterators.flatten(([[Y1(n), Y2(n)] for n in 1:dim]))))))

coordenadas = [CartesianIndex(X[i],Y[i]) for i in 1:dim*dim][1:dim*dim-1]
E[coordenadas] = numeros

p(x) = prod(sign.(x.%(2:round(sqrt(x)))))
p.(E)

[Colors.RGB(p.(E)[CartesianIndex(i,j)]) for i in 1:dim, j in 1:dim]