#=
Utilizando la técnica de graficar sobre imágenes, se hace un fractal de arbol.
=#

using Plots

w, h = 1000, 1000
Arbol = [RGB(1,1,1) for i in 1:w, j in 1:h];

"""Función que devuelve los puntos rama de cada segmento tronco, en un vector de vectores"""
rotacion(θ) = [cos(θ) -sin(θ); sin(θ) cos(θ)]
function puntos_rama(segmento)
    tronco = segmento[2]-segmento[1]
    p1 = segmento[1]
    p2 = segmento[2]
    p3 = rotacion(π/3)*tronco/1.75 .+ p2
    p4 = rotacion((π/3)*(-1))*tronco/1.75 .+ p2
    
    #devuelve un vector de vectores de los puntos del tronco y las ramas
    return [[p1,p2],[p2,p3],[p2,p4]]
end
"""Función que itera sobre cada uno de los segmentos contenidos en el segmento tronco ya definido,
    y aplica la función puntos_rama, devuelve un vector de vectores de vectores"""
function fractal_arbol(segmentos)
    segmentos2 = []
    for i in 1:length(segmentos) #iteración de cada segmento tronco
        s = puntos_rama(segmentos[i]) #variable auxiliar para almacenar el vector de vectores obtenido
        for j in 1:3 #iteración del vector de vectores con los puntos de las ramas
            push!(segmentos2,s[j])
        end
    end
    #devuelve todos los puntos recolectados en un vector de vectores de vectores
    return segmentos2
end


# main
gr()
#OBTENCIÓN DE PUNTOS
segmentos =[[[1,1], [1,2]]] #segmento base
for i in 1:7 #itera sobre el número de niveles que se desee
    segmentos = fractal_arbol(segmentos)
end
#GRÁFICA DE LOS PUNTOS
plot()
for i in 1:length(segmentos) #iteración del vector de vectores de vectores final obtenido
    plot!([segmentos[i][j][1] for j in 1:2],[segmentos[i][j][2] for j in 1:2],
        aspect_ratio = :equal, key= false, color = 1 )
end
plot!()