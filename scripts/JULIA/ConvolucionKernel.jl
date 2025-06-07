#=
Convoluciones: Para hacer una convolución primero se genera una función para mezclar colores de un cuadrado de
(2n+1)x(2n+1) pixeles (típicamente elegimos n=1), que se le conoce como Kernel.
En este caso, se hace dado un kernel cualquiera.
Para cada pixel (que es un objeto RGB), obtenemos la cantidad de rojo, verde y azul que tiene usando
pixel[i,j].r, pixel[i,j].g y pixel[i,j].b
luego, en la nueva imágen tendremos que
    pixel_nueva_imagen[i,j] = RGB((pixel[i,j].r+pixel[i,j+1].r+pixel[i,j-1].r+...)/9, (pixel[i,j].g+pixel[i,j+1].g+pixel[i,j-1].g+...)/9, (pixel[i,j].b+pixel[i,j+1].b+pixel[i,j-1].b+...)/9).

Aquí hay que notar que cuando i o j corresponden a la frontera, no existirán algunos de los vecinos.
En ese caso se puede sustituir el vecino por un color fijo, por ejemplo negro o blanco.

Nota: Hay algunos kernels donde pueden salir proporciones negativas de algún color. No tiene sentido RGB(-1,0,0),
así que la regla es: si algún color tiene más de 1, entonces se vuelve 1 y si tiene menos de 0, se vuelve 0.
=#

using Images
Imagen = load("Imagen.jpg")
Imagen[1:3:end, 1:3:end]


function aplica_kernel(color,kernel,n, x,y)
    vecinos = [color[x+i, y+j] for i in -n:n, j in -n:n] #establece la vecindad alrededor del pixel
    suma = sum(vecinos .* kernel) #multiplica la vecindad por el kernel entrada por entrada y suma todos los valores
    
    #si la suma es mayor a 1, devuelve 1; si la suma es menor a 0, devuelve 0; el cualquier otro caso devuelve el valor calculado
    if suma<0 suma=0
    elseif suma>1 suma=1
    else suma
    end
    
    return suma
end
function convolucion(Imagen, kernel)
    tamaño = size(Imagen)
    n = Int((size(kernel)[1]-1)/2)
    
    #crea bordes de tamaño n alrededor de la imagen y al mismo tiempo descompone en rojo, verde y azul
    RED = zeros(tamaño[2]+2n, tamaño[1]+2n)
    GREEN = zeros(tamaño[2]+2n, tamaño[1]+2n)
    BLUE = zeros(tamaño[2]+2n, tamaño[1]+2n)
    for i in 1:tamaño[2]+(2*n)
        for j in 1:tamaño[1]+(2*n)
            if (i<=n || i>tamaño[2]+n || j<=n || j>tamaño[1]+n)
                RED[i,j] = 1
                GREEN[i,j] = 1
                BLUE[i,j] = 1
            else
                RED[i,j] = red(Imagen[j-n,i-n])
                GREEN[i,j] = green(Imagen[j-n,i-n])
                BLUE[i,j] = blue(Imagen[j-n,i-n])
            end
        end
    end
    
    #almacena los nuevos valores de rojo, verde y azul ya aplicada la convolucion
    RED_nueva = [aplica_kernel(RED,kernel,n, i,j) for i in n+1:size(RED)[1]-n, j in n+1:size(RED)[2]-n]
    GREEN_nueva = [aplica_kernel(GREEN,kernel,n, i,j) for i in n+1:size(GREEN)[1]-n, j in n+1:size(GREEN)[2]-n]
    BLUE_nueva = [aplica_kernel(BLUE,kernel,n, i,j) for i in n+1:size(BLUE)[1]-n, j in n+1:size(BLUE)[2]-n]
    #crea la nueva imagen con la composición de rojo, verde y azul
    nueva_imagen = [RGB(RED_nueva[i,j], GREEN_nueva[i,j], BLUE_nueva[i,j]) for j in n+1:size(RED_nueva)[2]-n, i in n+1:size(RED_nueva)[1]-n]
    
    return nueva_imagen
end


# main
kernel = [-1 -1 -1; -1 8 -1; -1 -1 -1]
convolucion(Imagen,kernel)[1:3:end, 1:3:end]