#=
Utilizando la técnica de graficar sobre imágenes, se hace el fractal del triángulo de Sierpinski.
=#

using Plots

w, h = 1000, 1000
Sierpinski = [RGB(1,1,1) for i in 1:w, j in 1:h];

"""Función que devuelve los puntos medios de cada lado de un triángulo, en un vector de vectores"""
function puntos_medios(triangulo)
    p1 = triangulo[1]
    p2 = (triangulo[2] - triangulo[1])/2 .+ triangulo[1]
    p3 = (triangulo[1] - triangulo[3])/2 .+ triangulo[3]
    p4 = triangulo[3]
    p5 = (triangulo[3] - triangulo[2])/2 .+ triangulo[2]
    p6 = triangulo[2]
    
    #devuelve un vector de vectores de los puntos de los tres triángulos "externos"
    return [[p1,p2,p3,p1],[p3,p4,p5,p3],[p5,p6,p2,p5]]
end
"""Función que itera sobre cada uno de los triángulos contenidos en el triángulo ya definido,
    y aplica la función puntos_medios, devuelve un vector de vectores de vectores"""
function triangulo_sierpinski(triangulos)
    triangulos2 = []
    for i in 1:length(triangulos) #iteración de cada triángulo "base"
        s = puntos_medios(triangulos[i]) #variable auxiliar para almacenar el vector de vectores obtenido
        for j in 1:3 #iteración del vector de vectores con los puntos de los triángulos contenidos
            push!(triangulos2,s[j])
        end
    end
    #devuelve todos los puntos recolectados en un vector de vectores de vectores
    return triangulos2
end


# main
gr()
#OBTENCIÓN DE PUNTOS
triangulos =[[[1,1], [3,1], [2,sqrt(3)+1]]] #triángulo base
for i in 1:4 #itera sobre el número de niveles que se desee
    triangulos = triangulo_sierpinski(triangulos)
end
#GRÁFICA DE LOS PUNTOS
plot()
for i in 1:length(triangulos) #iteración del vector de vectores de vectores final obtenido
    plot!([triangulos[i][j][1] for j in 1:4],[triangulos[i][j][2] for j in 1:4],
        aspect_ratio = :equal, key= false, color = RGB(1,0,0.7) )
end
plot!()