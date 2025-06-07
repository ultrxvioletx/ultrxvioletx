#=
Diagramas de Cobweb:
Estos diagramas consisten de el mapeo de una funcion f que se va a estudiar, la recta identidad,
el segmento (x0,0), (x0,f(x0)), y de los segmentos de la forma (x_i,x_{x+1}), (x_{i+1},x_{x+1})
                                                                (x_i,x_{x+1}), (x_{i+1},x_{x+2})
Se hace una función que dado un mapeo f(x), un valor inicial x0 y un número de aplicaciones del mapeo,
regresa el diagrama de Cobweb correspondiente.
Se prueba con el mapeo logístico para el caso donde hay un punto atractivo (que corresponde a la intersección de la parábola y la recta identidad), comenzando desde x0 = 0.3. Se prueba también para el caso donde haya 2 valores que sean cíclicos
(o sea que f(f(x_c)) = x_c pero f(x_c) <> x_c
=#

using Plots

"""Esta función grafica una diagrama de Cobweb para una determinada función, un número de aplicaciones y algún punto inicial"""
function cobweb(f, n, x₀ᵢ, i=1, x₀=0)
    if i == 1 x₀ = x₀ᵢ end
    if i >= n
        insert!(puntos,1,[x₀,0])
        gr()
        return plot([(p[1],p[2]) for p in puntos])
    end
    push!(puntos, [x₀ᵢ,f(x₀ᵢ)], [f(x₀ᵢ),f(x₀ᵢ)])
    i += 1
    cobweb(f, n, f(x₀ᵢ), i, x₀)
end

# main
puntos=[]
cobweb(x-> 3.97*x*(1-x), 20, 0.3)
plot!([x-> x, x-> 3.97*x*(1-x)], key=false)